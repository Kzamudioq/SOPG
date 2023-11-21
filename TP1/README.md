# Sistema de Comunicación entre Procesos con Named FIFO
`Trabajo práctico 1`

Este sistema permite la comunicación bidireccional entre dos procesos, denominados `writer` y `reader`, a través de un Named FIFO. El `writer` puede recibir texto desde la consola y señales, mientras que el `reader` registra el texto y las señales en archivos separados.

## Estructura del Sistema

### Proceso Writer

- **Objetivo**: Inicia y espera que el usuario ingrese texto hasta que presiona ENTER. Luego, escribe los datos en un Named FIFO con el formato `DATA:XXXXXXXXX`. Además, puede recibir las señales SIGUSR1 y SIGUSR2 y escribe en el Named FIFO los mensajes `SIGN:1` o `SIGN:2`, respectivamente.

- **Funcionamiento**:
  - Espera que el usuario ingrese texto.
  - Escribe en el Named FIFO con el formato `DATA:XXXXXXXXX`.
  - Puede recibir señales SIGUSR1 o SIGUSR2 y escribe en el Named FIFO los mensajes `SIGN:1` o `SIGN:2`.

### Proceso Reader

- **Objetivo**: Lee los datos del Named FIFO y, según los encabezados "DATA" o "SIGN", escribe en el archivo `log.txt` o `signals.txt`.

- **Funcionamiento**:
  - Lee los datos del Named FIFO.
  - Escribe en `log.txt` si el encabezado es "DATA".
  - Escribe en `signals.txt` si el encabezado es "SIGN".

## Ejecución del Sistema

1. Compilar los archivos de código fuente:
   ```bash
   gcc writer.c -o writer -pthread
   gcc reader.c -o reader
2. Ejecutar los procesos en terminales separadas:
   ```bash
   ./writer
   ./reader
3. Seguir las instrucciones proporcionadas por el programa.

## Buenas Prácticas en el Código

### Proceso Writer (writer.c)

#### 1. Manejo de Señales
   - Implementación de manejo de señales (SIGUSR1, SIGUSR2, SIGPIPE, SIGINT).
   - Uso de la función `signalHandler` para gestionar las señales SIGUSR1 y SIGUSR2.

####  2. Comunicación Entre Procesos
   - Uso de Named FIFO (`TP_FIFO`) para la comunicación entre procesos.
   - Escritura en el Named FIFO con formato `DATA:XXXXXXXXX` para los datos de texto.

####  3. Manejo de Errores
   - Funciones como `write_to_fifo` para gestionar errores al escribir en el FIFO.
   - Funciones como `initialize_signal_handlers` para gestionar errores en la inicialización de manejadores de señales.

####  4. Seguridad en Funciones
   - Verificación de punteros antes de su uso para evitar comportamientos indefinidos.
   - Protección contra cierre accidental del FIFO antes de salir (`exit_handler`).

####  5. Modularización y Funciones
   - Uso de funciones para tareas específicas, mejorando la modularización y la legibilidad del código.
   - Función `background_signal_thread` para manejar las señales en un hilo en segundo plano.

### Proceso Reader (reader.c)

####  1. Manejo de Señales
   - Registro de señales, con `SIGINT` manejado por `signals_handler`.

####  2. Comunicación Entre Procesos
   - Lectura de datos desde el Named FIFO.
   - Escritura en archivos (`log.txt`, `signals.txt`) según los encabezados "DATA" o "SIGN".

####  3. Manejo de Errores
   - Cierre seguro de archivos en `exit_handler` para evitar pérdida de datos.

####  4. Seguridad en Funciones
   - Comprobación de archivos antes de cerrarlos para evitar comportamientos indefinidos.

####  5. Modularización y Funciones
   - Uso de funciones como `exit_handler` y `initialize_signal_handlers` para gestionar la salida y las señales.

---

**¡Diviértete explorando y aprendiendo con este código! 🚀**

