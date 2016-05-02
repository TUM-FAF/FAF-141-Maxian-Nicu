package com.maxiannicu.pomodoro;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

import com.maxiannicu.pomodoro.adapters.PomodoroEntryAdapter;
import com.maxiannicu.pomodoro.models.PomodoroEntry;

public class StatisticsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_statistics);
        initRecycler();
    }

    private void initRecycler() {
        RecyclerView recyclerView = (RecyclerView)findViewById(R.id.recycler);
        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        layoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setAdapter(new PomodoroEntryAdapter(PomodoroEntry.listAll(PomodoroEntry.class,"id desc")));
    }
}
