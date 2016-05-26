package com.raisingthebar.projectr;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteQueryBuilder;

public class DBHelper extends SQLiteOpenHelper {

    public static final int DATABASE_VERSION = 1;
    public static final String DATABASE_NAME = "ProjectR";

    private static final String TEXT_TYPE = " TEXT"; // The value is a text string, stored using the database encoding (UTF-8, UTF-16BE or UTF-16LE).
    private static final String INT_TYPE = " INTEGER"; // The value is a signed integer, stored in 1, 2, 3, 4, 6, or 8 bytes depending on the magnitude of the value.
    private static final String REAL_TYPE = " REAL"; // The value is a floating point value, stored as an 8-byte IEEE floating point number.
    private static final String BLOB_TYPE = " BLOB"; // The value is a blob of data, stored exactly as it was input.
    private static final String COMMA_SEP = ",";
    // TODO: 5/24/2016 add datetime column
    private static final String SQL_CREATE_ENTRIES =
            "CREATE TABLE IF NOT EXISTS " + Contract.Entry.TABLE_NAME + " (" +
                    Contract.Entry._ID + " INTEGER PRIMARY KEY," +
                    Contract.Entry.COL_NAME_USERNAME + TEXT_TYPE + COMMA_SEP +
                    Contract.Entry.COL_NAME_SCORE + INT_TYPE + COMMA_SEP +
                    Contract.Entry.COL_NAME_DATE + TEXT_TYPE +
            " )";

    private static final String SQL_DELETE_ENTRIES =
            "DROP TABLE IF EXISTS " + Contract.Entry.TABLE_NAME;

    public DBHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        sqLiteDatabase.execSQL(SQL_CREATE_ENTRIES);
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {
        sqLiteDatabase.execSQL(SQL_DELETE_ENTRIES);
        onCreate(sqLiteDatabase);
    }

    @Override
    public void onDowngrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {

    }

    public Cursor getEntries(String id, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
        SQLiteQueryBuilder sqliteQueryBuilder = new SQLiteQueryBuilder();
        sqliteQueryBuilder.setTables(Contract.Entry.TABLE_NAME);

        if(id != null) {
            sqliteQueryBuilder.appendWhere("_id" + " = " + id);
        }

        if (projection == null) {
            projection = new String[] {
                    Contract.Entry._ID,
                    Contract.Entry.COL_NAME_USERNAME,
                    Contract.Entry.COL_NAME_SCORE,
                    Contract.Entry.COL_NAME_DATE
            };
        }

        // how you want the results sorted in the resulting Cursor
        if (sortOrder == null) {
            sortOrder = Contract.Entry.COL_NAME_SCORE + " DESC";
        }

        return sqliteQueryBuilder.query(getReadableDatabase(),
                projection,
                selection,
                selectionArgs,
                null,
                null,
                sortOrder);
    }

    public long addEntry(ContentValues values) {
        long id = getWritableDatabase().insert(Contract.Entry.TABLE_NAME, Contract.Entry.COL_NAME_NULLABLE, values);
        if(id <=0 ) {
            throw new SQLException("Failed to add an entry");
        }
        return id;
    }
}
