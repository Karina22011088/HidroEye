## Estructura del Código

El código fuente se organiza según el tipo de dispositivo o componente del sistema:

### 1. **Nodo Sensor - ESP32 LoRa (Heltec / LILYGO):**
- `main.cpp`  
  - Inicialización de sensores, lectura cíclica, codificación de datos y transmisión LoRa.
- `sensor_utils.h/.cpp`  
  - Funciones específicas para cada sensor.
- `lora_comm.h/.cpp`  
  - Gestión de la transmisión LoRa y validación de paquetes.
- Variables ajustables para calibración y tiempo de muestreo.

### 2. **Nodo Receptor + GPRS (ESP32 + SIM7000G):**
- `receiver_main.cpp`  
  - Recepción de datos por LoRa, retransmisión por ESP-NOW.
- `mqtt_client.cpp`  
  - Conexión al broker MQTT y envío de datos estructurados.
- `gprs_modem.cpp`  
  - Control del módulo SIM7000G vía comandos AT.

### 3. **Servidor IoT (Raspberry Pi u Orange Pi):**
- **Mosquitto**  
  - Configuración de topics, autenticación y persistencia.
- **Node-RED**
  - Flujo de nodos: input MQTT → parseo → almacenamiento InfluxDB.
- **InfluxDB**
  - Scripts de creación de base (`CREATE DATABASE hidroeye`), gestión de usuarios y retención de datos.
- **Grafana**
  - Dashboards configurados para cada parámetro sensado con alertas.
- **Zabbix**
  - Agentes configurados en el servidor y reglas para monitorear conectividad y carga del sistema.
