# Curso de Sistemas Operativos de Propósito General - FIUBA

¡Bienvenido al curso de Sistemas Operativos de Propósito General en la Facultad de Ingeniería de la Universidad de Buenos Aires (FIUBA)!

## Descripción del Curso

Este curso ofrece una introducción exhaustiva a los fundamentos y aplicaciones de los sistemas operativos en entornos de propósito general, con un enfoque especial en su implementación y adaptación a sistemas embebidos. Los sistemas operativos desempeñan un papel crucial en la gestión de recursos y el rendimiento de los sistemas informáticos, y este curso explora cómo estos principios se aplican a dispositivos con recursos limitados.

## Objetivos

1. **Principios Fundamentales:** Comprender los conceptos básicos de los sistemas operativos y sus funciones esenciales.

2. **Aplicaciones en Sistemas Embebidos:** Adaptar los principios de los sistemas operativos a entornos embebidos, considerando las limitaciones de recursos.

3. **Procesos y Planificación:** Aprender sobre la gestión de procesos, la planificación de tareas y la asignación de prioridades.

4. **Gestión de Memoria:** Explorar estrategias de administración de memoria en sistemas embebidos.

5. **Sistema de Archivos:** Conocer las estructuras y operaciones básicas de sistemas de archivos en entornos embebidos.

## Metodología

- Clases teóricas y prácticas.
- Proyectos prácticos aplicados a sistemas embebidos.
- Evaluación continua mediante tareas y exámenes.

## Evaluación

La evaluación se basará en la participación activa en proyectos prácticos, exámenes teóricos y prácticos, así como la asistencia y participación en clases.

Este curso proporciona las habilidades y conocimientos necesarios para desarrollar sistemas operativos eficientes y adaptados a las necesidades de dispositivos embebidos, preparando a los estudiantes para los desafíos del mundo de la ingeniería informática. ¡Esperamos que disfrutes del curso y te desafíes a ti mismo en la exploración de los sistemas operativos en su máxima expresión!











# Comunicación Entre Procesos en C - Proyecto Final

Este proyecto final se centra en la implementación de la comunicación entre dos procesos en lenguaje C utilizando un Named FIFO. Los procesos involucrados son el escritor (Writer) y el lector (Reader), cada uno con sus propias funciones y características únicas.

## Contenido del Repositorio

### 1. Writer (writer.c)

- **Objetivo:** Este proceso recibe texto desde la consola y señales del usuario. Escribe en un Named FIFO con el formato `DATA:XXXXXXXXX` para los datos y `SIGN:1` o `SIGN:2` para las señales SIGUSR1 o SIGUSR2.
- **Características Destacadas:**
  - Manejo de señales: Implementa manejo de señales (SIGUSR1, SIGUSR2, SIGPIPE, SIGINT).
  - Comunicación entre procesos: Utiliza Named FIFO (`TP_FIFO`) para la comunicación.
  - Manejo de errores: Funciones dedicadas para gestionar errores, como `write_to_fifo`.
  - Seguridad en funciones: Verificación de punteros y cierre seguro del FIFO antes de salir.

### 2. Reader (reader.c)

- **Objetivo:** Este proceso lee datos desde el Named FIFO y los escribe en archivos `log.txt` o `signals.txt` según los encabezados "DATA" o "SIGN".
- **Características Destacadas:**
  - Manejo de señales: Registro de señales, con `SIGINT` manejado por `signals_handler`.
  - Comunicación entre procesos: Lee datos desde el Named FIFO y escribe en archivos según encabezados.
  - Manejo de errores: Cierre seguro de archivos en `exit_handler` para evitar pérdida de datos.
  - Seguridad en funciones: Comprobación de archivos antes de cerrar.

### 3. Buenas Prácticas

- **Organización del Código:**
  - Utilización de funciones para modular y organizar el código.
  - Comentarios detallados en español para facilitar la comprensión.

- **Manejo de Errores:**
  - Implementación de funciones específicas para gestionar y notificar errores.
  - Verificación de resultados de funciones y manejo adecuado de errores.

- **Manejo de Señales:**
  - Registro y manejo de señales relevantes para una interrupción y terminación controlada.

- **Seguridad en Funciones:**
  - Comprobación de punteros y cierre seguro de recursos para evitar comportamientos inesperados.

- **Estilo de Código:**
  - Uso consistente de mayúsculas y minúsculas, y sangría para mejorar la legibilidad.

## Ejecución del Proyecto

1. Compilar los archivos `writer.c` y `reader.c`.
2. Ejecutar el programa `writer` en un terminal.
3. Ejecutar el programa `reader` en otro terminal.
4. Observar la comunicación y el registro de datos y señales.

¡Diviértete explorando la comunicación entre procesos en C!
