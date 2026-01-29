package com.example.currentmodeapp;

import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;
import android.widget.ToggleButton;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    ToggleButton toggleMode;
    Button btnChangeMode;
    ImageView modeImage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        toggleMode = findViewById(R.id.toggleMode);
        btnChangeMode = findViewById(R.id.btnChangeMode);
        modeImage = findViewById(R.id.modeImage);

        // ToggleButton state change
        toggleMode.setOnClickListener(v -> updateMode());

        // Change Mode button click
        btnChangeMode.setOnClickListener(v -> {
            toggleMode.setChecked(!toggleMode.isChecked());
            updateMode();
        });
    }

    private void updateMode() {
        if (toggleMode.isChecked()) {
            modeImage.setImageResource(R.drawable.wifi);
            Toast.makeText(this, "Current Mode: Wi-Fi", Toast.LENGTH_SHORT).show();
        } else {
            modeImage.setImageResource(R.drawable.mobile_data);
            Toast.makeText(this, "Current Mode: Mobile Data", Toast.LENGTH_SHORT).show();
        }
    }
}
