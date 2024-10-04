#include <DHT.h>

#define DHTPIN 2     // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11   // Definimos el tipo de sensor DHT
#define RELAY_PIN 3   // Pin donde está conectado el relé
#define LED_PIN 13    // Pin donde está conectado el LED


DHT dht(DHTPIN, DHTTYPE);

unsigned long relayStartTime = 0;
bool relayOn = false;


void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  delay(1000);
  
  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("Fallo sensor DHT11");
    // Si el sensor falla, parpadea el LED rápidamente
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    digitalWrite(RELAY_PIN, LOW);
    
  } else {
    // Mostrar temperatura y humedad por serial
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" °C, Humedad: ");
    Serial.print(humidity);
    Serial.println(" % ");
    
    // Si el sensor vuelve a funcionar, apaga el LED y reinicia la variable
    digitalWrite(LED_PIN, LOW);
    
    if (temperature >= 25) {
      if (!relayOn) {
        relayOn = true;
        relayStartTime = millis();
        digitalWrite(RELAY_PIN, HIGH);
      }
    } else if (temperature <= 24 && relayOn) {
      unsigned long elapsedTime = (millis() - relayStartTime) / 60000; // Convertir a minutos
      unsigned long remainingTime = 30 - elapsedTime;
      Serial.print("Minutos restantes: ");
      Serial.println(remainingTime);
      
      if (elapsedTime >= 30) {
        relayOn = false;
        digitalWrite(RELAY_PIN, LOW);
      }
    }
    
    if (relayOn) {
      unsigned long elapsedTime = (millis() - relayStartTime) / 60000; // Convertir a minutos
      unsigned long remainingTime = 30 - elapsedTime;
      Serial.print("Minutos restantes: ");
      Serial.println(remainingTime);
      digitalWrite(RELAY_PIN, HIGH);
      
      if (elapsedTime >= 30) {
        relayOn = false;
        digitalWrite(RELAY_PIN, LOW);
      }
    }
  }
}
