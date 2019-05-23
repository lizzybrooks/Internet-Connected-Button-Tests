
/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 *
*/


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "spirit-week-vote-counter.firebaseio.com"
#define FIREBASE_AUTH "GFx5p62qRI0tIXEKnBMibhWJylsgZ2De6J3rJp0W"
#define WIFI_SSID "StudentNet"
#define WIFI_PASSWORD "4153334021"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

void setup()
{

  Serial.begin(115200);

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
  
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

  // String path = "/ESP8266_Test";
  String path = "/class" // new path to jeffrey's database architcture 

  String jsonStr = "";
 
  Serial.println("------------------------------------");
  Serial.println("Set double test...");

// __________________
//   if (Firebase.setDouble(firebaseData, path + "/Double/Data" + 10) ))
//   {
//       Serial.println("PASSED");
//       Serial.println("PATH: " + firebaseData.dataPath());
//       Serial.println("TYPE: " + firebaseData.dataType());
//       Serial.println("ETag: " + firebaseData.ETag());
//       Serial.print("VALUE: ");
//       if (firebaseData.dataType() == "int")
//         Serial.println(firebaseData.intData());
//       else if (firebaseData.dataType() == "float")
//         Serial.println(firebaseData.floatData(), 5);
//       else if (firebaseData.dataType() == "double")
//         Serial.println(firebaseData.doubleData(), 9);
//       else if (firebaseData.dataType() == "boolean")
//         Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
//       else if (firebaseData.dataType() == "string")
//         Serial.println(firebaseData.stringData());
//       else if (firebaseData.dataType() == "json")
//         Serial.println(firebaseData.jsonData());
//       Serial.println("------------------------------------");
//       Serial.println();
//   }
//   else
//   {
//       Serial.println("FAILED");
//       Serial.println("REASON: " + firebaseData.errorReason());
//       Serial.println("------------------------------------");
//       Serial.println();
//   }
//  //________________________

//   Serial.println("------------------------------------");
//   Serial.println("Get double test...");

//   for (uint8_t i = 0; i < 10; i++)
//   {

//     if (Firebase.getInt(firebaseData, path + "/Double/Data" + (i + 1)))
//     {
//       Serial.println("PASSED");
//       Serial.println("PATH: " + firebaseData.dataPath());
//       Serial.println("TYPE: " + firebaseData.dataType());
//       Serial.println("ETag: " + firebaseData.ETag());
//       Serial.print("VALUE: ");
//       if (firebaseData.dataType() == "int")
//         Serial.println(firebaseData.intData());
//       else if (firebaseData.dataType() == "float")
//         Serial.println(firebaseData.floatData(), 5);
//       else if (firebaseData.dataType() == "double")
//         Serial.println(firebaseData.doubleData(), 9);
//       else if (firebaseData.dataType() == "boolean")
//         Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
//       else if (firebaseData.dataType() == "string")
//         Serial.println(firebaseData.stringData());
//       else if (firebaseData.dataType() == "json")
//         Serial.println(firebaseData.jsonData());
//       Serial.println("------------------------------------");
//       Serial.println();
//     }
//     else
//     {
//       Serial.println("FAILED");
//       Serial.println("REASON: " + firebaseData.errorReason());
//       Serial.println("------------------------------------");
//       Serial.println();
//     }
//   }

//   Serial.println("------------------------------------");
//   Serial.println("Push integer test...");

//   for (uint8_t i = 0; i < 5; i++)
//   {

//     if (Firebase.pushInt(firebaseData, path + "/Push/Int", (i + 1)))
//     {
//       Serial.println("PASSED");
//       Serial.println("PATH: " + firebaseData.dataPath());
//       Serial.print("PUSH NAME: ");
//       Serial.println(firebaseData.pushName());
//       Serial.println("ETag: " + firebaseData.ETag());
//       Serial.println("------------------------------------");
//       Serial.println();
//     }
//     else
//     {
//       Serial.println("FAILED");
//       Serial.println("REASON: " + firebaseData.errorReason());
//       Serial.println("------------------------------------");
//       Serial.println();
//     }
//   }

//   Serial.println("------------------------------------");
//   Serial.println("Push JSON test...");

//   for (uint8_t i = 5; i < 10; i++)
//   {

//     jsonStr = "{\"Data" + String(i + 1) + "\":" + String(i + 1) + "}";

//     if (Firebase.pushJSON(firebaseData, path + "/Push/Int", jsonStr))
//     {
//       Serial.println("PASSED");
//       Serial.println("PATH: " + firebaseData.dataPath());
//       Serial.print("PUSH NAME: ");
//       Serial.println(firebaseData.pushName());
//       Serial.println("ETag: " + firebaseData.ETag());
//       Serial.println("------------------------------------");
//       Serial.println();
//     }
//     else
//     {
//       Serial.println("FAILED");
//       Serial.println("REASON: " + firebaseData.errorReason());
//       Serial.println("------------------------------------");
//       Serial.println();
//     }
//   }

//   Serial.println("------------------------------------");
//   Serial.println("Update test...");

//   for (uint8_t i = 0; i < 5; i++)
//   {

//     jsonStr = "{\"Data" + String(i + 1) + "\":" + String(i + 5.5) + "}";

//     if (Firebase.updateNode(firebaseData, path + "/Int", jsonStr))
//     {
//       Serial.println("PASSED");
//       Serial.println("PATH: " + firebaseData.dataPath());
//       Serial.println("TYPE: " + firebaseData.dataType());
//       //No ETag available
//       Serial.print("VALUE: ");
//       if (firebaseData.dataType() == "int")
//         Serial.println(firebaseData.intData());
//       else if (firebaseData.dataType() == "float")
//         Serial.println(firebaseData.floatData(), 5);
//       else if (firebaseData.dataType() == "double")
//         Serial.println(firebaseData.doubleData(), 9);
//       else if (firebaseData.dataType() == "boolean")
//         Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
//       else if (firebaseData.dataType() == "string")
//         Serial.println(firebaseData.stringData());
//       else if (firebaseData.dataType() == "json")
//         Serial.println(firebaseData.jsonData());
//       Serial.println("------------------------------------");
//       Serial.println();
//     }
//     else
//     {
//       Serial.println("FAILED");
//       Serial.println("REASON: " + firebaseData.errorReason());
//       Serial.println("------------------------------------");
//       Serial.println();
//     }
//   }
  push_data(1, "test_yr")
}

Int get_data(Int pn_nm, String cls_yr)
{
  if (Firebase.getInt(firebaseData, "class/"+cls_yr))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ")
      Serial.println(firebaseData.intData());
      return firebaseData.intData()
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
      return -1
    }
}

void push_data( Int pin_name, String class_yr )
{
  Int cur_val = get_data(pin_name, class_yr)
  if (cur_val != -1)
  {
    jsonStr = "{" + class_yr + "\":" + String(cur_val+1) + "}";

    if (Firebase.pushJSON(firebaseData, "class", jsonStr))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }
}

void loop()
{
  
  
  String path = "/class" // new path to jeffrey's database architcture 

  String jsonStr = "";
 
  Serial.println("------------------------------------");
  
  // pins 12 13 14 16
  
}
