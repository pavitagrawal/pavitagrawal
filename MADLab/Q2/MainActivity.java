package com.example.myapplication;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.activity.EdgeToEdge;

public class MainActivity extends AppCompatActivity {

    // Tag for logging
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Enable EdgeToEdge for modern Android devices
        EdgeToEdge.enable(this);

        // Set the layout
        setContentView(R.layout.activity_main);

        // Adjust padding for system bars (status & navigation)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        // ---- Link your views ----
        EditText etUsername = findViewById(R.id.etUsername);
        EditText etPassword = findViewById(R.id.etPassword);

        Button btnLogin = findViewById(R.id.btnLogin);
        Button btnClear = findViewById(R.id.btnClear);

        // ---- Login button click ----
        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String username = etUsername.getText().toString();
                String password = etPassword.getText().toString();

                // Show Toast
                Toast.makeText(MainActivity.this,
                        "Login clicked\nUsername: " + username + "\nPassword: " + password,
                        Toast.LENGTH_SHORT).show();

                // ---- Logcat output ----
                Log.d(TAG, "Login button clicked");
                Log.d(TAG, "Username: " + username);
                Log.d(TAG, "Password: " + password);
            }
        });

        // ---- Clear button click ----
        btnClear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                etUsername.setText("");
                etPassword.setText("");

                // Show Toast
                Toast.makeText(MainActivity.this,
                        "Cleared!", Toast.LENGTH_SHORT).show();

                // ---- Logcat output ----
                Log.d(TAG, "Clear button clicked, fields cleared");
            }
        });
    }
}
