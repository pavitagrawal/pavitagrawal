package com.example.myapplication;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.GridView;
import android.widget.ListView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.PagerAdapter;
import androidx.viewpager.widget.ViewPager;

import com.google.android.material.tabs.TabLayout;

public class MainActivity extends AppCompatActivity {

    ViewPager viewPager;
    TabLayout tabLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tabLayout = findViewById(R.id.tabLayout);
        viewPager = findViewById(R.id.viewPager);

        // Set adapter
        viewPager.setAdapter(new MyPagerAdapter(this));
        tabLayout.setupWithViewPager(viewPager);
    }

    // 🔹 INNER PAGER ADAPTER CLASS
    private class MyPagerAdapter extends PagerAdapter {

        Context context;
        int[] layouts = {
                R.layout.tab_list,
                R.layout.tab_grid,
                R.layout.tab_table
        };

        MyPagerAdapter(Context context) {
            this.context = context;
        }

        @Override
        public int getCount() {
            return layouts.length;
        }

        @Override
        public boolean isViewFromObject(View view, Object object) {
            return view == object;
        }
        @Override
        public CharSequence getPageTitle(int position) {
            switch (position) {
                case 0: return "ListView";
                case 1: return "GridView";
                case 2: return "TableLayout";
                default: return "";
            }
        }

        @Override
        public Object instantiateItem(ViewGroup container, int position) {
            LayoutInflater inflater = LayoutInflater.from(context);
            View view = inflater.inflate(layouts[position], container, false);

            // Setup ListView
            if (position == 0) {
                ListView listView = view.findViewById(R.id.listView);
                String[] countries = {
                        "American Samoa",
                        "El Salvador",
                        "Saint Helena",
                        "Saint Lucia",
                        "Samoa",
                        "San Marino"
                };
                ArrayAdapter<String> adapter =
                        new ArrayAdapter<>(context,
                                android.R.layout.simple_list_item_1, countries);
                listView.setAdapter(adapter);
            }

            // Setup GridView
            if (position == 1) {
                GridView gridView = view.findViewById(R.id.gridView);
                String[] animals = {
                        "Dog", "Cat", "Tiger",
                        "Lion", "Horse", "Fox"
                };
                ArrayAdapter<String> adapter =
                        new ArrayAdapter<>(context,
                                android.R.layout.simple_list_item_1, animals);
                gridView.setAdapter(adapter);
            }

            container.addView(view);
            return view;
        }

        @Override
        public void destroyItem(ViewGroup container, int position, Object object) {
            container.removeView((View) object);
        }
    }
}
