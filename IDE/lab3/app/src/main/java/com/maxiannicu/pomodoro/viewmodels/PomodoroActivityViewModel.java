package com.maxiannicu.pomodoro.viewmodels;

import android.content.Context;
import android.databinding.BaseObservable;
import android.databinding.Bindable;
import android.databinding.BindingAdapter;
import android.os.Vibrator;
import android.view.View;

import com.maxiannicu.pomodoro.BR;
import com.maxiannicu.pomodoro.helpers.TimeHelper;
import com.maxiannicu.pomodoro.models.PomodoroActivityModel;
import com.maxiannicu.pomodoro.models.PomodoroEntry;
import com.maxiannicu.pomodoro.widgets.CircleProgressBar;

import java.util.Calendar;
import java.util.Date;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

/**
 * Created by nick on 5/2/16.
 */
public class PomodoroActivityViewModel extends BaseObservable implements Runnable {
    public static final int TOTAL_SECONDS = 1500;
    public static final int ELAPSED_SECONDS = 0;
    private Context context;
    private PomodoroActivityModel model;
    private ScheduledExecutorService executorService;
    private ScheduledFuture<?> future;
    private boolean inProgress;
    private Date startTime;
    private int duration;

    public PomodoroActivityViewModel(Context context) {
        this.context = context;
        model = new PomodoroActivityModel();
        executorService = Executors.newSingleThreadScheduledExecutor();
    }

    public void start(View view) {
        future = executorService.scheduleAtFixedRate(this, 0, 1, TimeUnit.SECONDS);
        initModel();
        notifyPropertyChanged(BR.max);
        setInProgress(true);
        initFutureModelData();
    }

    private void initModel() {
        model.setTotalSeconds(TOTAL_SECONDS);
        model.setElapsedSeconds(ELAPSED_SECONDS);
    }

    private void initFutureModelData() {
        startTime = Calendar.getInstance().getTime();
    }

    public void stop(View view) {
        future.cancel(false);
        duration = model.getElapsedSeconds();
        setInProgress(false);
        vibrate();
        saveEntry();
    }

    private void saveEntry() {
        PomodoroEntry entry = new PomodoroEntry(startTime,duration);
        entry.save();
    }

    @Bindable
    public String getProgressText() {
        if(!inProgress){
            return "";
        }

        return TimeHelper.getDuration(model.getRemainingSeconds());
    }

    @Bindable
    public int getMax() {
        return model.getTotalSeconds();
    }

    @Bindable
    public int getProgress() {
        return model.getElapsedSeconds();
    }

    @Bindable
    public int getStartVisibility() {
        return inProgress ? View.GONE : View.VISIBLE;
    }

    @Bindable
    public int getStopVisibility() {
        return inProgress ? View.VISIBLE : View.GONE;
    }

    @Override
    public void run() {
        model.tick();
        notifyPropertyChanged(BR.progress);
        notifyPropertyChanged(BR.progressText);
        if (model.isDone()) {
            stop(null);
        }
    }
    private void setInProgress(boolean inProgress) {
        this.inProgress = inProgress;
        notifyPropertyChanged(BR.startVisibility);
        notifyPropertyChanged(BR.stopVisibility);
    }

    private void vibrate(){
        Vibrator v = (Vibrator) this.context.getSystemService(Context.VIBRATOR_SERVICE);
        v.vibrate(500);
    }

    @BindingAdapter("animateProgress")
    public static void animateProgress(CircleProgressBar circleProgressBar, int progress) {
        circleProgressBar.setProgressWithAnimation(progress);
    }

}
