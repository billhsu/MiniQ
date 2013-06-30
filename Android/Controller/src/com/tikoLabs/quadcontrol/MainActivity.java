package com.tikoLabs.quadcontrol;

import com.zerokol.views.JoystickView;
import com.zerokol.views.JoystickView.OnJoystickMoveListener;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {
    private TextView angleTextView;
    private TextView powerTextView;
    private TextView directionTextView;
	private JoystickView joystick;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        angleTextView = (TextView) findViewById(R.id.angleTextView);
        powerTextView = (TextView) findViewById(R.id.powerTextView);
        
        joystick = (JoystickView) findViewById(R.id.joystickView);
        joystick.setOnJoystickMoveListener(new OnJoystickMoveListener() {
            @Override
            public void onValueChanged(int angle, int power, int direction) {
                 angleTextView.setText(" " + String.valueOf(angle) + "бу");
                 powerTextView.setText(" " + String.valueOf(power) + "%");
            }
       }, JoystickView.DEFAULT_LOOP_INTERVAL);
    }
    
}
