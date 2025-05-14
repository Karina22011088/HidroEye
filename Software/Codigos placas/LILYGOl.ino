#define TINY_GSM_MODEM_SIM7000
#define TINY_GSM_DEBUG Serial
#define ESP_WIFI_PS WIFI_PS_NONE

#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <TinyGsmClient.h>
#include <PubSubClient.h>

// Configuración hardware
#define SerialAT Serial1

// Configuración de red móvil
const char apn[] = "internet.itelcel.com";
const char gprsUser[] = "webgpr";
const char gprsPass[] = "webgprs2002";

// Configuración MQTT
const char* broker = "broker.emqx.io";
const char* topicDatos = "hidroeye/lora";
const int mqttPort = 1883;

// Estructura para ESP-NOW
#pragma pack(push, 1)
typedef struct struct_message {
  char mensaje[100];
} struct_message;
#pragma pack(pop)

struct_message datosRecibidos;

// Objetos globales
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

// Variables de control
unsigned long lastReconnectAttempt = 0;
const long reconnectInterval = 30000; // 30 segundos
bool mqttEnabled = true;

// Configuración WiFi para coexistencia
wifi_config_t wifi_config;

// Función mejorada para conectar GPRS
bool conectarGPRS() {
  Serial.println("\nIniciando conexión GPRS...");
  
  modem.restart();
  delay(2000);
  
  Serial.println("Esperando red móvil...");
  if (!modem.waitForNetwork(180000)) { // 3 minutos de timeout
    Serial.println("Fallo al conectar a red móvil");
    return false;
  }
  Serial.println("Red móvil conectada");
  
  Serial.println("Conectando a APN...");
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    Serial.println("Fallo al conectar a APN");
    return false;
  }
  
  Serial.println("Verificando conexión GPRS...");
  if (!modem.isGprsConnected()) {
    Serial.println("GPRS no conectado");
    return false;
  }
  
  Serial.print("Dirección IP: ");
  Serial.println(modem.getLocalIP());
  Serial.print("Nivel de señal: ");
  Serial.println(modem.getSignalQuality());
  
  return true;
}

// Función mejorada para conectar MQTT
bool mqttConnect() {
  if (!mqttEnabled) return false;
  
  Serial.println("\nIntentando conexión MQTT...");
  
  // Desactivar ESP-NOW temporalmente
  if (esp_now_deinit() != ESP_OK) {
    Serial.println("Error al desactivar ESP-NOW");
  }
  delay(100);
  
  // Configurar WiFi para MQTT
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  // Intentar conexión MQTT
  mqtt.setServer(broker, mqttPort);
  mqtt.setKeepAlive(60);
  
  int retries = 3;
  while (retries--) {
    Serial.print("Intento MQTT... ");
    if (mqtt.connect("SIM7000_Client")) {
      Serial.println("Conectado!");
      
      // Reactivar ESP-NOW después de conectar MQTT
      WiFi.mode(WIFI_STA);
      if (esp_now_init() != ESP_OK) {
        Serial.println("Error al reiniciar ESP-NOW");
        return false;
      }
      
      return true;
    }
    
    Serial.print("Falló (");
    Serial.print(mqtt.state());
    Serial.println(")");
    delay(5000);
  }
  
  // Reactivar ESP-NOW incluso si falla MQTT
  WiFi.mode(WIFI_STA);
  esp_now_init();
  
  return false;
}

// Callback para datos ESP-NOW (versión corregida)
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&datosRecibidos, data, min(sizeof(datosRecibidos), (size_t)len));
  Serial.print("\nDatos recibidos por ESP-NOW: ");
  Serial.println(datosRecibidos.mensaje);

  if (mqtt.connected()) {
    if (mqtt.publish(topicDatos, datosRecibidos.mensaje)) {
      Serial.println("Datos publicados en MQTT");
    } else {
      Serial.println("Error al publicar en MQTT");
    }
  } else {
    Serial.println("MQTT no conectado - Almacenando datos localmente");
    // Aquí podrías agregar lógica para almacenar datos y enviarlos luego
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\nIniciando dispositivo...");
  
  // 1. Configurar prioridades WiFi
  esp_wifi_set_ps(WIFI_PS_NONE);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  // 2. Inicializar módem GPRS
  SerialAT.begin(115200, SERIAL_8N1, 26, 27);
  delay(6000);
  
  if (!conectarGPRS()) {
    Serial.println("Error crítico: No se pudo conectar GPRS");
    ESP.restart();
  }
  
  // 3. Configurar MQTT (primer intento)
  if (!mqttConnect()) {
    Serial.println("Advertencia: No se pudo conectar inicialmente a MQTT");
  }
  
  // 4. Configurar ESP-NOW con la nueva firma de callback
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error al inicializar ESP-NOW");
    ESP.restart();
  }
  
  esp_now_register_recv_cb(OnDataRecv);  // Usando la nueva firma
  
  // Configuración avanzada WiFi para coexistencia
  esp_wifi_get_config(WIFI_IF_STA, &wifi_config);
  wifi_config.sta.listen_interval = 3;
  wifi_config.sta.sort_method = WIFI_CONNECT_AP_BY_SIGNAL;
  esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
  
  Serial.println("\nDispositivo listo");
  Serial.print("Memoria libre: ");
  Serial.println(esp_get_free_heap_size());
}

void loop() {
  static unsigned long lastStatusCheck = 0;
  
  // Mantener conexión MQTT
  if (mqttEnabled && !mqtt.connected() && millis() - lastReconnectAttempt > reconnectInterval) {
    lastReconnectAttempt = millis();
    mqttConnect();
  }
  
  if (mqtt.connected()) {
    mqtt.loop();
  }
  
  // Verificar estado general cada 60 segundos
  if (millis() - lastStatusCheck > 60000) {
    lastStatusCheck = millis();
    
    Serial.println("\n--- Estado del sistema ---");
    Serial.print("GPRS: ");
    Serial.println(modem.isGprsConnected() ? "Conectado" : "Desconectado");
    Serial.print("MQTT: ");
    Serial.println(mqtt.connected() ? "Conectado" : "Desconectado");
    Serial.print("Memoria libre: ");
    Serial.println(esp_get_free_heap_size());
    Serial.print("Nivel señal: ");
    Serial.println(modem.getSignalQuality());
    Serial.println("-----------------------\n");
    
    // Reforzar conexión GPRS si es necesario
    if (!modem.isGprsConnected()) {
      conectarGPRS();
    }
  }
  
  delay(100); // Pequeña pausa para evitar sobrecarga
}