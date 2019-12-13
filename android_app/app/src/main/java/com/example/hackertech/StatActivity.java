package com.example.hackertech;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class StatActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stat);


        Intent i = getIntent();
        Bundle b = i.getExtras();
        String troop = (String) b.get("troop");

        Log.v("Troop number ",troop);

    }
}
