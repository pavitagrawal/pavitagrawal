package com.example.myapplication;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.button.MaterialButton;
import com.google.android.material.textfield.TextInputEditText;

public class MainActivity extends AppCompatActivity {

    TextInputEditText etUsername, etPassword;
    MaterialButton btnLogin;
    TextView tvMessage;

    Toast toast; // <-- prevent toast spam

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        etUsername = findViewById(R.id.etUsername);
        etPassword = findViewById(R.id.etPassword);
        btnLogin = findViewById(R.id.btnLogin);
        tvMessage = findViewById(R.id.tvMessage);

        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // Disable button briefly to prevent multiple clicks
                btnLogin.setEnabled(false);
                btnLogin.postDelayed(() -> btnLogin.setEnabled(true), 1200);

                String username = etUsername.getText().toString().trim();
                String password = etPassword.getText().toString().trim();

                // Clear old message
                tvMessage.setText("");

                if (username.isEmpty() || password.isEmpty()) {
                    tvMessage.setText("Please fill all fields");
                }
                else if (username.equals("admin") && password.equals("1234")) {
                    tvMessage.setText("Login Successful");

                    // Cancel old toast if exists
                    if (toast != null) toast.cancel();

                    toast = Toast.makeText(
                            MainActivity.this,
                            "Welcome " + username,
                            Toast.LENGTH_SHORT
                    );
                    toast.show();
                }
                else {
                    tvMessage.setText("Invalid Username or Password");
                }
            }
        });
    }
}
