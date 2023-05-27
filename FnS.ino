#include <OneWire.h>
#include <DallasTemperature.h>

// LED

#define LED D5

// SMOKE (MQ2)

int mq2 = A0; 
int data; 

// IR_FLAME

int Flame_sensor = D0;

int Flame_detected;

// DS18B20
const int oneWireBus = 4;     

OneWire oneWire(oneWireBus);

DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(Flame_sensor, INPUT);
  pinMode(mq2,INPUT);  
  pinMode(LED, OUTPUT);
}

void loop() {
  Flame_detected = digitalRead(Flame_sensor);
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  data = analogRead(mq2);    
  if (Flame_detected == 0) {
    Serial.println("Fire detected");
    Serial.print("Smoke Level : ");
    Serial.println(data);
    delay(3000);
    if(temperatureC >= 40) {
      digitalWrite(LED, HIGH);      
      Serial.println("ALERT!!! TAKE ACTION"); 
      Serial.println("------------------------");
      delay(10000);        
      digitalWrite(LED, LOW);      
    }    
  }
  else {
    Serial.print(temperatureC);
    Serial.println("ºC");
    Serial.print(temperatureF);
    Serial.println("ºF");
    Serial.println("-----------NORMAL-----------");
  }
}
