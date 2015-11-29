package com.tutorial.game;

import android.content.Intent;
import android.content.IntentSender;
import android.util.Log;

import java.lang.Override;
import java.lang.String;

import org.libsdl.app.SDLActivity;

public class GameActivity extends SDLActivity
{
    private static final String TAG = "GameActivity";

    public static String SCORE = "0";

    @Override
    protected void onDestroy() {
        super.onDestroy();

        Log.d(TAG, "onDestroy()");

        Intent myIntent = new Intent(GameActivity.this, GameOverActivity.class);
        //myIntent.putExtra("SCORE", SCORE);
        GameActivity.this.startActivity(myIntent);
    }
		
}

