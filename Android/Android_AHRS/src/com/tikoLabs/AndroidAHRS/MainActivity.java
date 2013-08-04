package com.tikoLabs.AndroidAHRS;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.Menu;

public class MainActivity extends Activity implements SensorEventListener{
    // Message types sent from the BluetoothChatService Handler
    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;
    float ax=0,ay=0,az=0,gx=0,gy=0,gz=0;
    // Key names received from the BluetoothChatService Handler
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";
    
    private SensorManager mSensorManager;
    private Sensor mSensorAcc,mSensorGryo;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mSensorAcc = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        mSensorGryo = mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    public final void onSensorChanged(SensorEvent event)
    {
        // Many sensors return 3 values, one for each axis.
        float x = event.values[0];
        float y = event.values[1];
        float z = event.values[2];
        if(event.sensor.getType()==Sensor.TYPE_ACCELEROMETER){
            ax=x;ay=y;az=z;
        }
        else if(event.sensor.getType()==Sensor.TYPE_GYROSCOPE){
            gx=x;gy=y;gz=z;
        }
        AHRSupdate.MadgwickAHRSupdateIMU(gx,gy,gz,ax,ay,az);
        Log.i("AHRS", "yaw:"+AHRSupdate.yaw+" pitch:"+AHRSupdate.pitch+" roll:"+AHRSupdate.roll);
    }
    
    @Override
    protected void onResume()
    {
        super.onResume();
        mSensorManager.registerListener((SensorEventListener) this, mSensorAcc, SensorManager.SENSOR_DELAY_FASTEST);
        mSensorManager.registerListener((SensorEventListener) this, mSensorGryo, SensorManager.SENSOR_DELAY_FASTEST);
    }
    @Override
    protected void onPause()
    {
        super.onPause();
        mSensorManager.unregisterListener((SensorEventListener) this);
    }


    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // TODO Auto-generated method stub
        
    }

}
