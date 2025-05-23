## Funcionalidades

El software del sistema HidroEye cumple con múltiples funcionalidades distribuidas entre los dispositivos embebidos, el servidor IoT y la interfaz de usuario:

### Principales funcionalidades:

- **Adquisición de datos en campo**
  - Lectura de sensores (pH, turbidez, temperatura) mediante pines analógicos/digitales en el **ESP32 LoRa**.
  - Conversión y normalización de señales para empaquetado eficiente.

- **Transmisión de datos**
  - Envío vía **LoRa** desde los nodos sensores al nodo receptor.
  - Comunicación entre **LoRa** receptor y **LILYGO T-SIM7000G** con GPRS vía **ESP-NOW**.
  - Envío de datos del campo al servidor mediante protocolo **MQTT sobre GPRS**.

- **Procesamiento y almacenamiento**
  - Recepción de datos en el broker **Mosquitto**.
  - Procesamiento de mensajes mediante flujos visuales en **Node-RED**.
  - Almacenamiento en base de datos **InfluxDB** con series temporales.

- **Visualización**
  - Visualización de los datos históricos mediante paneles dinámicos en **Grafana** y en tiempo real en **Node-RED**.

- **Acceso multiplataforma**
  - Consultas a la página web desde PC, tablet o smartphone a través de navegadores web seguros, sin necesidad de instalar software adicional.
