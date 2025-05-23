## Software

### Tecnologías Utilizadas

A continuación se presenta la lista de lenguajes de programación, frameworks, bibliotecas y herramientas empleadas en el desarrollo del sistema HidroEye:

- **Lenguajes de programación:**
  - `C++` – Para la programación de los microcontroladores ESP32 y la gestión de sensores.
  - `JavaScript` – Para flujos lógicos en Node-RED y personalización de dashboards.
  - `JSON` – Para la estructuración de mensajes en el protocolo MQTT.

- **Frameworks y herramientas:**
  - **Arduino IDE** – Entornos de desarrollo utilizados para la codificación y carga del firmware en los ESP32.
  - **Node-RED** – Herramienta de programación visual para el procesamiento de datos recibidos por MQTT.
  - **Grafana** – Plataforma de visualización de datos en tiempo real mediante dashboards personalizados.
  - **InfluxDB** – Base de datos optimizada para series temporales, utilizada para almacenar datos sensados.
  - **EMQX (MQTT Broker)** – Broker MQTT ligero utilizado para la transmisión eficiente de datos entre dispositivos y servidor.
  - **IoTStack** – Conjunto de herramientas desplegado en una Raspberry Pi que integra Mosquitto, Node-RED, InfluxDB y Grafana.

- **Comunicación y protocolos:**
  - **LoRa** – Tecnología de comunicación de largo alcance y bajo consumo para transmitir datos desde los sensores remotos.
  - **ESP-NOW** – Protocolo de comunicación inalámbrico entre dispositivos ESP32.
  - **GPRS** – Transmisión de datos móviles mediante el módulo SIM7000G.
  - **MQTT** – Protocolo de mensajería ligero ideal para IoT, usado para enviar los datos del sensor al servidor.

Estas tecnologías permiten que el sistema sea modular, de bajo consumo energético, y apto para zonas rurales sin acceso a internet tradicional.
