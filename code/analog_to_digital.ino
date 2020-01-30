int SpeedSensor = A0;
int TorqueSensor = A1;

void setup() {
    // put your setup code here, to run once:
  pinMode(SpeedSensor, INPUT); //Sets Speed sensor pin as an input pin
  pinMode(TorqueSensor, INPUT); //Sets Toque sensor pin as an input pin 
  Serial.begin(9600); //sets up the baud rate for UART communication serial monitor of screen.
}

void loop() {
  // put your main code here, to run repeatedly:
  float analog_speed_value = 0; //initialize speed value as zero
  float Speed; 
  float finalSpeed;
  
//  for(int i=0; i<150; i++){
  analog_speed_value = analogRead(SpeedSensor); //reads speed value (range between 0 to 1024)
 // }
  delay(10);
  //Speed_value = Speed_value/150;
 
  finalSpeed = (Speed_value * 5)/1024;
  finalSpeed = finalSpeed/0.2;
  delay(500);

  Speed = (finalSpeed * 3000)/1.7;
 
  Serial.println(finalSpeed);
  Serial.println("Speed is:  ");
   Serial.print(Speed) ;

   Serial.println(" RPM");
   delay(500);  
   Serial.println( );

  }
  
