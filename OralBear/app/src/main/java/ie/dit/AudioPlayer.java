package ie.dit;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.media.MediaPlayer;

public class AudioPlayer extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_player);
        Button play = (Button) findViewbyId(R.id.button_play);
        Button pause = (Button) findViewbyId(R.id.button_pause);
        Button stop = (Button) findViewbyId(R.id.button_stop);


        final MediaPlayer mp = MediaPlayer.create(MainActivity.this, R.shooting_stars);

        play.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mp.start();
            }
        });

        pause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mp.pause();
            }
        });

        stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mp.stop();
                AudioPlayer.this.finish();
            }
        });﻿

    }
}

