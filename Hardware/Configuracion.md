## Configuración

### Instrucciones para la Configuración Física de los Componentes

#### 1. Conexión de la Placa LoRa 32 v2

- **Conectar los Sensores:**
  - **Sensor de Temperatura:**
    - Conectar el pin de datos del sensor al pin digital correspondiente en la LoRa 32 v2.
  - **Sensor de Turbidez:**
    - Conectar a un pin analógico para la lectura de datos.
  - **Sensor de pH:**
    - Conectar a otro pin analógico.

- **Conexiones de Alimentación:**
  - Conectar el VCC de los sensores a la fuente de alimentación de 5V de la placa.
  - Conectar el GND de los sensores al GND de la placa.

#### 2. Conexión de la Lilygo T-SIM7000G

- **Conectar a la Fuente de Alimentación:**
  - Conectar la placa Lilygo a una fuente de alimentación adecuada (puede ser a través de un panel solar o una batería).

- **Conexiones de Antena:**
  - Asegúrate de conectar la antena al módulo GSM para mejorar la recepción de señal.

#### 3. Conexión de los Paneles Solares

- **Panel Solar de 6V y 4V:**
  - Conectar los paneles solares al módulo TP4056 para cargar las baterías.
  - Asegúrate de que la polaridad sea correcta (positivo a positivo y negativo a negativo).

#### 4. Montaje en Carcasas

- **Instalación:**
  - Coloca todos los componentes dentro de las carcasas para protegerlos de condiciones ambientales.
  - Asegúrate de que las conexiones sean accesibles para facilitar el mantenimiento.

#### 5. Pruebas de Conexión

- **Verificación:**
  - Una vez que todo esté conectado, enciende las placas y verifica que los sensores funcionen correctamente.
  - Realiza pruebas de comunicación entre la placa LoRa y la Lilygo T-SIM7000G para asegurar que los datos se envían correctamente.

### Notas Adicionales

- Asegúrate de utilizar cables de calidad para evitar pérdidas de señal.
- Mantén los componentes alejados de fuentes de interferencia electromagnética.