# Instrucciones de Instalación

## Requisitos Previos

Antes de comenzar, asegúrate de tener lo siguiente:

- **Hardware**
  - 2 placas LoRa 32 v2
  - 1 placa LILYGO T-SIM7000G
  - Sensores de temperatura, turbidez y pH
  - Raspberry Pi 3

- **Software**
  - Arduino IDE
  - Librerías necesarias (LoRa, ArduinoJson, Adafruit_SSD1306, etc.)
  - Docker instalado en Raspberry Pi

## Pasos para Instalar y Configurar el Software

### 1. Configuración de las Placas LoRa 32 v2

#### a. Instalación de Arduino IDE

1. Descarga e instala el [Arduino IDE](https://www.arduino.cc/en/software).
2. Abre el IDE y ve a **Archivo > Preferencias**.
3. En "Gestor de URLs Adicionales de Tarjetas", agrega: (https://dl.espressif.com/dl/package_esp32_index.json)
4. Ve a **Herramientas > Placa > Gestor de Placas** y busca "ESP32". Instala el paquete correspondiente.

#### b. Instalación de Librerías

1. Ve a **Programa > Incluir Biblioteca > Administrar Bibliotecas**.
2. Busca e instala las siguientes librerías:
- LoRa
- ArduinoJson
- Adafruit SSD1306
- DallasTemperature
- OneWire

#### c. Carga del Código

1. Conecta la primera placa LoRa 32 v2 al ordenador.
2. Copia y pega el código para el transmisor (con sensores) en el IDE.
3. Selecciona la placa correcta en **Herramientas > Placa**.
4. Carga el código.

5. Repite el proceso para la segunda placa LoRa 32 v2, utilizando el código del receptor.

### 2. Configuración de LILYGO T-SIM7000G

#### a. Instalación de Librerías

1. Abre el Arduino IDE.
2. Repite el proceso de instalación de librerías como se hizo con las placas LoRa.
3. Carga el código correspondiente a la LILYGO T-SIM7000G.

### 3. Configuración del Servidor en Raspberry Pi 3

#### a. Instalación de Docker mediante la Interfaz Gráfica

1. Abre la interfaz gráfica de Raspberry Pi.
2. Ve a **Preferencias > Añadir / Quitar Software**.
3. Busca "Docker" en la lista e instálalo.
4. Una vez instalado, abre la aplicación Docker.

#### b. Configuración de IOSTACK

1. Abre Docker y ve a **Crear** o **Nuevo Contenedor**.
2. Agrega el siguiente contenido para crear un contenedor de InfluxDB:
- Imagen: `influxdb:latest`
- Puertos: `8086:8086`
- Volúmenes: `influxdb_data:/var/lib/influxdb`

3. Repite el proceso para crear contenedores para Grafana y Node-RED con las siguientes configuraciones:
- **Grafana**
  - Imagen: `grafana/grafana:latest`
  - Puertos: `3000:3000`
  - Dependencias: InfluxDB

- **Node-RED**
  - Imagen: `nodered/node-red`
  - Puertos: `1880:1880`
  - Volúmenes: `nodered_data:/data`

### 4. Configuración del Broker MQTT

1. Utiliza un broker MQTT público, como `broker.emqx.io`, para recibir datos de la LILYGO T-SIM7000G.

### 5. Visualización de Datos

1. Accede a Grafana en `http://<IP_de_tu_Raspberry_Pi>:3000`.
2. Agrega InfluxDB como fuente de datos.
3. Crea paneles para visualizar los datos de temperatura, turbidez y pH.

## Notas Finales

- Asegúrate de que todas las conexiones estén correctamente configuradas.
- Realiza pruebas iniciales para verificar la comunicación entre dispositivos.
- Ajusta los parámetros de los sensores según sea necesario.