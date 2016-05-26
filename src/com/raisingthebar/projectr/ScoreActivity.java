package com.raisingthebar.projectr;

import android.app.ListActivity;
import android.content.CursorLoader;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CursorAdapter;
import android.widget.SimpleCursorAdapter;

public class ScoreActivity extends ListActivity {

    private static final String TAG = "ScoreActivity";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_score);

        Button continueButton = (Button) findViewById(R.id.contButton);
        continueButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent myIntent = new Intent(ScoreActivity.this, GameActivity.class);
                ScoreActivity.this.startActivity(myIntent);
            }
        });

        selectEntries();
    }

    public void selectEntries() {
        // define a projection that specifies which columns from the db you will use after this query
        String[] projection = {
                Contract.Entry.COL_NAME_USERNAME,
                Contract.Entry.COL_NAME_SCORE,
                Contract.Entry.COL_NAME_DATE
        };

        // how you want the results sorted in the resulting Cursor
        String sortOrder = Contract.Entry.COL_NAME_SCORE + " DESC";

        SimpleCursorAdapter simpleCursorAdapter = new SimpleCursorAdapter(
                getBaseContext(),
                R.layout.list_layout,
                null,
                projection,
                new int[]{ R.id.name, R.id.score, R.id.date},
                CursorAdapter.FLAG_REGISTER_CONTENT_OBSERVER
        );
        setListAdapter(simpleCursorAdapter);

        CursorLoader cursorLoader = new CursorLoader(
                getBaseContext(),
                EntryProvider.CONTENT_URI,
                null,
                null,
                null,
                sortOrder
        );
        Cursor cursor = cursorLoader.loadInBackground();
        simpleCursorAdapter.swapCursor(cursor);
    }
}
