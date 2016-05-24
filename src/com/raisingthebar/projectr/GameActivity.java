package com.raisingthebar.projectr;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

public class GameActivity extends SDLActivity {

    private static final String TAG = "GameActivity";
    private Handler handler;
    private boolean flag;

    static {
        System.loadLibrary("main");
    }

    // define native functions in jni/SDL2/src/main/android/SDL_android_main.c && jni/src/
    public static native boolean isGameFinished();
    //public static native Boolean isGameFinished();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "Game " + Boolean.toString(isGameFinished()));

        super.onCreate(savedInstanceState);

        handler = new Handler();
        flag = false;

        final Runnable r = new Runnable() {
            public void run() {

                if (isGameFinished()) {
                    nativeQuit();

                    // if player lives == 0, push the score to a new intent
                    Intent myIntent = new Intent(GameActivity.this, GameoverActivity.class);
                    // myIntent.putExtra("SCORE", SCORE);
                    GameActivity.this.startActivity(myIntent);
                    flag = true;
                }

                if (!flag) {
                    handler.postDelayed(this, 1000);
                }
            }
        };

        handler.postDelayed(r, 1000);
    }
}

