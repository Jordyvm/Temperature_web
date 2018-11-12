#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include "DHT.h"

#define FIREBASE_HOST "temperatuur-jordy.firebaseio.com"
#define FIREBASE_AUTH "zzWXw7aKXBCbX8hXlKL4mZPzaPCMSDYb8WaDanJm"
#define WIFI_SSID "Dollard_2.4GHz"
#define WIFI_PASSWORD "ik54j3s94rgq"

#define LED 2

#define DHTPIN 14
#define DHTTYPE DHT11

int sPin = 0;

float  maxTemp, minTemp;

DHT dht(DHTPIN, DHTTYPE);
float hic,hif;

void setup() {

  dht.begin();

  pinMode(LED, OUTPUT);
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
  digitalWrite(LED, HIGH);

  minTemp = Firebase.getFloat("minTemp");
  maxTemp = Firebase.getFloat("maxTemp");
}

void loop() {
  delay(2000);
  temp();
  
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  
  Firebase.setFloat("currentTemp", hic);

  if (hic > maxTemp) {
    maxTemp = hic;
    Firebase.setFloat("maxTemp", hic);
  }

  if (hic < minTemp) {
    minTemp = hic;
    Firebase.setFloat("minTemp", hic);
  }

}

void temp(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  }
