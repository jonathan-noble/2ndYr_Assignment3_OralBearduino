package ie.dit;

/**
 * Created by Butan on 03/04/2017.
 * buttons/background color created by pia
 */

//import android.content.SharedPreferences;
//import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
//import android.media.AudioManager;
//import android.media.MediaPlayer;



public class MainActivity extends AppCompatActivity {

   // MediaPlayer mySound;
   //  SharedPreferences sharedPref;
    View view;

    //created object for color picker buttons
    private Button redBtn, blueBtn, yellowBtn;
    @Override

    //its like void setup()--stndrd default
    protected void onCreate(Bundle savedInstanceState) {
        //i think calling all methods on savedinstances
        super.onCreate(savedInstanceState);
        //calling layout
        setContentView(R.layout.activity_main);

       // sharedPref= PreferenceManager.getDefaultSharedPreferences(this);

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
    }

//code so when button is clicked these methods will be executed
    private void onButtonClick(int color){
        Intent intent = new Intent(this, AudioActivity.class);
        intent.putExtra("background",color);
        startActivity(intent);
    }


    public void ListenAudio(View v) {

        startActivity(new Intent(this, AudioActivity.class));
    }

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
        return super.onOptionsItemSelected(item);
    }




//        mySound = MediaPlayer.create(this, R.raw.shooting_stars);
//
//         Button play = (Button) findViewbyId(R.id.button_play);
////         Button pause = (Button) findViewbyId(R.id.button_pause);
////         Button stop = (Button) findViewbyId(R.id.button_stop);

//
//    public void playMusic(View view) {
//    mySound.start();
//    }
}

