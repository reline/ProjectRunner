package com.raisingthebar.projectr;

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

public class GameoverActivity extends Activity {

    private static final String TAG = "DEBUGGING";
    private Button continueButton;
    private int count = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gameover);

        continueButton = (Button) findViewById(R.id.continueButton);
        continueButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d(TAG, "Continue " + Integer.toString(++count));

                Intent myIntent = new Intent(GameoverActivity.this, GameActivity.class);
                GameoverActivity.this.startActivity(myIntent);
                myIntent = new Intent(GameoverActivity.this, GameActivity.class);
                GameoverActivity.this.startActivity(myIntent);
            }
        });

        // TODO: display the score and save to the database along with a username that the user enters here

    }
}

