package com.raisingthebar.projectr;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class GameoverActivity extends Activity {

    private static final String TAG = "GameoverActivity";

    private DBHelper dbHelper;
    private SQLiteDatabase db;

    private TextView scoreTextView;
    private EditText nameEditText;
    private Button continueButton;

    private int score = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gameover);

        dbHelper = new DBHelper(getApplicationContext());
        // gets the data repository in write mode
        db = dbHelper.getWritableDatabase();

        Intent intent = getIntent();
        score = intent.getIntExtra("SCORE", 0);

        scoreTextView = (TextView) findViewById(R.id.scoreTextView);
        scoreTextView.setText("Score: " + Integer.toString(score));

        nameEditText = (EditText) findViewById(R.id.nameTextView);
        nameEditText.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View view, boolean hasFocus) {
                if (hasFocus) {
                    if (nameEditText.getText().length() >= 3) {
                        nameEditText.setError(null);
                    }
                }
            }
        });

        continueButton = (Button) findViewById(R.id.continueButton);
        continueButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (nameEditText.getText().length() < 3) {
                    nameEditText.setError("Enter three characters");
                } else {
                    nameEditText.setError(null);

                    insertEntry();

                    Intent myIntent = new Intent(GameoverActivity.this, ScoreActivity.class);
                    GameoverActivity.this.startActivity(myIntent);
                    finish();
                }
            }
        });
    }

    public void insertEntry() {
        // create a new map of values, where column names are the keys
        ContentValues values = new ContentValues();
        values.put(Contract.Entry.COL_NAME_USERNAME, nameEditText.getText().toString());
        values.put(Contract.Entry.COL_NAME_SCORE, score);
        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss", Locale.US);
        values.put(Contract.Entry.COL_NAME_DATE, dateFormat.format(new Date()));

        getContentResolver().insert(EntryProvider.CONTENT_URI, values);
    }
}

