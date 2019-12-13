package com.example.hackertech;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {


    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference squad = database.getReference();
    TextView heartrate1,temprature1,id1;
    TextView heartrate2,temprature2,id2;
    FrameLayout frameLayout1,frameLayout2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        heartrate1=findViewById(R.id.heartrate1);
        temprature1=findViewById(R.id.temprature1);
        id1=findViewById(R.id.sol_id1);
        heartrate2=findViewById(R.id.heartrate2);
        temprature2=findViewById(R.id.temprature2);
        id2=findViewById(R.id.sol_id2);
        frameLayout1=findViewById(R.id.sol1);
        frameLayout2=findViewById(R.id.sol2);
        soldier_stats1();
        soldier_stats2();
        troop_click();


    }


    public void troop_click(){

        frameLayout1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent=new Intent(MainActivity.this, StatActivity.class);
                intent.putExtra("troop","1");
                startActivity(intent);
            }
        });
        frameLayout2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent=new Intent(MainActivity.this, StatActivity.class);
                intent.putExtra("troop","2");
                startActivity(intent);
            }
        });

    }


    public void soldier_stats1(){


        squad.child("soldier1").child("bv").child("hr").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - Heart Rate",String.valueOf(dataSnapshot.getValue()));
                heartrate1.setText(String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        squad.child("soldier1").child("bv").child("temp").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - Temperature",String.valueOf(dataSnapshot.getValue()));
                temprature1.setText(String.valueOf(dataSnapshot.getValue())+(char) 0x00B0+"F");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        squad.child("soldier1").child("gps").child("latitude").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - Latitude",String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });


        squad.child("soldier1").child("gps").child("longitude").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - Longitude",String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        squad.child("soldier1").child("id").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - ID",String.valueOf(dataSnapshot.getValue()));
                id1.setText("Troop ID: "+String.valueOf(dataSnapshot.getValue()));

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        squad.child("soldier1").child("sos").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - SOS",String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });





    }
    public void soldier_stats2(){


        squad.child("soldier2").child("bv").child("hr").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - Heart Rate",String.valueOf(dataSnapshot.getValue()));
                heartrate2.setText(String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        squad.child("soldier2").child("bv").child("temp").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - Temperature",String.valueOf(dataSnapshot.getValue()));
                temprature2.setText(String.valueOf(dataSnapshot.getValue())+(char) 0x00B0+"F");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        squad.child("soldier2").child("gps").child("latitude").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - Latitude",String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });


        squad.child("soldier2").child("gps").child("longitude").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - Longitude",String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        squad.child("soldier2").child("id").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - ID",String.valueOf(dataSnapshot.getValue()));
                id2.setText("Troop ID: "+String.valueOf(dataSnapshot.getValue()));

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        squad.child("soldier2").child("sos").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Log.v("Soldier Stats - SOS",String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });





    }

}
