package com.maxiannicu.pomodoro;

import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

import com.maxiannicu.pomodoro.databinding.ActivityMainBinding;
import com.maxiannicu.pomodoro.viewmodels.PomodoroActivityViewModel;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActivityMainBinding binding = DataBindingUtil.setContentView(this, R.layout.activity_main);
        PomodoroActivityViewModel viewModel = new PomodoroActivityViewModel(this);
        binding.setViewModel(viewModel);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.main_activity,menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == R.id.menu_statistics_activity){
            startActivity(new Intent(this,StatisticsActivity.class));
        }
        return super.onOptionsItemSelected(item);
    }
}
