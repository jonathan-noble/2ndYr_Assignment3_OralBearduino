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
//import android.media.AudioManager;
//import android.media.MediaPlayer;



public class MainActivity extends AppCompatActivity {

   // MediaPlayer mySound;
   //  SharedPreferences sharedPref;
    View view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        view=this.getWindow().getDecorView();
        view.setBackgroundResource(R.color.gray);

       // sharedPref= PreferenceManager.getDefaultSharedPreferences(this);

    }

//code so when button is clicked these methods will be executed
    public void goRED(View v)
    {

        view.setBackgroundResource(R.color.red);
        Intent intent = new Intent(this, AudioActivity.class);
        intent.putExtra("Red", R.color.red);
        startActivity(intent);
    }

    public void goBLUE(View v)
    {

        view.setBackgroundResource(R.color.blue);
//        Intent intent = new Intent(this, AudioActivity.class);
//        intent.putExtra("Blue", R.color.blue);
//        startActivity(intent);
    }

    public void goYELLOW(View v)
    {
        view.setBackgroundResource(R.color.yellow);
//        Intent intent = new Intent(this, AudioActivity.class);
//        intent.putExtra("Yellow", R.color.yellow);
//        startActivity(intent);
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

