package ie.dit;

/**
 * Created by Butan on 03/04/2017.
 */

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
//import android.view.Menu;
//import android.view.MenuItem;
//import android.media.AudioManager;
//import android.media.MediaPlayer;
//import android.button;


public class MainActivity extends AppCompatActivity {

   // MediaPlayer mySound;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    public void onAudio(View v) {

        startActivity(new Intent(this, AudioActivity.class));
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
//
//
//    @Override
//    public boolean onCreateOptionsMenu(Menu menu) {
//        //Inflate the menu; this adds items to the action bar if itis present.
//        getMenuInflater().inflate(R.menu.menu_main, menu);
//        return true;
//    }
//
//
//    @Override
//    public boolean onOptionsItemSelected(MenuItem item) {
//        int id = item.getItemId();
//
//        if (id == R.id.action_settings) {
//            return true;
//        }
//        return super.onOptionsItemSelected(item);
//    }

}

