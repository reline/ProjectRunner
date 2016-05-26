package com.raisingthebar.projectr;

import android.provider.BaseColumns;

public class Contract {

    public Contract() {

    }

    public static abstract class Entry implements BaseColumns {
        public static final String TABLE_NAME = "Entry";
        public static final String COL_NAME_NULLABLE = "Nullable";
        public static final String COL_NAME_USERNAME = "Username";
        public static final String COL_NAME_SCORE = "Score";
        public static final String COL_NAME_DATE = "Date";
    }
}
