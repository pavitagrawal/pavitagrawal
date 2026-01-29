package com.example.foodorderingapp;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.CheckBox;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    CheckBox cbPizza, cbBurger, cbPasta;
    Button btnSubmit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        cbPizza = findViewById(R.id.cbPizza);
        cbBurger = findViewById(R.id.cbBurger);
        cbPasta = findViewById(R.id.cbPasta);
        btnSubmit = findViewById(R.id.btnSubmit);

        btnSubmit.setOnClickListener(v -> {

            StringBuilder orderDetails = new StringBuilder();
            int totalCost = 0;

            if (cbPizza.isChecked()) {
                orderDetails.append("Pizza - ₹200\n");
                totalCost += 200;
            }

            if (cbBurger.isChecked()) {
                orderDetails.append("Burger - ₹120\n");
                totalCost += 120;
            }

            if (cbPasta.isChecked()) {
                orderDetails.append("Pasta - ₹150\n");
                totalCost += 150;
            }

            orderDetails.append("\nTotal Cost: ₹").append(totalCost);

            // Disable checkboxes after submit
            cbPizza.setEnabled(false);
            cbBurger.setEnabled(false);
            cbPasta.setEnabled(false);
            btnSubmit.setEnabled(false);

            // Send data to next activity
            Intent intent = new Intent(MainActivity.this, OrderSummaryActivity.class);
            intent.putExtra("order", orderDetails.toString());
            startActivity(intent);
        });
    }
}
