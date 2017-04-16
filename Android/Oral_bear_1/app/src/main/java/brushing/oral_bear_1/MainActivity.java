package brushing.oral_bear_1;

import android.support.annotation.NonNull;
import android.support.design.widget.NavigationView;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.TextView;
import android.widget.TimePicker;

import java.text.DateFormat;
import java.util.Calendar;



public class MainActivity extends AppCompatActivity {

    DateFormat formatDateTime = DateFormat.getDateTimeInstance();
    Calendar dateTime = Calendar.getInstance();
    private TextView text;
    private Button btn_date;
    private Button btn_time;
    DrawerLayout drawerLayout;

    //create variable for the toolbar
    Toolbar toolbar;
    //create var for action bar
    ActionBarDrawerToggle actionBarDrawerToggle;
    //display first frag play music
    FragmentTransaction fragmentTransaction;

    //variable for navigation view
    NavigationView navigationView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //initalise toolbar variable
        toolbar=(Toolbar)findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        drawerLayout =(DrawerLayout)findViewById(R.id.drawer_layout);

        actionBarDrawerToggle = new ActionBarDrawerToggle(this,drawerLayout,toolbar,R.string.drawer_open,R.string.drawer_close);
        //drawer listener
        drawerLayout.addDrawerListener(actionBarDrawerToggle);
        //we need to override onpost method with one arg object of bundle

        //display music frag
        //initialise frag tran
        fragmentTransaction = getSupportFragmentManager().beginTransaction();

        //add frag to container
        fragmentTransaction.add(R.id.main_container,new MusicFragment());
        fragmentTransaction.commit();

        //change title of tool bar to music frag when app is opened default page
        getSupportActionBar().setTitle("Play Music");

        //init nav view
        navigationView =(NavigationView) findViewById(R.id.navigation_view);
        //create click listener for nav view
        navigationView.setNavigationItemSelectedListener(new NavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                //get id of menu item
                //create switc statement
                switch (item.getItemId())
                {
                    //now we have to analyse each case
                    case R.id.music_id:
                        //we have to display music frag
                        fragmentTransaction = getSupportFragmentManager().beginTransaction();
                        //replace() becoz we need to put this frag in the container
                        fragmentTransaction.replace(R.id.main_container,new MusicFragment());
                        fragmentTransaction.commit();

                        //change title of tool bar
                        getSupportActionBar().setTitle("Play Music");
                        item.setChecked(true);
                        drawerLayout.closeDrawers();
                        break;

                    case R.id.reminder_id:
                        //we have to display music frag
                        fragmentTransaction = getSupportFragmentManager().beginTransaction();
                        //replace() becoz we need to put this frag in the container
                        fragmentTransaction.replace(R.id.main_container,new ReminderFragment());
                        fragmentTransaction.commit();

                        //change title of tool bar
                        getSupportActionBar().setTitle("Daily Reminder");
                        item.setChecked(true);
                        drawerLayout.closeDrawers();
                        break;

                    case R.id.tutorial_id:
                        //we have to display music frag
                        fragmentTransaction = getSupportFragmentManager().beginTransaction();
                        //replace() becoz we need to put this frag in the container
                        fragmentTransaction.replace(R.id.main_container,new TutorialFragment());
                        fragmentTransaction.commit();

                        //change title of tool bar
                        getSupportActionBar().setTitle("Watch Tutorials");
                        item.setChecked(true);
                        drawerLayout.closeDrawers();
                        break;

                }
                return true;
            }
        });

        text = (TextView) findViewById(R.id.txt_TextDateTime);
        btn_date = (Button) findViewById(R.id.btn_datePicker);
        btn_time = (Button) findViewById(R.id.btn_timePicker);

        btn_date.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateDate();
            }
        });

        btn_time.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateTime();
            }
        });

        updateTextLabel();


    }

    private void updateDate(){
        new DatePickerDialog(this, d, dateTime.get(Calendar.YEAR),dateTime.get(Calendar.MONTH),dateTime.get(Calendar.DAY_OF_MONTH)).show();
    }

    private void updateTime(){
        new TimePickerDialog(this, t, dateTime.get(Calendar.HOUR_OF_DAY), dateTime.get(Calendar.MINUTE), true).show();
    }

    DatePickerDialog.OnDateSetListener d = new DatePickerDialog.OnDateSetListener() {
        @Override
        public void onDateSet(DatePicker view, int year, int monthOfYear, int dayOfMonth) {
            dateTime.set(Calendar.YEAR, year);
            dateTime.set(Calendar.MONTH, monthOfYear);
            dateTime.set(Calendar.DAY_OF_MONTH, dayOfMonth);
            updateTextLabel();
        }
    };

    TimePickerDialog.OnTimeSetListener t = new TimePickerDialog.OnTimeSetListener() {
        @Override
        public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
            dateTime.set(Calendar.HOUR_OF_DAY, hourOfDay);
            dateTime.set(Calendar.MINUTE, minute);
            updateTextLabel();
        }
    };

    private void updateTextLabel(){
        text.setText(formatDateTime.format(dateTime.getTime()));
    }


    @Override

    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
        //from this method u have to sync the action bar toggle
        actionBarDrawerToggle.syncState();
        //hamburger icon
    }




}
