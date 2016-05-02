package com.maxiannicu.pomodoro.adapters;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.maxiannicu.pomodoro.R;
import com.maxiannicu.pomodoro.models.PomodoroEntry;
import com.maxiannicu.pomodoro.viewholders.PomodoroEntryViewHolder;

import java.util.List;

/**
 * Created by nick on 5/2/16.
 */
public class PomodoroEntryAdapter extends RecyclerView.Adapter<PomodoroEntryViewHolder> {
    private LayoutInflater layoutInflater;
    private List<PomodoroEntry> list;

    public PomodoroEntryAdapter(List<PomodoroEntry> list) {
        this.list = list;
    }

    @Override
    public PomodoroEntryViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        layoutInflater = LayoutInflater.from(parent.getContext());
        View view = layoutInflater.inflate(R.layout.item_pomodoro_entry, parent, false);
        return new PomodoroEntryViewHolder(view);
    }

    @Override
    public void onBindViewHolder(PomodoroEntryViewHolder holder, int position) {
        holder.setModel(position+1,list.get(position));
    }

    @Override
    public int getItemCount() {
        return list.size();
    }
}
