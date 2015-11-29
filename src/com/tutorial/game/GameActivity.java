package com.tutorial.game;

import android.content.Intent;
import android.content.IntentSender;
import android.util.Log;

import java.lang.Override;
import java.lang.String;

import org.libsdl.app.SDLActivity;

public class GameActivity extends SDLActivity
{
    //public static String SCORE = "0";

    @Override
    protected void onDestroy() {
        Log.v("SDL", "onDestroy()");
        // Send a quit message to the application
        SDLActivity.mExitCalledFromJava = true;
        SDLActivity.nativeQuit();

        // Now wait for the SDL thread to quit
        if (SDLActivity.mSDLThread != null) {
            try {
                SDLActivity.mSDLThread.join();
            } catch(Exception e) {
                Log.v("SDL", "Problem stopping thread: " + e);
            }
            SDLActivity.mSDLThread = null;

            //Log.v("SDL", "Finished waiting for SDL thread");
        }

        super.onDestroy();

        Intent myIntent = new Intent(GameActivity.this, GameOverActivity.class);
        //myIntent.putExtra("SCORE", SCORE);
        GameActivity.this.startActivity(myIntent);

        // Reset everything in case the user re opens the app
        SDLActivity.initialize();
    }
		
}

