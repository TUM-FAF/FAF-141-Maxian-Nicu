package com.maxiannicu.pomodoro.models;

import com.orm.SugarRecord;

import java.util.Date;

/**
 * Created by nick on 5/2/16.
 */
public class PomodoroEntry extends SugarRecord {
    private Date startDate;
    private int duration;

    public PomodoroEntry() {
    }

    public PomodoroEntry(Date startDate, int duration) {
        this.startDate = startDate;
        this.duration = duration;
    }

    public Date getStartDate() {
        return startDate;
    }

    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }

    public int getDuration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }
}
