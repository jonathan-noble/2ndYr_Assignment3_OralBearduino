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

   View view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio);

        view=this.getWindow().getDecorView();
        view.setBackgroundResource(R.color.gray);

        int redBG = getIntent().getIntExtra("Red", -1);
        RelativeLayout rootView1 = (RelativeLayout)findViewById(R.id.activity_audio);
        rootView1.setBackgroundResource(redBG);

//        int blueBG = getIntent().getIntExtra("Blue", -1);
//        RelativeLayout rootView2 = (RelativeLayout)findViewById(R.id.activity_audio);
//        rootView2.setBackgroundResource(blueBG);
//
//        int yellowBG = getIntent().getIntExtra("Yellow", -1);
//        RelativeLayout rootView3 = (RelativeLayout)findViewById(R.id.activity_audio);
//        rootView3.setBackgroundResource(yellowBG);
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
