# HidroEye
## Breve descripción del proyecto

**HidroEye** es un sistema de Internet de las Cosas (IoT) diseñado para monitorear en tiempo real la calidad del agua de riego en zonas agrícolas del municipio de Mixquiahuala. Su propósito principal es prevenir riesgos para los cultivos y para la salud humana mediante la recolección, transmisión y análisis de datos fisicoquímicos del agua.

El **alcance** del proyecto incluye la medición de parámetros clave en puntos estratégicos de los canales de riego, la transmisión de estos datos hacia una estación receptora central, y su posterior envío a un servidor donde son almacenados, procesados y visualizados para su análisis por técnicos, autoridades y agricultores.

## Tecnologías utilizadas

- **Sensores**:
  - DS18B20 (temperatura)
  - Sensor de turbidez
  - Sensor de pH
  - Sensor TDS (Total Dissolved Solids)

- **Microcontrolador**:
  - LILYGO T-SIM7000G ESP32 con conectividad GPRS y LoRa

- **Tecnologías de comunicación**:
  - **LoRa** para comunicación de largo alcance entre nodos sensores y la estación receptora
  - **ESP-NOW (WiFi)** para comunicación punto a punto entre dispositivos locales
  - **GPRS** para el envío de datos hacia el servidor IoT a través de redes móviles

- **Servidor IoT** (Orange Pi o Raspberry Pi con IoTStack):
  - **Mosquitto** (broker MQTT)
  - **Node-RED** (procesamiento de datos)
  - **InfluxDB** (base de datos de series temporales)
  - **Grafana** (visualización de datos en dashboards)

- **Visualización**:
  - Dashboards dinámicos en **Grafana** accesibles por navegador web

## Diagrama de topología lógica del sistema

A continuación se describe la topología lógica del sistema, representando el flujo de datos desde los sensores hasta el usuario final:

```mermaid
flowchart TD
    subgraph Nodo Sensor Remoto
        Sensor1[Sensor pH / TDS / Turbidez / Temp]
        ESP32_Node1[LILYGO ESP32 + LoRa]
        Sensor1 --> ESP32_Node1
    end

    subgraph Estación Receptora
        LoRa_Receptor[LILYGO ESP32 LoRa]
        Local_ESP32[ESP32 + GPRS]
        LoRa_Receptor -->|ESP-NOW| Local_ESP32
    end

    subgraph Red Celular
        GPRS_Module[SIM7000G]
        Local_ESP32 -->|GPRS| GPRS_Module
    end

    subgraph Servidor IoT
        MQTT[Broker MQTT - Mosquitto]
        NodeRED[Node-RED]
        DB[InfluxDB]
        Grafana[Dashboard - Grafana]
        GPRS_Module --> MQTT
        MQTT --> NodeRED
        NodeRED --> DB
        DB --> Grafana
    end

    subgraph Usuario Final
        Usuario[Web (PC/Smartphone)]
        Grafana --> Usuario
    end