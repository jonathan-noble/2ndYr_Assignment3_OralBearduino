package brushing.oral_bear_1;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;


public class ReminderFragment extends Fragment
{

    Button btnDatePicker, btnTimePicker;
    EditText in_date,in_time;
    TextView txtDate,txtTime;

    public ReminderFragment() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v;
        // Inflate the layout for this fragment
        v = inflater.inflate(R.layout.fragment_reminder, container, false);

        //date btn
        btnDatePicker = (Button) v.findViewById(R.id.btn_date);
        txtDate = (TextView) v.findViewById(R.id.in_date);

        btnDatePicker.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                FragmentManager fm = getFragmentManager();
                FragmentTransaction ft = fm.beginTransaction();
                ft.commit();
            }
        });

        //time btn
        btnTimePicker = (Button) v.findViewById(R.id.btn_time);
        txtTime = (TextView) v.findViewById(R.id.in_time);
        txtDate = (TextView) v.findViewById(R.id.in_date);

        in_date=(EditText) getActivity().findViewById(R.id.in_date);
        in_time=(EditText) getActivity().findViewById(R.id.in_time);

        btnTimePicker.setOnClickListener
                (new View.OnClickListener()
                {
                    @Override
                    public void onClick(View v) {
                        FragmentManager fm = getFragmentManager();
                        FragmentTransaction ft = fm.beginTransaction();
                        ft.commit();
                    }



                });
        String in_date = txtDate.getText().toString();
        String in_time =txtTime.getText().toString();
        txtDate.setText(in_date);
        return v;
    }
}




