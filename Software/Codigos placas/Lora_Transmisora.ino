// LoRa Transmisora JSON
#include <LoRa.h>
#include <SPI.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pines LoRa
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
#define BAND 915E6

// Pantalla OLED
#define ANCHOPANTALLA 128
#define ALTOPANTALLA 64
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16

// Pines de sensores
#define TURBIDITY_PIN 39
#define PH_PIN 32
#define ONE_WIRE_BUS 22

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 display(ANCHOPANTALLA, ALTOPANTALLA, &Wire, OLED_RST);

// Variables pH
int buf[10];
int temp = 0;
unsigned long int avgValue;

void setup() {
  Serial.begin(115200);
  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("TRANSMISOR LORA");
  display.display();

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(903900000)) {
    Serial.println("Error iniciando LoRa");
    while (1);
  }

  sensors.begin();
}

float leerPHCalibrado() {
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(PH_PIN);
    delay(10);
  }

  // Ordenar el arreglo
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  avgValue = 0;
  for (int i = 2; i < 8; i++) {
    avgValue += buf[i];
  }

  float voltage = (float)avgValue * 3.3 / 4096.0 / 4.3;  // 3.3V y divisor resistivo 4.3
  float ph = -5.70 * voltage + 29.5;
  ph = 14.2 - ph;  // Ajuste empírico (puedes cambiarlo si hiciste otro)

  return ph;
}

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  float turbidity = analogRead(TURBIDITY_PIN) * 0.1;
  float pH = leerPHCalibrado();  // Usamos la función calibrada

  // Crear objeto JSON
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["temperatura"] = temperature;
  jsonDoc["turbidez"] = turbidity;
  jsonDoc["pH"] = pH;

  // Serializar JSON
  char jsonBuffer[200];
  serializeJson(jsonDoc, jsonBuffer);

  // Enviar por LoRa
  LoRa.beginPacket();
  LoRa.print(jsonBuffer);
  LoRa.endPacket();

  // Mostrar por Serial
  Serial.println("Datos enviados:");
  Serial.println(jsonBuffer);

  // Mostrar en OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.setCursor(0, 10);
  display.print("Turbidez: ");
  display.print(turbidity);
  display.setCursor(0, 20);
  display.print("pH: ");
  display.print(pH);
  display.display();

  delay(10000); // Espera 10 segundos
}
