package ie.dit;

/**
 * Created by Butan on 03/04/2017.
 * buttons/background color created by pia
 */

import android.support.design.widget.NavigationView;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;



public class MainActivity extends AppCompatActivity {

    // MediaPlayer mySound;
    //  SharedPreferences sharedPref;

    //created object for color picker buttons
    private Button redBtn, blueBtn, yellowBtn;
    private DrawerLayout mDrawerLayout;
    private ActionBarDrawerToggle mToggle;

    //initialise fragment variables



    //private Toolbar mToolbar;


     //its like void setup()--stndrd default
     @Override
    protected void onCreate(Bundle savedInstanceState) {
        //i think calling all methods on savedinstances
        super.onCreate(savedInstanceState);
        //calling layout
        setContentView(R.layout.activity_main);

         //initialised buttons
         redBtn = (Button) findViewById(R.id.button_red);
         blueBtn = (Button) findViewById(R.id.button_blue);
         yellowBtn = (Button) findViewById(R.id.button_yellow);

         redBtn.setOnClickListener(new View.OnClickListener() {
             @Override
             public void onClick(View view) {
                 onButtonClick(R.color.red);
             }
         });
         blueBtn.setOnClickListener(new View.OnClickListener() {
             @Override
             public void onClick(View view) {
                 onButtonClick(R.color.blue);
             }
         });
         yellowBtn.setOnClickListener(new View.OnClickListener() {
             @Override
             public void onClick(View view) {
                 onButtonClick(R.color.yellow);
             }
         });

         //mToolbar =(Toolbar)findViewById(R.id.nav_action);
         //setSupportActionBar(mToolbar);

         mDrawerLayout = (DrawerLayout) findViewById(R.id.drawerLayout);
         mToggle =new ActionBarDrawerToggle(this,mDrawerLayout,R.string.open,R.string.navigation_drawer_close);
         //4 param this activity,layout then 2 strings



         mDrawerLayout.addDrawerListener(mToggle);

         //fragment var to display them


         mToggle.syncState();

        //getSupportActionBar().setDisplayHomeAsUpEnabled(true);


         //change title of tool bar to whatver fragment
        // getSupportActionBar().setTitle("Reminder Fragment...");


        //getSupportActionBar().setLogo(R.drawable.Toothbrus);
        // sharedPref= PreferenceManager.getDefaultSharedPreferences(this);

    }



    //code so when button is clicked these methods will be executed
    private void onButtonClick(int color) {
        Intent intent = new Intent(this, AudioActivity.class);
        intent.putExtra("background", color);
        startActivity(intent);
    }


//    public void ListenAudio(View v) {
//
//        startActivity(new Intent(this, AudioActivity.class));
//    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }


    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;

        }

        if(mToggle.onOptionsItemSelected(item))
        {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

}

