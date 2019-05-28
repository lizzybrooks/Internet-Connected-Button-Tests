
/*
 * Created by LWHS Community Computing students Oscar Derryk, Raffa Gonzales, Jeffrey Jiang
 * based on example code by K. Suwatchai (Mobizt): Github: https://github.com/mobizt
 *
*/

//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "spirit-week-vote-counter.firebaseio.com" //put your database address here
#define FIREBASE_AUTH "GFx5p62qRI0tIXEKnBMibhWJylsgZ2De6J3rJp0W" // put your database secret here
#define WIFI_SSID "StudentNet" //wifi network
#define WIFI_PASSWORD "4153334021" //wifi password

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

//button stuff below
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 12;    // the number of the pushbutton pin
const int ledPin = 0;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// create a new float variable to hold the counter value for votes
int seniorcount;
int juniorcount;
int sophcount;
int froshcount;


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup(){

  Serial.begin(115200);  //frequency for the Huzzah ESP8266
  //button
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

//database initialization sequence
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

 
  Firebase.getInt(firebaseData, "/class/srtickets");
  seniorcount = firebaseData.intData();
  Serial.println(seniorcount);

  Firebase.getInt(firebaseData, "/class/jrtickets");
  seniorcount = firebaseData.intData();
  Serial.println(juniorcount);

  Firebase.getInt(firebaseData, "/class/sophtickets");
  sophcount = firebaseData.intData();
  Serial.println(sophcount);

  Firebase.getInt(firebaseData, "/class/froshtickets");
  froshcount = firebaseData.intData();
  Serial.println(froshcount);

}

void loop(){
  
//database path variables
     String path = "/class";
     String jsonStr = "";      

  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        froshcount = froshcount +1;
    
        
        if(Firebase.setDouble(firebaseData, path + "/froshtickets", froshcount)){
            Serial.println("sent counter to the database");
            Serial.println(firebaseData.intData());
        }
        else{
            Serial.println("FAILED");
            Serial.println("REASON: " + firebaseData.errorReason());
            Serial.println("------------------------------------");
            Serial.println();
            }
        }
      }
    }
  

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

  

}
