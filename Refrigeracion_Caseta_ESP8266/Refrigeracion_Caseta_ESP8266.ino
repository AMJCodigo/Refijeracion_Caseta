
#include "001_Globales.h"
#include "002_Conectar_Internet.h"


void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();

  Conectar_Internet();
  
}

void loop() {

    digitalWrite(LED_PIN, HIGH); // Enciende el LED
    delay(100); // Espera 100 milisegundos
    digitalWrite(LED_PIN, LOW); // Apaga el LED

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  delay(1000);
  
  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("Fallo sensor DHT11");
    digitalWrite(RELAY_PIN, LOW);
      {for (int i = 0; i < 100; i++) {
    digitalWrite(LED_PIN, HIGH); // Enciende el LED
    delay(50); // Espera 100 milisegundos
    digitalWrite(LED_PIN, LOW); // Apaga el LED
    delay(50); // Espera 100 milisegundos
  }

}
    
  } else {
    // Mostrar temperatura y humedad por serial
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" °C, Humedad: ");
    Serial.print(humidity);
    Serial.println(" % ");
    
    // Si el sensor vuelve a funcionar, apaga el LED y reinicia la variable
    digitalWrite(LED_PIN, LOW);
    
    if (temperature >= 22) {
      if (!relayOn) {
        relayOn = true;
        relayStartTime = millis();
        digitalWrite(RELAY_PIN, HIGH);
      }
    } else if (temperature <= 21 && relayOn) {
      unsigned long elapsedTime = (millis() - relayStartTime) / 60000; // Convertir a minutos
      unsigned long remainingTime = 30 - elapsedTime;
      Serial.print("Minutos restantes: ");
      Serial.println(remainingTime);
      
      if (elapsedTime >= 15) {
        relayOn = false;
        digitalWrite(RELAY_PIN, LOW);
      }
    }
    
    if (relayOn) {
      unsigned long elapsedTime = (millis() - relayStartTime) / 60000; // Convertir a minutos
      unsigned long remainingTime = 15 - elapsedTime;

      digitalWrite(RELAY_PIN, HIGH);
      
      if (elapsedTime >= 15) {
        relayOn = false;
        digitalWrite(RELAY_PIN, LOW);
      }
    }
  }
}
