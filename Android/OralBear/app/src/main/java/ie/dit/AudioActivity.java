package ie.dit;

/**
 * Created by Butan on 03/04/2017.
 */


import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.media.MediaPlayer;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.RelativeLayout;


public class AudioActivity extends AppCompatActivity {

  // View view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio);

//        view=this.getWindow().getDecorView();
//        view.setBackgroundResource(R.color.gray);

        int color = getIntent().getIntExtra("background", -1);
        if(color != -1) {
            RelativeLayout rootView = (RelativeLayout) findViewById(R.id.activity_audio);
            rootView.setBackgroundResource(color);
        }
    }


    public void PlayAudio(View v) {
        MediaPlayer player = MediaPlayer.create(this, R.raw.mirror_maru);
        player.start();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.audio, menu);
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

}
