package com.tutorial.game;

import android.app.Activity;
import android.content.Intent;
import android.content.IntentSender;
import android.os.Bundle;
import android.widget.Button;
import android.view.View;
//import android.widget.TextView;

import java.lang.String;

public class GameOverActivity extends Activity {

    Button continueButton;
    //TextView scoreText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //this.requestWindowFeature(Window.FEATURE_NO_TITLE); // remove title bar
        setContentView(R.layout.activity_gameover);

        continueButton = (Button) findViewById(R.id.continueButton);
        continueButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(GameOverActivity.this, MenuActivity.class);
                GameOverActivity.this.startActivity(myIntent);
            }
        });

        //scoreText = (TextView) findViewById(R.id.scoreText);
        //scoreText.setText(getIntent().getExtras().getString("SCORE", "0"));
    }
}

