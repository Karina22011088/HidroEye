// LoRa Receptora
#include <LoRa.h>
#include <SPI.h>
#include <Wire.h>
#include <esp_now.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

#define ANCHOPANTALLA 128
#define ALTOPANTALLA 64
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16

Adafruit_SSD1306 display(ANCHOPANTALLA, ALTOPANTALLA, &Wire, OLED_RST);
uint8_t macLILYGO[] = {0xFC, 0xB4, 0x67, 0xCE, 0xAF, 0x08};

struct struct_message {
    char mensaje[200];
} datosEnviar;

void setup() {
    Serial.begin(115200);
    Wire.begin(OLED_SDA, OLED_SCL);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(20, 20);
    display.println("LORA RECEPTORA");
    display.display();
    delay(2000);  // Mostrar el mensaje inicial por 2 segundos

    WiFi.mode(WIFI_STA);
    esp_now_init();

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, macLILYGO, 6);
    esp_now_add_peer(&peerInfo);

    SPI.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DIO0);
    LoRa.begin(903900000);
}

void loop() {
    int tamanoPaquete = LoRa.parsePacket();
    if (tamanoPaquete) {
        String datoLoRa = "";
        while (LoRa.available()) {
            datoLoRa += (char)LoRa.read();
        }

        Serial.println("Recibido: " + datoLoRa);

        // Mantener el formato JSON recibido
        strncpy(datosEnviar.mensaje, datoLoRa.c_str(), sizeof(datosEnviar.mensaje) - 1);
        datosEnviar.mensaje[sizeof(datosEnviar.mensaje) - 1] = '\0';
        esp_now_send(macLILYGO, (uint8_t *)&datosEnviar, sizeof(datosEnviar));

        StaticJsonDocument<200> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, datoLoRa);

        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(25, 0);
        display.println("LORA RECEPTORA");

        if (!error) {
            float temperatura = jsonDoc["temperatura"] | 0.0;
            float turbidez = jsonDoc["turbidez"] | 0.0;
            float pH = jsonDoc["pH"] | 0.0;

            Serial.print("Temp: "); Serial.println(temperatura);
            Serial.print("Turbidez: "); Serial.println(turbidez);
            Serial.print("pH: "); Serial.println(pH);

            display.setCursor(0, 18);
            display.print("Temp: ");
            display.print(temperatura);
            display.println(" C");

            display.setCursor(0, 33);
            display.print("Turbidez: ");
            display.print(turbidez);

            display.setCursor(0, 48);
            display.print("pH: ");
            display.print(pH);
        } else {
            Serial.println("Error al deserializar JSON");
            display.setCursor(0, 30);
            display.println("Error JSON");
        }

        display.display();
    }
}
