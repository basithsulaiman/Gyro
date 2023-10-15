/* Get all possible data from MPU6050
 * Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
 * Gyro values are given in deg/s
 * Angles are given in degrees
 * Note that X and Y are tilt angles and not pitch/roll.
 *
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
#include <LiquidCrystal_PCF8574.h>



LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int show;

MPU6050 mpu(Wire);

long timer = 0;

void setup() {
  
  int error;

  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  
  Wire.beginTransmission(0x27); //Your LCD Address
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
  } // if

  lcd.begin(16, 2); // initialize the lcd
  show = 0;



}

void loop() {
  //imu.updateBias();
  mpu.update();
float ver,hor,r;
  if(millis() - timer > 1000){ // print data every second
    
    Serial.print(F("\nANGLE     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY()); Serial.print("\tZ: ");Serial.print(mpu.getAngleZ());
    
    // to display the LCD data
    lcd.setBacklight(255);
    lcd.home(); lcd.clear();
    //lcd.print("Y:"); lcd.setCursor(2,0);  lcd.print(mpu.getAngleX());
    //lcd.setCursor(9,0); 
    //lcd.print("X:"); lcd.setCursor(11,0);  lcd.print(mpu.getAngleZ());
    //lcd.setCursor(0,1);

    lcd.print("H:");lcd.print(mpu.getAngleZ());lcd.setCursor(8,0);lcd.print("V:");lcd.print(mpu.getAngleX());



    
    hor=sin(mpu.getAngleZ());
    Serial.print("\n");
    Serial.print("\n");
    Serial.print(hor);
        
    
    ver=sin(mpu.getAngleX());
    Serial.print("\n");
    Serial.print("\n");
    Serial.print(ver);
    

    Serial.print("\ndistance");
    r = sqrt(sq(sin(mpu.getAngleX())) + sq(cos(mpu.getAngleZ())));
    Serial.print(r);


    lcd.setCursor(0,1);lcd.print("distance"); lcd.setCursor(10,1);  lcd.print(r);
    



    timer = millis();

  }

}
