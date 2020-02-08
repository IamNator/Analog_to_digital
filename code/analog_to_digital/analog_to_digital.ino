#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x3F for a 16 chars and 2 line display


int SpeedSensor = A0;
int TorqueSensor = A1;
int VoltageSensor = A2;

void setup() {
    // code runs once:
  pinMode(SpeedSensor, INPUT); //Sets Speed sensor pin as an input pin
  pinMode(TorqueSensor, INPUT); //Sets Toque sensor pin as an input pin 
  Serial.begin(9600); //sets up the baud rate for UART communication serial monitor of screen.



  lcd.init();                      // initialize the lcd 
  lcd.begin(16,2);  //Screen size
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Analog to digi-");
  lcd.setCursor(0,1);
  lcd.print("tal");
  lcd.setCursor(5,1);
  lcd.print("Converter.");
  delay(3000);
}



int RpmFunction();
float TorqueFunction();
float voltageFunction();
int loops = 0;


void loop() {
  loops++;
  lcd.clear();

  if (loops%10 == 0){
    
    /****for voltage*****/
    lcd.setCursor(0,0);
    lcd.print("Voltage:");
    lcd.setCursor(11,0);
    lcd.print(voltageFunction());
    lcd.setCursor(0,1);
    lcd.print(loops);
    delay(1500);
  
  }

  
  lcd.clear();
  /* .. for rpm .. */
  lcd.setCursor(0,0);
  lcd.print("RPM:");
  lcd.setCursor(5,0);
  lcd.print(RpmFunction());
  lcd.setCursor(10,0);
  lcd.print("rpm");

  /*...for torque display */
  lcd.setCursor(0,1);
  lcd.print("Torque: ");
  lcd.setCursor(8,1); 
  lcd.print(TorqueFunction());  
  lcd.setCursor(14,1);
  lcd.print("Nm");

  delay(2500); //Refresh every 5 seconds
}
  


int RpmFunction(){

    int rpm_speed; 
    float analog_read_rpm = 0; //initialize speed value as zero
    float volt_speed;
    
    for(int i=0; i<150; i++){
    analog_read_rpm = analogRead(SpeedSensor); //reads speed value (range between 0 to 1024)
   }
    delay(15); 
    Speed_value = Speed_value/150;
  
    volt_speed = (analog_read_rpm * 5)/1024; //5volts corresponds to a 1024 measured input
  // volt_speed = volt_speed/0.2; 
    rpm_speed = (int) (volt_speed * 3000)/1.7;  //since an rpm of 3000 corresponds to 1.7volts
    
    /****** For easy debugging **********/

    Serial.print("Analog read value : ");
    Serial.println(analog_read_rpm);

    Serial.print("volts from RPM meter is :");
    Serial.println(volt_speed);

    Serial.print("RPM is: ");
    Serial.print(rpm_speed); 

/*********************************/


  if (rpm_speed > 3100)  rpm_speed /= 2; 
  if (rpm_speed < 2500)  rpm_speed = 2610; 
  
 return rpm_speed;
 
}




float TorqueFunction(){

  int newton_meter_torque = 0;
  float analog_read_torque = 0;
  float volt_torque = 0;

  for (int j=0; j<150; j++){
  analog_read_torque = analogRead(TorqueSensor);
  }

  analog_read_torque /= 150;
  delay(10);

  volt_torque = analog_read_torque * voltageFunction()/1024;
  newton_meter_torque = volt_torque * 1.581787606/1.23; // volt_torque * valueoftorque@/valueofVolt@ ; 1 inch lbs 0.112984829 Nm


  /* for easy debugging with laptop or serial monitor */

  Serial.print("Analog read torque : ");
  Serial.println(analog_read_torque);

  Serial.print("Volt read torque : ");
  Serial.println(volt_torque);

  Serial.print("torque in Nm :");
  Serial.println(newton_meter_torque); 

  /***************/

  return newton_meter_torque;
}
 

float voltageFunction(){
  float R1 = 7500, R2 = 30000;
  float volts=0;
  float volts_analog;
  if (int j=0; j<150; j++){
  volts_analog = analogRead(VoltageSensor);
  }
  volts_analog /= 150;
  float voltTemporal = (volts_analog * 5.0)/1024.0;
  
  volts = voltTemporal/(R2/(R1+R2));
  
  

return volts;
}
