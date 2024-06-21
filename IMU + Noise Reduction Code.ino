#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(3, 4);

long f=1;
long b=2;
long l=3;
long r=4;
long s=0;

float filteredValueX=0;
float filteredValueY=0;
float filteredValueZ=0;

float alpha=0.5;

#include <Wire.h>
#include <SPI.h>
#include <MPU6050.h>

const byte address[6] = "0x1234567890LL";

MPU6050 mpu;

// Variables to hold raw IMU data
int16_t ax, ay, az;
int16_t gx, gy, gz;

const int threshold = 10000; // Adjust this threshold based on your specific needs

void setup () {
  Serial.begin(9600);
  Serial.begin(9600);
  Serial.begin(9600);
  Serial.begin(9600);
  Wire.begin(); // Initialize I2C
  mpu.initialize(); // Initialize MPU6050

  // Check if MPU6050 is connected
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
  Serial.println("MPU6050 connected");
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate (RF24_1MBPS);
  radio.setPALevel (RF24_PA_HIGH);
  radio.openWritingPipe (0x1234567890LL);
}
void loop () {
  // Read raw IMU data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = mpu.getAccelerationX();
  filteredValueX = alpha * ax + (1 - alpha) * filteredValueX;
  ay = mpu.getAccelerationY();
  filteredValueY = alpha * ay + (1 - alpha) * filteredValueY;
  az = mpu.getAccelerationZ();
  filteredValueZ = alpha * az + (1 - alpha) * filteredValueZ;

  Serial.print ("RawX: ");
  Serial.print(ax);
  Serial.print(", FilteredX: ");
  Serial.println(filteredValueX);

  Serial.print ("RawY: ");
  Serial.print(ay);
  Serial.print(", FilteredY: ");
  Serial.println(filteredValueY);

  Serial.print ("RawZ: ");
  Serial.print(az);
  Serial.print(", FilteredZ: ");
  Serial.println(filteredValueZ);

  if (filteredValueX > threshold) {
    radio.write (&f, sizeof(f));
    //Serial.println("f");
  }
  else if (filteredValueX < -threshold) {
    radio.write (&b, sizeof(b));
    //Serial.println("b");
  }
  else if (filteredValueY > threshold) {
    radio.write (&l, sizeof(l));
    //Serial.println("l");
  }
  else if (filteredValueY < -threshold) {
    radio.write (&r, sizeof(r));
    //Serial.println("r");
  }
  else {
    radio.write (&s, sizeof(s));
    //Serial.println("s");
  }
}