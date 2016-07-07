#include <Timer.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>

//temperature related variables
const float hysteresis = 6.0; //max hysteresis provided by drug manufacturer
const float targetTemp = 5.0; //ideal temperature provided by drug manufacturer
const long updatePeriod = 1*1000; //<-- setup required!!!
const int tempPin = 4;
const int heatPin = 13;
const int hornPin = 6;
const int sensorPin = A0; //TEST
int value = 0;
float temp = 0.0;
//const float offset = -4.0; //<-- setup required!!!
//OneWire oneWire(tempPin);
//DallasTemperature sensor(&oneWire);



// timer
Timer t;

void setup() {
  Serial.begin(115200);
  pinMode(heatPin, OUTPUT);
  t.every(updatePeriod, measureTemp);
  t.every(updatePeriod, checkTemp);

}

void loop() {  
t.update();
}

void measureTemp() {
  //read value from temp sensor with calibration offset
  //sensor.requestTemperaturesByIndex(0);
  //temp = sensor.getTempCByIndex(0) + offset;
  value = analogRead(sensorPin); //TEST
  temp = map(value,0,1023,-1000,1000)/100.0; //TEST
  }

void checkTemp() {
  if (temp<targetTemp-(hysteresis/2.0)) {
    digitalWrite(heatPin, HIGH);
    digitalWrite(hornPin, LOW);
    Serial.print("LOW Temperature: ");
    Serial.println(temp);
    } else if (temp>targetTemp+(hysteresis/2.0)) {
      digitalWrite(hornPin, HIGH);
      digitalWrite(heatPin, LOW);
      Serial.print("HIGH Temperature: ");
      Serial.print(temp);
      Serial.println(" ALARM! ALARM! ALARM!");
      
      } else {
        digitalWrite(heatPin, LOW);
        digitalWrite(hornPin, LOW);
        Serial.print("IDEAL Temperature: ");
        Serial.println(temp);
        }
  } 
  
