int SpeedSensor = A0;
int TorqueSensor = A1;

void setup() {
    // put your setup code here, to run once:
  pinMode(SpeedSensor, INPUT); //Sets Speed sensor pin as an input pin
  pinMode(TorqueSensor, INPUT); //Sets Toque sensor pin as an input pin 
  Serial.begin(9600); //sets up the baud rate for UART communication serial monitor of screen.
}

int RpmFunction();
int TorqueFunction();



void loop() {
  RpmFunction();
  TorqueFunction();   
}
  


int RpmFunction(){

    int rpm_speed; 
    float analog_read_rpm = 0; //initialize speed value as zero
    float volt_speed;
    
  //  for(int i=0; i<150; i++){
    analog_read_speed_value = analogRead(SpeedSensor); //reads speed value (range between 0 to 1024)
  // }
    delay(15); 
    //Speed_value = Speed_value/150;
  
    volt_speed = (analog_read_rpm * 5)/1024; //5volts corresponds to a 1024 measured input
  // volt_speed = volt_speed/0.2; 
    rpm_speed = (int) (volt_speed * 3000)/1.7;  //since an rpm of 3000 corresponds to 1.7volts
    
    /****** For easy debugging **********/

    Serial.print("Analog read value : ");
    Serial.println(analog_read_rpm);

    Serial.print("volts from RPM meter is :")
    Serial.println(volt_speed);

    Serial.print("RPM is: ");
    Serial.print(rpm_speed); 

/*********************************/


 return rpm_speed;
}




int TorqueFunction(){

  int newton_meter_torque = 0;
  float analog_read_torque = 0;
  float volt_torque = 0;

  analog_read_torque = analogRead(TorqueSensor); 
  delay(10);

  volt_torque = analog_read_torque * 5/1024;
  newton_meter_torque = volt_torque * 2000/3.5; // volt_torque * valueoftorque@/valueofVolt@ ;


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

