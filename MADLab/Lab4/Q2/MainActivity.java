package com.example.androidversions;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    Button btnLollipop, btnMarshmallow, btnNougat;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnLollipop = findViewById(R.id.btnLollipop);
        btnMarshmallow = findViewById(R.id.btnMarshmallow);
        btnNougat = findViewById(R.id.btnNougat);

        btnLollipop.setOnClickListener(v ->
                showCustomToast("Android Lollipop", R.drawable.android_lollipop)
        );

        btnMarshmallow.setOnClickListener(v ->
                showCustomToast("Android Marshmallow", R.drawable.android_marshmallow)
        );

        btnNougat.setOnClickListener(v ->
                showCustomToast("Android Nougat", R.drawable.android_nougat)
        );
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
