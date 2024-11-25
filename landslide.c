#include <SoftwareSerial.h>

SoftwareSerial sim800l(2, 3); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted

#define Motion_Sensor A0 //Button pin, on the other pin it's wired with GND
bool Sensor_State; //Sensor_State


void setup()
{
 
  pinMode(Motion_Sensor, INPUT); //The button is always on HIGH level, when pressed it goes LOW
  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
  Serial.begin(9600);   
  delay(1000);
}
 
void loop()
{
  
//SendSMS(); 
  Sensor_State = digitalRead(Motion_Sensor);   //We are constantly reading the button State
 
  if (Sensor_State == HIGH) {            //And if it's pressed
    Serial.println("Sensor detect motion");   //Shows this message on the serial monitor
    delay(200);                         //Small delay to avoid detecting the button press many times
    
    SendSMS();                          //And this function is called
delay(4000);

 }
 else{
 Serial.println(".");
 }
 
  if (sim800l.available()){            //Displays on the serial monitor if there's a communication from the module
    Serial.write(sim800l.read()); 
  }
}
 
void SendSMS()
{
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+###############\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print("Security Alert.....!!!!!!! Some one entered in the house ");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);

}