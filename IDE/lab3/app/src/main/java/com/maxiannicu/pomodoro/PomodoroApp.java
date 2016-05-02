package com.maxiannicu.pomodoro;

import android.app.Application;

import com.orm.SugarContext;

/**
 * Created by nick on 5/2/16.
 */
public class PomodoroApp extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        SugarContext.init(this);
    }
}
