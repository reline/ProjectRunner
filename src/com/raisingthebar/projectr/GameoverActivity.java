package com.raisingthebar.projectr;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.widget.Button;

public class GameoverActivity extends Activity {

    private static final String TAG = "GameoverActivity";
    private Button continueButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gameover);

        continueButton = (Button) findViewById(R.id.continueButton);
        continueButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent myIntent = new Intent(GameoverActivity.this, GameActivity.class);
                GameoverActivity.this.startActivity(myIntent);
                //myIntent = new Intent(GameoverActivity.this, GameActivity.class);
                //GameoverActivity.this.startActivity(myIntent);
            }
        });

        // TODO: display the score and save to the database along with a username that the user enters here

    }
}

