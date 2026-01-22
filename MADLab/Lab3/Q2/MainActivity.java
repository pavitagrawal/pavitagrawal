package com.example.sportsactivity;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    ListView sportsListView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sportsListView = findViewById(R.id.sportsListView);

        // Sports data
        String[] sports = {
                "Cricket",
                "Football",
                "Hockey",
                "Basketball",
                "Tennis",
                "Badminton",
                "Volleyball",
                "Swimming"
        };

        // Adapter
        ArrayAdapter<String> adapter = new ArrayAdapter<>(
                this,
                android.R.layout.simple_list_item_1,
                sports
        );

        sportsListView.setAdapter(adapter);

        // Click listener
        sportsListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

                String selectedSport = sports[position];

                Toast.makeText(
                        MainActivity.this,
                        "Selected Sport: " + selectedSport,
                        Toast.LENGTH_SHORT
                ).show();
            }
        });
    }
}
