#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "temperatuur-jordy.firebaseio.com"
#define FIREBASE_AUTH "zzWXw7aKXBCbX8hXlKL4mZPzaPCMSDYb8WaDanJm"
#define WIFI_SSID "Dollard_2.4GHz"
#define WIFI_PASSWORD "ik54j3s94rgq"

#define LED 2

int sPin = 0;

int temp, maxTemp, minTemp;

void setup() {

  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("LEDStatus", 0);

  minTemp = Firebase.getInt("minTemp");
  maxTemp = Firebase.getInt("maxTemp");
}

void loop() {

  if (Firebase.getInt("LEDStatus")) {
    digitalWrite(LED, HIGH);
  }

  else {
    digitalWrite(LED, LOW);
  }

  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  //delay(10);

  temp = analogRead(sPin);
  Firebase.setInt("currentTemp", temp);

  if (temp > maxTemp) {
    maxTemp = temp;
    Firebase.setInt("maxTemp", temp);
  }

  if (temp < minTemp) {
    minTemp = temp;
    Firebase.setInt("minTemp", temp);
  }

}
