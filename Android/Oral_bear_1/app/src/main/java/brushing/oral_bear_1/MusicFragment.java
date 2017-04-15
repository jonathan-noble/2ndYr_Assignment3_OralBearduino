package brushing.oral_bear_1;


import android.media.MediaPlayer;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


/**
 * A simple {@link Fragment} subclass.
 */
public class MusicFragment extends Fragment {


    public MusicFragment() {
        // Required empty public constructor
    }
Button play,pause;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View rootView=inflater.inflate(R.layout.fragment_music,
                container, false);
        play =(Button) rootView.findViewById(R.id.play_but);
        pause =(Button) rootView.findViewById(R.id.pause_but);

        final MediaPlayer sound = MediaPlayer.create(getActivity(),R.raw.barney);
        play.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                sound.setLooping(true);
                sound.start();
            }
        });

        pause.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if(sound.isPlaying())
                {
                    sound.pause();
                }
            }

        });

        return rootView;

        //to play audio within fragment u must implement rootview

    }

}
