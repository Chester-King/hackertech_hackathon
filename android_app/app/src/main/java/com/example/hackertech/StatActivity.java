package com.example.hackertech;

import androidx.annotation.ColorInt;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.airbnb.lottie.LottieAnimationView;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class StatActivity extends AppCompatActivity {

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference squad = database.getReference();
    DatabaseReference troopRef;
    TextView heartrate,temprature,latitude,longitude,sos;
    String sos_state;
    LottieAnimationView danger,map;
    String lat,lon;

    LinearLayout sos_layout;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stat);


        Intent i = getIntent();
        Bundle b = i.getExtras();
        String troop = "soldier"+(String) b.get("troop");

        sos_layout=findViewById(R.id.sos_layout);
        danger=findViewById(R.id.assist);
        heartrate=findViewById(R.id.heartrate);
        temprature=findViewById(R.id.temprature);
        latitude=findViewById(R.id.latitude);
        longitude=findViewById(R.id.longitude);
        sos=findViewById(R.id.sos);
        map=findViewById(R.id.locate);



        Log.v("Troop number ",troop);
        troopRef=squad.child(troop);

        troopRef.child("bv").child("hr").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                heartrate.setText(String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        troopRef.child("bv").child("temp").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                temprature.setText(String.valueOf(dataSnapshot.getValue())+(char) 0x00B0+"C");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        troopRef.child("gps").child("latitude").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                lat=String.valueOf(dataSnapshot.getValue());
                latitude.setText("Latitude : "+String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        troopRef.child("gps").child("longitude").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                lon=String.valueOf(dataSnapshot.getValue());
                longitude.setText("Longitude : "+String.valueOf(dataSnapshot.getValue()));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        troopRef.child("sos").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                sos_state=String.valueOf(dataSnapshot.getValue());
                if(sos_state.equalsIgnoreCase("Yes")){

                    sos_layout.setVisibility(View.VISIBLE);
                    sos.setVisibility(View.GONE);
                    danger.setVisibility(View.VISIBLE);

                }
                if(sos_state.equalsIgnoreCase("No")){


                    sos_layout.setVisibility(View.GONE);
                }

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });


        map.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("geo:"+lat+","+lon+"?q="+lat+","+lon+"(Troop+"+troop+")"));
                startActivity(intent);
            }
        });


    }
}
