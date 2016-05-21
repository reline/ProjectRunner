package com.tutorial.game;

import android.content.Intent;
import android.content.IntentSender;
import android.util.Log;
import android.os.Bundle;
import android.app.Activity;
import android.widget.Button;
import android.view.View;

import java.lang.Override;
import java.lang.String;
import java.lang.System;

import org.libsdl.app.SDLActivity;

public class MainActivity extends Activity {

    private static final String TAG = "MainActivity";

    private Button playButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        playButton = (Button) findViewById(R.id.play_button);
        playButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(MainActivity.this, GameActivity.class);
                MainActivity.this.startActivity(myIntent);
            }
        });
    }
}

