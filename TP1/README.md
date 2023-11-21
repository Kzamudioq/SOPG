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

