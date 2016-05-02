package com.maxiannicu.pomodoro.models;

/**
 * Created by nick on 5/2/16.
 */
public class PomodoroActivityModel {
    private int totalSeconds;
    private int elapsedSeconds;

    public int getTotalSeconds() {
        return totalSeconds;
    }

    public void setTotalSeconds(int totalSeconds) {
        this.totalSeconds = totalSeconds;
    }

    public int getElapsedSeconds() {
        return elapsedSeconds;
    }

    public void setElapsedSeconds(int elapsedSeconds) {
        this.elapsedSeconds = elapsedSeconds;
    }

    public void tick(){
        this.elapsedSeconds++;
    }

    public boolean isDone(){
        return elapsedSeconds >= totalSeconds;
    }

    public int getRemainingSeconds(){
        return totalSeconds- elapsedSeconds;
    }
}
