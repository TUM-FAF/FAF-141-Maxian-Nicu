package com.maxiannicu.pomodoro.viewmodels;

import com.maxiannicu.pomodoro.helpers.TimeHelper;
import com.maxiannicu.pomodoro.models.PomodoroEntry;

/**
 * Created by nick on 5/2/16.
 */
public class PomodoroEntryViewModel {
    private PomodoroEntry model;
    private int order;

    public PomodoroEntryViewModel(int order,PomodoroEntry model) {
        this.order = order;
        this.model = model;
    }

    public String getOrder(){
        return Integer.toString(order);
    }

    public String getDuration(){
        return TimeHelper.getPrettyDuration(model.getDuration());
    }

    public String getDate(){
        return TimeHelper.getDate(model.getStartDate());
    }
}
