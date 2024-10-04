#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11   // Definimos el tipo de sensor DHT11
#define RELAYPIN 3   // Pin donde está conectado el relé
#define LEDPIN 13    // Pin donde está conectado el LED

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const long interval = 1800000; // 30 minutos en milisegundos
bool relayOn = false;
bool sensorError = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAYPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW); // Aseguramos que el relé esté apagado al inicio
  digitalWrite(LEDPIN, HIGH);   // Aseguramos que el LED esté apagado al inicio
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  delay(1000);

  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer del sensor DHT11");
    sensorError = true;
    digitalWrite(RELAYPIN, LOW);
  } else {
    sensorError = false;
    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }

  if (sensorError) {
    // Parpadeo rápido del LED
    digitalWrite(LEDPIN, LOW);
    delay(100);
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
    digitalWrite(LEDPIN, HIGH);
    delay(100);

    return;
  } else {
    digitalWrite(LEDPIN, HIGH); // Aseguramos que el LED esté apagado si el sensor funciona
  }

  unsigned long currentMillis = millis();

  if (t >= 30 && !relayOn) {
    digitalWrite(RELAYPIN, HIGH);
    Serial.println("El extractor se ha puesto en marcha");
    previousMillis = currentMillis;
    relayOn = true;
  }

  if (relayOn) {
    unsigned long elapsedMillis = currentMillis - previousMillis;
    unsigned long remainingMillis = interval - elapsedMillis;
    int remainingMinutes = remainingMillis / 60000;
    Serial.print("Minutos restantes para completar el ciclo = ");
    Serial.println(remainingMinutes);
    
    if (elapsedMillis >= interval && t <= 27) {
      digitalWrite(RELAYPIN, LOW);
      Serial.println("El extractor se ha apagado");
      relayOn = false;
    }
  }
}
