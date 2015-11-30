package com.tutorial.game;

import android.content.Intent;
import android.content.IntentSender;
import android.util.Log;
import android.os.Bundle;

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
    public static native String stringFromJNI();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(TAG, stringFromJNI());

        // if player lives == 0, push the score to a new intent
        /*Intent myIntent = new Intent(GameActivity.this, GameOverActivity.class);
        myIntent.putExtra("SCORE", SCORE);
        GameActivity.this.startActivity(myIntent);*/
    }
}

