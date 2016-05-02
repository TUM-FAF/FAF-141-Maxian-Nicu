package com.maxiannicu.pomodoro.viewholders;

import android.support.v7.widget.RecyclerView;
import android.view.View;

import com.maxiannicu.pomodoro.databinding.ItemPomodoroEntryBinding;
import com.maxiannicu.pomodoro.models.PomodoroEntry;
import com.maxiannicu.pomodoro.viewmodels.PomodoroEntryViewModel;

/**
 * Created by nick on 5/2/16.
 */
public class PomodoroEntryViewHolder extends RecyclerView.ViewHolder {
    private ItemPomodoroEntryBinding binding;

    public PomodoroEntryViewHolder(View itemView) {
        super(itemView);
        binding = ItemPomodoroEntryBinding.bind(itemView);
    }

    public void setModel(int order,PomodoroEntry model){
        binding.setViewModel(new PomodoroEntryViewModel(order,model));
    }
}
