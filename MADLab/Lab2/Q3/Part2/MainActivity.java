package com.example.myapplication;

import android.os.Bundle;
import android.text.TextUtils;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); // Set layout

        // Get views
        EditText inputEditText = findViewById(R.id.input);
        Button cancelButton = findViewById(R.id.button_cancel);
        Button okButton = findViewById(R.id.button_ok);

        // Cancel button clears input
        cancelButton.setOnClickListener(v -> {
            inputEditText.setText("");
            Toast.makeText(MainActivity.this, "Input cleared", Toast.LENGTH_SHORT).show();
        });

        // OK button shows input text
        okButton.setOnClickListener(v -> {
            String text = inputEditText.getText().toString().trim();
            if (TextUtils.isEmpty(text)) {
                Toast.makeText(MainActivity.this, "Please enter something", Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(MainActivity.this, "You typed: " + text, Toast.LENGTH_SHORT).show();
            }
        });
    }
}
