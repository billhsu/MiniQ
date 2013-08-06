package com.tikoLabs.AndroidAHRS;

import java.nio.ByteBuffer;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements SensorEventListener{
    // Message types sent from the BluetoothChatService Handler
    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;
    float ax=0,ay=0,az=0,gx=0,gy=0,gz=0,mx=0,my=0,mz=0;
    // Key names received from the BluetoothChatService Handler
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";
    // Intent request codes
    private static final int REQUEST_CONNECT_DEVICE = 1;
    private static final int REQUEST_ENABLE_BT = 2;
    
    private long millis;
    private SensorManager mSensorManager;
    private Sensor mSensorAcc,mSensorGryo,mSensorMag;
    private TextView AHRSResult;
    
    // Name of the connected device
    private String mConnectedDeviceName = null;
    // Array adapter for the conversation thread
    private ArrayAdapter<String> mConversationArrayAdapter;
    // Local Bluetooth adapter
    private BluetoothAdapter mBluetoothAdapter = null;
    // Member object for the chat services
    private BluetoothService mBTService = null;
    
    public static byte [] float2ByteArray (float value)
    {  
         return ByteBuffer.allocate(4).putFloat(value).array();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mSensorAcc = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        mSensorGryo = mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        mSensorMag = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        AHRSResult = (TextView)findViewById(R.id.AHRSResult);
        millis = System.currentTimeMillis();
        
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        // If the adapter is null, then Bluetooth is not supported
        if (mBluetoothAdapter == null) {
            Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
            finish();
            return;
        }
    }
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d("AHRS", "onActivityResult " + resultCode);
        switch (requestCode) {
        case REQUEST_CONNECT_DEVICE:
            // When DeviceListActivity returns with a device to connect
            if (resultCode == Activity.RESULT_OK) {
                // Get the device MAC address
                String address = data.getExtras()
                                     .getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);
                // Get the BLuetoothDevice object
                BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
                // Attempt to connect to the device
                mBTService.connect(device);
            }
            break;
        case REQUEST_ENABLE_BT:
            // When the request to enable Bluetooth returns
            if (resultCode == Activity.RESULT_OK) {
                // Bluetooth is now enabled, so set up a chat session
                setupBTService();
            } else {
                // User did not enable Bluetooth or an error occured
                Log.d("AHRS", "BT not enabled");
                Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
                finish();
            }
        }
    }
    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case MESSAGE_STATE_CHANGE:
                Log.i("AHRS", "MESSAGE_STATE_CHANGE: " + msg.arg1);
                switch (msg.arg1) {
                case BluetoothService.STATE_CONNECTED:
                    Log.i("AHRS",mConnectedDeviceName);
                    break;
                case BluetoothService.STATE_CONNECTING:
                    Log.i("AHRS",""+R.string.title_connecting);
                    break;
                case BluetoothService.STATE_LISTEN:
                case BluetoothService.STATE_NONE:
                    Log.i("AHRS",""+R.string.title_not_connected);
                    break;
                }
                break;
            case MESSAGE_WRITE:
                byte[] writeBuf = (byte[]) msg.obj;
                // construct a string from the buffer
                String writeMessage = new String(writeBuf);
                //mConversationArrayAdapter.add("Me:  " + writeMessage);
                break;
            case MESSAGE_READ:
                byte[] readBuf = (byte[]) msg.obj;
                // construct a string from the valid bytes in the buffer
                String readMessage = new String(readBuf, 0, msg.arg1);
                //mConversationArrayAdapter.add(mConnectedDeviceName+":  " + readMessage);
                break;
            case MESSAGE_DEVICE_NAME:
                // save the connected device's name
                mConnectedDeviceName = msg.getData().getString(DEVICE_NAME);
                Toast.makeText(getApplicationContext(), "Connected to "
                               + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
                break;
            case MESSAGE_TOAST:
                Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),
                               Toast.LENGTH_SHORT).show();
                break;
            }
        }
    };
    private void setupBTService() {
        Log.d("AHRS", "setupBTService()");

        // Initialize the BluetoothChatService to perform bluetooth connections
        mBTService = new BluetoothService(this, mHandler);

    }
    @Override
    protected void onStart() {
        // TODO Auto-generated method stub
        super.onStart();
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
        // Otherwise, setup the chat session
        } else {
            if (mBTService == null) setupBTService();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
            case R.id.menu_connect:
                Intent serverIntent = new Intent(MainActivity.this, DeviceListActivity.class);
                startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
    
    public static byte[] toBytes(short s){
        if(s<0) s=(short) (32768-s);
        return new byte[]{(byte)(s & 0x00FF),(byte)((s & 0xFF00)>>8)};
    }

    
    public final void onSensorChanged(SensorEvent event)
    {
        long timeDelta = System.currentTimeMillis() - millis;
        // Many sensors return 3 values, one for each axis.
        float x = event.values[0];
        float y = event.values[1];
        float z = event.values[2];
        if(event.sensor==mSensorAcc){
            ax=x;ay=y;az=z;
        }
        else if(event.sensor==mSensorGryo){
            gx=x;gy=y;gz=z;
        }
        else if(event.sensor==mSensorMag){
            mx=x;my=y;mz=z;
        }
        AHRSupdate.timeDelta = timeDelta/1000.0f;
        AHRSupdate.myUpdate(gx,gy,gz,ax,ay,az);
        AHRSResult.setText("yaw:"+AHRSupdate.yaw+"\npitch:"+AHRSupdate.roll+"\nroll:"+AHRSupdate.pitch+
                "\nax:"+ax+"\nay:"+ay+"\naz:"+az);
        millis = System.currentTimeMillis();
        byte[] sendResult= {(byte) 0xf0, (byte) 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        /*short sYaw=0,sRoll=0,sPitch=0;
        sYaw = (short) (-AHRSupdate.yaw*10);
        sRoll = (short) (-AHRSupdate.roll*10);
        sPitch = (short) (AHRSupdate.pitch*10);
        byte [] yawByte = toBytes(sYaw);
        byte [] rollByte = toBytes(sRoll);
        byte [] pitchByte = toBytes(sPitch);
        sendResult[2] = yawByte[1];sendResult[3] = yawByte[0];
        sendResult[4] = pitchByte[1];sendResult[5] = pitchByte[0];
        sendResult[6] = rollByte[1];sendResult[7] = rollByte[0];*/
        byte [] bq0 = float2ByteArray(AHRSupdate.q0);
        byte [] bq1 = float2ByteArray(AHRSupdate.q1);
        byte [] bq2 = float2ByteArray(AHRSupdate.q2);
        byte [] bq3 = float2ByteArray(AHRSupdate.q3);
        sendResult[2] = bq0[3]; sendResult[3] = bq0[2];sendResult[4] = bq0[1];sendResult[5] = bq0[0];
        sendResult[2+4] = bq1[3]; sendResult[3+4] = bq1[2];sendResult[4+4] = bq1[1];sendResult[5+4] = bq1[0];
        sendResult[2+8] = bq2[3]; sendResult[3+8] = bq2[2];sendResult[4+8] = bq2[1];sendResult[5+8] = bq2[0];
        sendResult[2+12] = bq3[3]; sendResult[3+12] = bq3[2];sendResult[4+12] = bq3[1];sendResult[5+12] = bq3[0];
        
        mBTService.write(sendResult);
    }
    
    @Override
    protected void onResume()
    {
        super.onResume();
        mSensorManager.registerListener((SensorEventListener) this, mSensorAcc, SensorManager.SENSOR_DELAY_FASTEST);
        mSensorManager.registerListener((SensorEventListener) this, mSensorGryo, SensorManager.SENSOR_DELAY_FASTEST);
        mSensorManager.registerListener((SensorEventListener) this, mSensorMag, SensorManager.SENSOR_DELAY_FASTEST);
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
