package com.raisingthebar.projectr;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

public class GameActivity extends SDLActivity {

    private Handler handler;

    static {
        System.loadLibrary("main");
    }

    // define native functions in jni/
    public static native boolean isGameFinished();
    public static native int getScore();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        handler = new Handler();

        final Runnable r = new Runnable() {
            public void run() {
                if (isGameFinished()) {
                    // if player lives == 0, push the score to a new intent
                    Intent myIntent = new Intent(GameActivity.this, GameoverActivity.class);
                    myIntent.putExtra("SCORE", getScore());
                    GameActivity.this.startActivity(myIntent);
                    nativeQuit();
                } else {
                    handler.postDelayed(this, 1000);
                }
            }
        };

        handler.postDelayed(r, 1000);
    }
}

