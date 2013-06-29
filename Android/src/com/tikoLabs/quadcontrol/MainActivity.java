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
        directionTextView = (TextView) findViewById(R.id.directionTextView);
        joystick = (JoystickView) findViewById(R.id.joystickView);
        joystick.setOnJoystickMoveListener(new OnJoystickMoveListener() {
            @Override
            public void onValueChanged(int angle, int power, int direction) {
                 angleTextView.setText(" " + String.valueOf(angle) + "бу");
                 powerTextView.setText(" " + String.valueOf(power) + "%");
                 switch (direction) {
                      case JoystickView.FRONT:
                           directionTextView.setText("front_lab");
                           break;

                      case JoystickView.FRONT_RIGHT:
                           directionTextView.setText("front_right_lab");
                           break;

                      case JoystickView.RIGHT:
                           directionTextView.setText("R.string.right_lab");
                            break;

                      case JoystickView.RIGHT_BOTTOM:
                           directionTextView.setText("R.string.right_bottom_lab");
                           break;

                      case JoystickView.BOTTOM:
                           directionTextView.setText("R.string.bottom_lab");
                           break;

                      case JoystickView.BOTTOM_LEFT:
                           directionTextView.setText("R.string.bottom_left_lab");
                           break;

                      case JoystickView.LEFT:
                           directionTextView.setText("R.string.left_lab");
                           break;

                      case JoystickView.LEFT_FRONT:
                           directionTextView.setText("R.string.left_front_lab");
                           break;

                      default:
                           directionTextView.setText("R.string.center_lab");
                 }
            }
       }, JoystickView.DEFAULT_LOOP_INTERVAL);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
