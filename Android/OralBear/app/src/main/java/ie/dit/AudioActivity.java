package ie.dit;

/**
 * Created by Butan on 03/04/2017.
 */


import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.media.MediaPlayer;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;



public class AudioActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio);
    }

    public void PlayAudio(View v) {
        MediaPlayer player = MediaPlayer.create(this, R.raw.shooting_stars);
        player.start();
    }


}
