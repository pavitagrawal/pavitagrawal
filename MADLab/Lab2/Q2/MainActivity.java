package com.example.myapplication;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    EditText n1, n2;
    TextView resultText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        n1 = findViewById(R.id.num1);
        n2 = findViewById(R.id.num2);
        resultText = findViewById(R.id.resultText);
    }

    public void add(View v) {
        calculate("+");
    }

    public void sub(View v) {
        calculate("-");
    }

    public void mul(View v) {
        calculate("*");
    }

    public void div(View v) {
        calculate("/");
    }

    private void calculate(String op) {

        int a = Integer.parseInt(n1.getText().toString());
        int b = Integer.parseInt(n2.getText().toString());
        int res = 0;

        switch (op) {
            case "+":
                res = a + b;
                break;
            case "-":
                res = a - b;
                break;
            case "*":
                res = a * b;
                break;
            case "/":
                res = a / b;
                break;
        }

        String output = a + " " + op + " " + b + " = " + res;
        resultText.setText(output);
    }
}
