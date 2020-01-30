/* FSR LCD display sketch, based on "FSR simple testing sketch" . 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
Potentiometer is connected to LCD and power/GND
LCD connected following scematic in Sparkfun Inventor Kit circuit #15

FSR is homemade, using conductive foam and two wires
*/
 
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrMin = 1023;        // minimum sensor value
int fsrMax = 0;           // maximum sensor value
 #include <LiquidCrystal.h>  //call the LCD library
 LiquidCrystal lcd(12,11,5,4,3,2);   //LCD connected to these pins
 
 
 
 
void setup(void) {
   
    lcd.begin(16, 2);   //Turn on the LCD
    lcd.clear();
    // calibrate during the first five seconds DON'T FORGET TO PUSH THE FSR HARD!!!
  while (millis() < 5000) {
    fsrReading = analogRead(fsrPin);

    // record the maximum sensor value
    if (fsrReading > fsrMax) {
      fsrMax = fsrReading;
    }

    // record the minimum sensor value
    if (fsrReading < fsrMin) {
      fsrMin = fsrReading;
    }
  }
}
 
void loop(void) {
  fsrReading = analogRead(fsrPin);    
  fsrReading = map(fsrReading, fsrMin, fsrMax, 0.0, 10.0);   //FSR pressure mapped on a scale of 1-10.  
  // Scale could be adjusted for more accurate force output when calibration is more controlled.
  fsrReading = constrain(fsrReading, 0.0, 10.0);   // no readings above or below the 0-10 scale
  
  lcd.setCursor(0,1); //output will be on lower line of LCD
 
  lcd.print("Pressure = ");
  lcd.print(fsrReading);  // LCD will display the pressure reading
  delay(250);  // Time between reading updates. 
  // LCD has trouble at really fast intervals. Use serial for that.
} 
