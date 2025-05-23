## Casos de Uso

A continuación, se presentan los principales casos de uso del sistema HidroEye, diferenciados por tipo de usuario: Usuario Final, Administrador y Proveedor del Servicio.

---

### 👤 Usuario Final

**Caso de Uso 1: Visualización de Datos en Tiempo Real**  
- **Descripción:** El usuario accede a la plataforma web desde un navegador en PC o smartphone para consultar el estado actual del agua monitoreada (pH, turbidez, temperatura, TDS).  
- **Flujo principal:**
  1. El usuario inicia sesión en el panel web.
  2. Selecciona el punto de monitoreo.
  3. Visualiza gráficos en tiempo real generados por Grafana.
- **Resultado esperado:** El sistema muestra los valores actualizados provenientes de la base de datos InfluxDB.

**Caso de Uso 2: Consulta de Datos Históricos**  
- **Descripción:** El usuario revisa las mediciones históricas almacenadas, con la posibilidad de aplicar filtros por fecha, sensor o nivel de alerta.  
- **Flujo principal:**
  1. Selección de filtros (rango de fechas, tipo de sensor).
  2. Visualización de estadísticas, tendencias o eventos críticos.
- **Resultado esperado:** El sistema entrega una visualización de los datos históricos en forma de gráficas interactivas.

**Caso de Uso 3: Recibir Notificaciones**  
- **Descripción:** El usuario recibe alertas automáticas (correo o notificación web) cuando los valores medidos superan ciertos umbrales.  
- **Flujo principal:**
  1. El sistema detecta un valor fuera de rango.
  2. Se activa una regla en Node-RED.
  3. El usuario es notificado mediante el canal configurado.
- **Resultado esperado:** El usuario recibe una notificación inmediata con detalles del evento crítico.

---

### 🛠️ Administrador

**Caso de Uso 1: Configuración de Dispositivos**  
- **Descripción:** El administrador configura los parámetros de los nodos de sensores (intervalos de muestreo, calibración, identificación).  
- **Flujo principal:**
  1. Accede al sistema como administrador.
  2. Selecciona el dispositivo a configurar.
  3. Envía los nuevos parámetros mediante comandos MQTT.
- **Resultado esperado:** Los cambios se aplican y son almacenados en el sistema.

**Caso de Uso 2: Gestión de Usuarios**  
- **Descripción:** El administrador registra, edita o elimina cuentas de usuarios con distintos niveles de permisos.  
- **Flujo principal:**
  1. Accede al panel de gestión de usuarios.
  2. Realiza las acciones necesarias (crear, actualizar, eliminar).
- **Resultado esperado:** La base de datos de usuarios se actualiza y los cambios se reflejan inmediatamente en el acceso al sistema.

**Caso de Uso 3: Monitoreo de Sistema**  
- **Descripción:** El administrador supervisa el estado de conectividad de sensores, bases de datos y servicios web.  
- **Flujo principal:**
  1. Revisión de panel de Zabbix.
  2. Detección de fallas de red o desconexiones.
  3. Registro de eventos para mantenimiento.
- **Resultado esperado:** El sistema alerta al administrador sobre cualquier fallo o interrupción en la red.

---

### 📡 Proveedor del Servicio

**Caso de Uso 1: Despliegue de Nuevos Nodos**  
- **Descripción:** El proveedor instala nuevos sensores remotos y los integra a la red del sistema.  
- **Flujo principal:**
  1. Configuración inicial de la placa (LILYGO ESP32).
  2. Emparejamiento por LoRa y validación de comunicación.
  3. Registro del nodo en la plataforma central.
- **Resultado esperado:** El nuevo nodo comienza a enviar datos al servidor y es visible en el dashboard.

**Caso de Uso 2: Mantenimiento Preventivo**  
- **Descripción:** Se realiza mantenimiento periódico de sensores (limpieza, calibración, pruebas de conectividad).  
- **Flujo principal:**
  1. El proveedor identifica el nodo por GPS o ID.
  2. Aplica mantenimiento físico o de firmware.
  3. Verifica su correcto funcionamiento en la plataforma.
- **Resultado esperado:** El nodo se mantiene activo y funcional sin pérdida de datos.

**Caso de Uso 3: Actualización de Firmware OTA**  
- **Descripción:** Se actualiza el firmware de los nodos de forma remota para agregar nuevas funcionalidades o corregir errores.  
- **Flujo principal:**
  1. Carga del nuevo firmware en el servidor.
  2. Transmisión vía GPRS o Wi-Fi al dispositivo.
  3. Validación automática del éxito de la actualización.
- **Resultado esperado:** El nodo reinicia con el nuevo firmware funcionando correctamente.

---
