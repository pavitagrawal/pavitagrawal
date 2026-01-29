package com.example.testapp;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    Button btnClick;
    ToggleButton toggleButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnClick = findViewById(R.id.btnClick);
        toggleButton = findViewById(R.id.toggleButton);

        // Normal Button click
        btnClick.setOnClickListener(v ->
                showCustomToast("Button Clicked", R.drawable.button_img)
        );

        // ToggleButton click
        toggleButton.setOnClickListener(v -> {
            if (toggleButton.isChecked()) {
                showCustomToast("Toggle ON", R.drawable.toggle_on);
            } else {
                showCustomToast("Toggle OFF", R.drawable.toggle_off);
            }
        });
    }

    private void showCustomToast(String message, int imageRes) {

        LayoutInflater inflater = getLayoutInflater();
        View view = inflater.inflate(R.layout.toast_layout, null);

        ImageView imageView = view.findViewById(R.id.toastImage);
        TextView textView = view.findViewById(R.id.toastText);

        imageView.setImageResource(imageRes);
        textView.setText(message);

        Toast toast = new Toast(getApplicationContext());
        toast.setDuration(Toast.LENGTH_SHORT);
        toast.setView(view);
        toast.show();
    }
}
