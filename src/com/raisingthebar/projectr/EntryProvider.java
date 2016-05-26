package com.raisingthebar.projectr;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;

public class EntryProvider extends ContentProvider {

    static final String PROVIDER_NAME = "raisingthebar.projectr.Entry";
    static final String URL = "content://" + PROVIDER_NAME + "/" + Contract.Entry.TABLE_NAME;
    static final Uri CONTENT_URI = Uri.parse(URL);

    private DBHelper dbHelper;
    private SQLiteDatabase db;

    private static final int ENTRIES = 1;
    private static final int ENTRY_ID = 2;

    private static final UriMatcher uriMatcher = getUriMatcher();
    private static UriMatcher getUriMatcher() {
        UriMatcher uriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
        uriMatcher.addURI(PROVIDER_NAME, Contract.Entry.TABLE_NAME, ENTRIES);
        uriMatcher.addURI(PROVIDER_NAME, Contract.Entry.TABLE_NAME + "/#", ENTRY_ID);
        return uriMatcher;
    }

    @Override
    public boolean onCreate() {
        dbHelper = new DBHelper(getContext());
        db = dbHelper.getWritableDatabase();
        return true;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
        String id = null;
        if(uriMatcher.match(uri) == ENTRY_ID) {
            //Query is for one single entry. Get the ID from the URI.
            id = uri.getPathSegments().get(1);
        }
        return dbHelper.getEntries(id, projection, selection, selectionArgs, sortOrder);
    }

    @Override
    public String getType(Uri uri) {
        switch (uriMatcher.match(uri)) {
            case ENTRIES:
                return "vnd.android.cursor.dir/vnd." + PROVIDER_NAME + "." + Contract.Entry.TABLE_NAME;
            case ENTRY_ID:
                return "vnd.android.cursor.item/vnd." + PROVIDER_NAME + "." + Contract.Entry.TABLE_NAME;

        }
        return "";
    }

    @Override
    public Uri insert(Uri uri, ContentValues contentValues) {
        /*db.insert(Contract.Entry.TABLE_NAME, Contract.Entry.COL_NAME_NULLABLE, contentValues);
        return null;*/

        try {
            long id = dbHelper.addEntry(contentValues);
            return ContentUris.withAppendedId(CONTENT_URI, id);
        } catch(Exception e) {
            return null;
        }
    }

    @Override
    public int delete(Uri uri, String s, String[] strings) {
        return 0;
    }

    @Override
    public int update(Uri uri, ContentValues contentValues, String s, String[] strings) {
        return 0;
    }
}
