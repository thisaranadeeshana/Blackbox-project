package com.example.relatimedatabase;


import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.example.relatimedatabase.databinding.ActivityReadDataBinding;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;


public class ReadData extends AppCompatActivity {

    ActivityReadDataBinding binding;
    DatabaseReference reference;
    Button ab;

    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityReadDataBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        ab = findViewById(R.id.basic);
        ab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                    readData();
            }
        });



    }

    private void readData() {

        String username = "machineA" ;
        reference = FirebaseDatabase.getInstance().getReference("SLTFactoryA");

        reference.child(username).get().addOnCompleteListener(new OnCompleteListener<DataSnapshot>() {
            @Override
            public void onComplete(@NonNull Task<DataSnapshot> task) {

                if (task.isSuccessful()){

                    if (task.getResult().exists()){

                        Toast.makeText(ReadData.this,"Successfully Read",Toast.LENGTH_SHORT).show();
                        DataSnapshot dataSnapshot = task.getResult();
                        String Temperature = String.valueOf(dataSnapshot.child("Heat").getValue());
                        String Spindle_speed = String.valueOf(dataSnapshot.child("RPM").getValue());
                        String Vibration = String.valueOf(dataSnapshot.child("Torque").getValue());
                        binding.Temperaturev.setText(Temperature);
                        binding.Spindle.setText(Spindle_speed);
                        binding.Vibrationv.setText(Vibration);


                    }else {

                        Toast.makeText(ReadData.this,"User Doesn't Exist",Toast.LENGTH_SHORT).show();

                    }


                }else {

                    Toast.makeText(ReadData.this,"Failed to read",Toast.LENGTH_SHORT).show();
                }

            }
        });

    }
}