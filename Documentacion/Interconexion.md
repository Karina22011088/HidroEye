## Interconexión de Red Cableada e Inalámbrica

### Red Cableada

#### Descripción de la Configuración

- **Tipo de Cableado:**
  - Se utiliza **cableado Ethernet** (Cat5e o superior) para la conexión entre dispositivos de red, como la Raspberry Pi y otros dispositivos que requieren conexión a internet.

- **Dispositivos de Red:**
  - **Raspberry Pi 3:** Actúa como servidor que aloja servicios como InfluxDB, Grafana y Node-RED.
  - **Switch de Red (opcional):** Se puede utilizar un switch para extender la red y conectar múltiples dispositivos.

- **Configuración:**
  - Configurar la Raspberry Pi para obtener una dirección IP estática o dinámica mediante DHCP.
  - Asegurarse de que la Raspberry Pi esté conectada a la red local para permitir el acceso a otros dispositivos y a internet.

### Red Inalámbrica

#### Descripción de la Configuración

- **Tipo de Tecnología Inalámbrica:**
  - **LoRa:** Se utiliza para la comunicación a larga distancia entre los sensores y la placa receptora.
  - **Wi-Fi:** Utilizado por la Lilygo T-SIM7000G para enviar datos a un broker MQTT.
  - **ESP-NOW:** Protocolo de comunicación que permite la transmisión de datos entre dispositivos ESP sin necesidad de un router.

- **Dispositivos de Red Inalámbrica:**
  - **Placas LoRa 32 v2:** Utilizadas para transmitir y recibir datos de los sensores.
  - **Lilygo T-SIM7000G:** Utiliza la red móvil para enviar datos a un broker público.

- **Configuración:**
  - **LoRa:**
    - Configurar las frecuencias de operación (ej. 915 MHz) en las placas LoRa.
    - Asegurarse de que ambos dispositivos LoRa tengan el mismo ID de red para comunicarse.
  
  - **Wi-Fi:**
    - Configurar la conexión a la red Wi-Fi mediante la configuración del APN y credenciales en la Lilygo T-SIM7000G.
  
  - **ESP-NOW:**
    - Inicializar ESP-NOW y agregar peers (dispositivos) para permitir la comunicación directa entre la placa receptora y la Lilygo.

### Notas Adicionales

- **Dirección IP:**
  - Asignar direcciones IP adecuadas a los dispositivos en la red cableada para garantizar la conectividad.
  
- **Seguridad:**
  - Asegurarse de habilitar medidas de seguridad en la red Wi-Fi, como WPA2, para proteger los datos transmitidos.
  
- **Interferencia:**
  - Considerar la ubicación de los dispositivos para minimizar la interferencia de otras señales inalámbricas.