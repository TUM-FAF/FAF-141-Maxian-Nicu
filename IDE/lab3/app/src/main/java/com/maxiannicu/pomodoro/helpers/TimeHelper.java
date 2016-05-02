package com.maxiannicu.pomodoro.helpers;

import org.ocpsoft.prettytime.PrettyTime;

import java.util.Date;

/**
 * Created by nick on 5/2/16.
 */
public class TimeHelper {
    private static PrettyTime prettyTime = new PrettyTime();

    public static String getDuration(int duration){
        int remains = duration;
        int minutes = remains / 60;
        remains %= 60;
        int seconds = remains;

        return String.format("%d:%d", minutes, seconds);
    }

    public static String getPrettyDuration(int duration){
        int remains = duration;
        int minutes = remains / 60;
        remains %= 60;
        int seconds = remains;

        String result = "";

        if(minutes > 0)
            result += Integer.toString(minutes) + "m";
        if(seconds > 0) {
            if (result.length() > 0)
                result += " , ";
            result += Integer.toString(seconds) + "s";
        }

        return result;
    }

    public static String getDate(Date date){
        return prettyTime.format(date);
    }
}
