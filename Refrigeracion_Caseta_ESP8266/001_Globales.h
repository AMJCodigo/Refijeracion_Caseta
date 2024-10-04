#include <DHT.h>
#include <ESP8266WiFi.h>  // Librería para la conexión WiFi

#define DHTPIN 2     // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11   // Definimos el tipo de sensor DHT
#define RELAY_PIN 4   // Pin donde está conectado el relé
#define LED_PIN 0    // Pin donde está conectado el LED

const char* ssid = "Change";  // Reemplaza con el nombre de tu red WiFi
const char* password = "89898989";  // Reemplaza con la contraseña de tu red WiFi

DHT dht(DHTPIN, DHTTYPE);

unsigned long relayStartTime = 0;
bool relayOn = false;