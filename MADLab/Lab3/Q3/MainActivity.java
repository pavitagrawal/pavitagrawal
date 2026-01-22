package com.example.newsapp;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.viewpager2.adapter.FragmentStateAdapter;
import androidx.viewpager2.widget.ViewPager2;

import com.google.android.material.tabs.TabLayout;
import com.google.android.material.tabs.TabLayoutMediator;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TabLayout tabLayout = findViewById(R.id.tabLayout);
        ViewPager2 viewPager = findViewById(R.id.viewPager);

        ViewPagerAdapter adapter = new ViewPagerAdapter(this);
        viewPager.setAdapter(adapter);

        new TabLayoutMediator(tabLayout, viewPager,
                (tab, position) -> {
                    switch (position) {
                        case 0:
                            tab.setText("Top Stories");
                            break;
                        case 1:
                            tab.setText("Sports");
                            break;
                        case 2:
                            tab.setText("Entertainment");
                            break;
                    }
                }
        ).attach();
    }

    // -------------------------------
    // ViewPager Adapter (Merged)
    // -------------------------------
    class ViewPagerAdapter extends FragmentStateAdapter {

        public ViewPagerAdapter(@NonNull AppCompatActivity activity) {
            super(activity);
        }

        @NonNull
        @Override
        public Fragment createFragment(int position) {
            switch (position) {
                case 0:
                    return NewsFragment.newInstance(
                            "Top Stories",
                            "Latest breaking news from around the world."
                    );
                case 1:
                    return NewsFragment.newInstance(
                            "Sports",
                            "Live scores, match highlights, and sports updates."
                    );
                case 2:
                    return NewsFragment.newInstance(
                            "Entertainment",
                            "Movies, celebrities, music, and TV news."
                    );
                default:
                    return new Fragment();
            }
        }

        @Override
        public int getItemCount() {
            return 3;
        }
    }

    // -------------------------------
    // News Fragment (Merged)
    // -------------------------------
    public static class NewsFragment extends Fragment {

        private static final String ARG_TITLE = "title";
        private static final String ARG_CONTENT = "content";

        public static NewsFragment newInstance(String title, String content) {
            NewsFragment fragment = new NewsFragment();
            Bundle args = new Bundle();
            args.putString(ARG_TITLE, title);
            args.putString(ARG_CONTENT, content);
            fragment.setArguments(args);
            return fragment;
        }

        @Nullable
        @Override
        public View onCreateView(
                @NonNull LayoutInflater inflater,
                @Nullable ViewGroup container,
                @Nullable Bundle savedInstanceState) {

            View view = inflater.inflate(R.layout.fragment_news, container, false);

            TextView titleText = view.findViewById(R.id.sectionTitle);
            TextView contentText = view.findViewById(R.id.sectionContent);

            if (getArguments() != null) {
                titleText.setText(getArguments().getString(ARG_TITLE));
                contentText.setText(getArguments().getString(ARG_CONTENT));
            }

            return view;
        }
    }
}
