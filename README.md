![MiniQ](https://github.com/billhsu/MiniQ/raw/master/doc/MiniQ_Logo.png)
=====

MiniQ: A mini quadcopter: From Hardware design to Software algorithm.

<table>
  <tr>
    <th>Type</th><th>Chipset</th>
  </tr>
  <tr>
    <td>MCU</td><td>STM32@72MHz</td>
  </tr>
  <tr>
    <td>Accelerometer</td><td>MPU6050</td>
  </tr>
  <tr>
    <td>Gyro</td><td>MPU6050</td>
  </tr>
  <tr>
    <td>Magnetometer</td><td>HMC5338l</td>
  </tr>
</table>

The algorithm used for altitude heading reference system (AHRS) is DCM complementary filting.  
The system calculates altitude and controls the output PWMs of the four motors 1600 times per sec.

For demo video:  
[DemoVideo1](http://v.youku.com/v_show/id_XNTc0MTE5NjY0.html)  
[DemoVideo2](http://v.youku.com/v_show/id_XNTczOTY4NDIw.html)

PCB Preview  
![MiniQ](https://github.com/billhsu/MiniQ/raw/master/doc/MiniQ_PCB.PNG)

MiniQ  
![MiniQ](https://github.com/billhsu/MiniQ/raw/master/doc/MiniQ.jpg)

PC control  
![MiniQ](https://github.com/billhsu/MiniQ/raw/master/doc/AHRS_Viewer.png)

Android control  
![MiniQ](https://github.com/billhsu/MiniQ/raw/master/doc/android.png)



