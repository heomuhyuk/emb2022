
#ifndef _accelMagGyro_h_
#define _accelMagGyro_h_

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

int accelInit(void);
int magInit(void);
int gyroInit(void);
int* accelRead(void);
int* magRead(void);
int* gyroRead(void);

#endif //_accelMagGyro_h_
