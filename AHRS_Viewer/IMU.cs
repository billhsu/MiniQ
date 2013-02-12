using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
namespace ahrs_viewer
{
    class IMU
    {
        public static float yaw, pitch, roll;
        static float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
        static long lastUpdate;
        const float M_PI = 3.1415926f;
        static float exInt = 0.0f, eyInt = 0.0f, ezInt = 0.0f;
        const float Kp = 2.0f, Ki = 0.53f;
        public static void IMU_update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
        {
            float norm;
            float hx, hy, hz, bx, bz;
            float vx, vy, vz, wx, wy, wz;
            float ex, ey, ez;
            float iq0, iq1, iq2, iq3;
            float halfT;
            float []q = new float [4];

            // auxiliary variables to reduce number of repeated operations
            float q0q0 = q0 * q0;
            float q0q1 = q0 * q1;
            float q0q2 = q0 * q2;
            float q0q3 = q0 * q3;
            float q1q1 = q1 * q1;
            float q1q2 = q1 * q2;
            float q1q3 = q1 * q3;
            float q2q2 = q2 * q2;
            float q2q3 = q2 * q3;
            float q3q3 = q3 * q3;


            halfT = ((float)(DateTime.Now.Ticks - lastUpdate) / 20000000.0f);
            lastUpdate = DateTime.Now.Ticks;
            //Trace.WriteLine("" + halfT+"  "+gx+" "+ax+" "+mx);
            norm =(float)Math.Sqrt(ax * ax + ay * ay + az * az);
            ax = ax / norm;
            ay = ay / norm;
            az = az / norm;

            norm = (float)Math.Sqrt(mx * mx + my * my + mz * mz);
            mx = mx / norm;
            my = my / norm;
            mz = mz / norm;

            // compute reference direction of flux
            hx = 2 * mx * (0.5f - q2q2 - q3q3) + 2 * my * (q1q2 - q0q3) + 2 * mz * (q1q3 + q0q2);
            hy = 2 * mx * (q1q2 + q0q3) + 2 * my * (0.5f - q1q1 - q3q3) + 2 * mz * (q2q3 - q0q1);
            hz = 2 * mx * (q1q3 - q0q2) + 2 * my * (q2q3 + q0q1) + 2 * mz * (0.5f - q1q1 - q2q2);
            bx = (float)Math.Sqrt((hx * hx) + (hy * hy));
            bz = hz;

            // estimated direction of gravity and flux (v and w)
            vx = 2 * (q1q3 - q0q2);
            vy = 2 * (q0q1 + q2q3);
            vz = q0q0 - q1q1 - q2q2 + q3q3;
            wx = 2 * bx * (0.5f - q2q2 - q3q3) + 2 * bz * (q1q3 - q0q2);
            wy = 2 * bx * (q1q2 - q0q3) + 2 * bz * (q0q1 + q2q3);
            wz = 2 * bx * (q0q2 + q1q3) + 2 * bz * (0.5f - q1q1 - q2q2);

            // error is sum of cross product between reference direction of fields and direction measured by sensors
            ex = (ay * vz - az * vy) + (my * wz - mz * wy);
            ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
            ez = (ax * vy - ay * vx) + (mx * wy - my * wx);

            if (ex != 0.0f && ey != 0.0f && ez != 0.0f)
            {
                // integral error scaled integral gain
                exInt = exInt + ex * Ki * halfT;
                eyInt = eyInt + ey * Ki * halfT;
                ezInt = ezInt + ez * Ki * halfT;


                // adjusted gyroscope measurements
                gx = gx + Kp * ex + exInt;
                gy = gy + Kp * ey + eyInt;
                gz = gz + Kp * ez + ezInt;
            }
            // integrate quaternion rate and normalise
            iq0 = (-q1 * gx - q2 * gy - q3 * gz) * halfT;
            iq1 = (q0 * gx + q2 * gz - q3 * gy) * halfT;
            iq2 = (q0 * gy - q1 * gz + q3 * gx) * halfT;
            iq3 = (q0 * gz + q1 * gy - q2 * gx) * halfT;

            q0 += iq0;
            q1 += iq1;
            q2 += iq2;
            q3 += iq3;

            // normalise quaternion

            norm = (float)Math.Sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
            q0 = q0 / norm;
            q1 = q1 / norm;
            q2 = q2 / norm;
            q3 = q3 / norm;

            q[0] = q0;
            q[1] = q1;
            q[2] = q2;
            q[3] = q3;

            yaw = (float)Math.Atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0] * q[0] + 2 * q[1] * q[1] - 1) * 180 / M_PI;
            pitch = (float)Math.Atan(gx / (float)Math.Sqrt(gy * gy + gz * gz)) * 180 / M_PI;
            roll = (float)Math.Atan(gy / (float)Math.Sqrt(gx * gx + gz * gz)) * 180 / M_PI;
        }
    }
}
