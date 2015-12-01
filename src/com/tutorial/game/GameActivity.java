package com.tutorial.game;

import android.content.Intent;
import android.content.IntentSender;
import android.util.Log;
import android.os.Bundle;
import android.os.Handler;
import android.os.AsyncTask;

import java.lang.Integer;
import java.lang.Override;
import java.lang.String;
import java.lang.System;

import org.libsdl.app.SDLActivity;

public class GameActivity extends SDLActivity
{
    private static final String TAG = "GameActivity";

    static {
        System.loadLibrary("main");
    }

    // define native functions in jni/SDL2/src/main/android/SDL_android_main.c
    public static native int currentLives();
    public static native int currentScore();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        LifeCheck lifeCheck = new LifeCheck();
        lifeCheck.execute(0);
    }

    public class LifeCheck extends AsyncTask<Integer, Integer, Integer> {

        @Override
        protected Integer doInBackground(Integer... number) {
            while(true) {
                Log.d(TAG, "currentLives: " + Integer.toString(currentLives()));
                if(currentLives() == 0) {
                    Log.d(TAG, "YOU ARE SO TOTALLY DEAD: " + Integer.toString(currentLives()));
                    return currentScore();
                }
            }
        }

        @Override
        protected void onPostExecute(Integer currentScore) {
            Intent myIntent = new Intent(GameActivity.this, GameOverActivity.class);
            myIntent.putExtra("SCORE", currentScore);
            GameActivity.this.startActivity(myIntent);
            finish();
        }

    }
}

