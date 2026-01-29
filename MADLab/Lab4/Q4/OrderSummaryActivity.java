package com.example.foodorderingapp;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class OrderSummaryActivity extends AppCompatActivity {

    TextView tvOrderSummary;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_order_summary);

        tvOrderSummary = findViewById(R.id.tvOrderSummary);

        String order = getIntent().getStringExtra("order");
        tvOrderSummary.setText(order);
    }
}