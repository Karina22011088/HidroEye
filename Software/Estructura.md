## Estructura del Código de la LoRa con sensores

1. **Inclusión de Librerías**
   - `#include <LoRa.h>`: Para manejar la comunicación LoRa.
   - `#include <SPI.h>`: Para la comunicación SPI.
   - `#include <Wire.h>`: Para la comunicación I2C.
   - `#include <ArduinoJson.h>`: Para manipular datos en formato JSON.
   - `#include <Adafruit_SSD1306.h>`: Para manejar pantallas OLED.
   - `#include <OneWire.h>`: Para la comunicación con sensores de temperatura.
   - `#include <DallasTemperature.h>`: Para manejar sensores de temperatura Dallas.

2. **Definiciones de Pines**
   - Se definen los pines para la comunicación LoRa, la pantalla OLED y los sensores de turbidez y pH.

3. **Configuración de Objetos**
   - `OneWire oneWire`: Crea un objeto para la comunicación con el sensor de temperatura.
   - `DallasTemperature sensors`: Crea un objeto para manejar el sensor de temperatura.
   - `Adafruit_SSD1306 display`: Inicializa el objeto para la pantalla OLED.

4. **Función `setup()`**
   - Inicializa la comunicación serie.
   - Configura la pantalla OLED y muestra un mensaje inicial.
   - Configura los pines y comienza la comunicación LoRa.
   - Inicia los sensores de temperatura.

5. **Función `leerPHCalibrado()`**
   - Lee y calibra el valor del pH a partir de un sensor analógico, promediando varias lecturas.

6. **Función `loop()`**
   - Solicita la temperatura del sensor y lee el valor de turbidez.
   - Calcula el pH utilizando la función calibrada.
   - Crea un objeto JSON con los datos.
   - Serializa el JSON y lo envía a través de LoRa.
   - Muestra los datos en el monitor serie y en la pantalla OLED.

## Propósito de los Módulos

- **LoRa**: Maneja la transmisión de datos a través de comunicación LoRa, permitiendo el envío de información a largas distancias.

- **ArduinoJson**: Facilita la manipulación de datos en formato JSON, permitiendo el envío y recepción de información estructurada.

- **Adafruit_SSD1306**: Controla la pantalla OLED para mostrar información visualmente, como los datos de temperatura, turbidez y pH.

- **DallasTemperature** y **OneWire**: Permiten la lectura de la temperatura desde un sensor específico.

## Resumen

Este código configura un transmisor LoRa que recopila datos de temperatura, turbidez y pH, los formatea en JSON y los envía a través de LoRa. Además, muestra los datos en una pantalla OLED y en el monitor serie. La función de calibración del pH asegura lecturas precisas, mejorando la utilidad de los datos transmitidos.

## Estructura del Código de la LoRa receptora

1. **Inclusión de Librerías**
   - `#include <LoRa.h>`: Para manejar la comunicación LoRa.
   - `#include <SPI.h>`: Para la comunicación SPI.
   - `#include <Wire.h>`: Para la comunicación I2C.
   - `#include <esp_now.h>`: Para la comunicación ESP-NOW.
   - `#include <WiFi.h>`: Para manejar conexiones WiFi.
   - `#include <ArduinoJson.h>`: Para manipular datos en formato JSON.
   - `#include <Adafruit_GFX.h>`: Librería base para gráficos.
   - `#include <Adafruit_SSD1306.h>`: Para manejar pantallas OLED.

2. **Definiciones de Pines**
   - Se definen los pines para la comunicación SPI y la pantalla OLED.

3. **Configuración de Pantalla OLED**
   - Se inicializa el objeto `Adafruit_SSD1306` para manejar la pantalla.

4. **Estructura de Datos**
   - `struct_message`: Define la estructura para almacenar el mensaje a enviar.

5. **Función `setup()`**
   - Inicializa la comunicación serie.
   - Configura la pantalla OLED y muestra un mensaje inicial.
   - Establece el modo WiFi y inicializa ESP-NOW.
   - Agrega un peer para la comunicación ESP-NOW.
   - Configura los pines y comienza la comunicación LoRa.

6. **Función `loop()`**
   - Escucha los paquetes LoRa entrantes.
   - Cuando se recibe un paquete, lo procesa y lo imprime en el monitor serie.
   - Deserializa el JSON recibido y muestra los valores en la pantalla OLED.
   - Envía el mensaje a través de ESP-NOW.

## Propósito de los Módulos

- **LoRa**: Maneja la recepción de datos a través de comunicación LoRa, permitiendo la transmisión de datos a largas distancias.

- **ESP-NOW**: Permite la comunicación entre dispositivos ESP sin necesidad de una red WiFi, ideal para enviar datos a otros nodos.

- **WiFi**: Configura el dispositivo para poder usar ESP-NOW.

- **ArduinoJson**: Facilita la manipulación de datos en formato JSON, permitiendo el envío y recepción de información estructurada.

- **Adafruit_SSD1306**: Controla la pantalla OLED para mostrar información visualmente, como datos recibidos y errores.

## Resumen

Este código configura un receptor LoRa que recibe datos, los procesa y los muestra en una pantalla OLED. Además, envía los datos a través de ESP-NOW para su uso en otros dispositivos. Utiliza JSON para estructurar los datos recibidos, lo que permite una fácil manipulación y visualización.

## Estructura del Código de la LILYGO T-SIM7000G para el envío de datos a la red

1. **Definiciones de Preprocesador**
   - `#define TINY_GSM_MODEM_SIM7000`: Configura el tipo de módem GSM a usar.
   - `#define TINY_GSM_DEBUG Serial`: Establece el puerto serie para depuración.
   - `#define ESP_WIFI_PS WIFI_PS_NONE`: Desactiva el modo de ahorro de energía de WiFi.

2. **Inclusión de Librerías**
   - `#include <WiFi.h>`: Para manejar conexiones WiFi.
   - `#include <esp_now.h>`: Para la comunicación ESP-NOW.
   - `#include <TinyGsmClient.h>`: Librería para manejar el módem GSM.
   - `#include <PubSubClient.h>`: Para manejar conexiones MQTT.

3. **Configuración de Hardware**
   - Se define el puerto serie para el módem GSM.

4. **Configuración de Red Móvil y MQTT**
   - Se establecen parámetros como APN, usuario, contraseña y detalles del broker MQTT.

5. **Estructura de Datos**
   - `struct_message`: Define la estructura para almacenar mensajes recibidos a través de ESP-NOW.

6. **Objetos Globales**
   - `TinyGsm modem`: Crea un objeto para el módem.
   - `TinyGsmClient client`: Cliente para manejar la conexión del módem.
   - `PubSubClient mqtt`: Cliente para manejar la conexión MQTT.

7. **Funciones Principales**
   - `conectarGPRS()`: Establece la conexión GPRS al módem y asegura que esté conectado.
   - `mqttConnect()`: Maneja la conexión al broker MQTT y reinicia ESP-NOW si es necesario.
   - `OnDataRecv()`: Callback que maneja los datos recibidos a través de ESP-NOW y los publica en el broker MQTT.

8. **Funciones de Configuración y Loop**
   - `setup()`: Inicializa el dispositivo, configura WiFi, GPRS y MQTT.
   - `loop()`: Mantiene la conexión MQTT, verifica el estado del sistema y ajusta la conexión GPRS si es necesario.

## Propósito de los Módulos

- **Bases de Datos**: No se manejan directamente en este código, pero los datos enviados a través de MQTT podrían ser almacenados en una base de datos en el servidor que recibe los mensajes.

- **MQTT**: Protocolo de mensajería ligero utilizado para la comunicación entre dispositivos. Este código permite enviar datos a un broker MQTT.

- **Grafana**: Aunque no se menciona en el código, Grafana se usaría para visualizar los datos almacenados en la base de datos que recibe los mensajes MQTT.

## Resumen

Este código configura un dispositivo que puede enviar datos a través de GPRS y MQTT, utilizando técnicas de comunicación como ESP-NOW. Permite la conexión a un broker MQTT para la transmisión de datos, que podrían ser utilizados por herramientas de visualización como Grafana y de monitoreo como Zabbix.
