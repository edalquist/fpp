#pragma once
/*
 * This file is part of the Falcon Player (FPP) and is Copyright (C)
 * 2013-2022 by the Falcon Player Developers.
 *
 * The Falcon Player (FPP) is free software, and is covered under
 * multiple Open Source licenses.  Please see the included 'LICENSES'
 * file for descriptions of what files are covered by each license.
 *
 * This source file is covered under the LGPL v2.1 as described in the
 * included LICENSE.LGPL file.
 */


class Timers {
public:
    static Timers INSTANCE;

    Timers();
    ~Timers();

    void fireTimers() {
        if (hasTimers) {
            long long t = GetTimeMS();
            if (t >= nextTimer) {
                fireTimersInternal(t);
            }
        }
    }

    void addTimer(const std::string &name, long long fireTimeMS, std::function<void()>& callback);
    void addTimer(const std::string &name, long long fireTimeMS, const std::string &preset);

private:    
    bool hasTimers = false;
    long long nextTimer = 0;


    class TimerInfo {
    public:
        TimerInfo() {}
        ~TimerInfo() {}

        std::string id;
        long long   fireTimeMS;
        std::string commandPreset;
        std::function<void()> callback;
    };
    std::vector<TimerInfo*> timers;


    void fireTimersInternal(long long t);
    void fireTimer(TimerInfo *);
    void updateTimers();
};