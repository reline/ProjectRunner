package com.tutorial.game;

import android.app.Activity;
import android.content.Intent;
import android.content.IntentSender;
import android.os.Bundle;
import android.widget.Button;
import android.view.View;
import android.util.Log;

import java.lang.String;

public class MenuActivity extends Activity {

    private static final String TAG = "MenuActivity";

    Button playButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //this.requestWindowFeature(Window.FEATURE_NO_TITLE); // remove title bar
        setContentView(R.layout.activity_menu);

        playButton = (Button) findViewById(R.id.playButton);
        playButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d(TAG, "playButton");
                Intent myIntent = new Intent(MenuActivity.this, GameActivity.class);
                MenuActivity.this.startActivity(myIntent);
                finish();
            }
        });
    }

    /*@Override
    protected void onDestroy() {
        super.onDestroy();
        Intent intent = new Intent(this, GameActivity.class);
        finish();
    }*/

}
