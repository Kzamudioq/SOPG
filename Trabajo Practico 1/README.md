# Comunicación de Procesos con Named FIFOs 🍌🚀
`Trabajo práctico 1`

¡Hola amigo humano! 👋 Bienvenido al Proyecto TP1, donde los minions están trabajando arduamente para demostrar la comunicación entre dos procesos usando named pipes (named fifo) en C. ¡Banana! 🍌🎉
---


<p align="center" width="100%">
    <img width="60%" src="https://github.com/Kzamudioq/SOPG/assets/138271936/de274c78-c5b1-4ec7-9dfb-88a55dcb7fcb"> 
</p>




## Requisitos del Sistema 🖥️

- Sistema operativo minion-compatible (algo como Unix, ¡banana Unix!).
- Compilador de C que hable el idioma minion.

<p align="center" width="100%">
    <img width="60%" src="https://github.com/Kzamudioq/SOPG/assets/138271936/bb4a8578-0adb-4d01-b9e4-c2181c62017a"> 
</p>

---

## Contenido del Proyecto 📁

- `writer.c`: aquí está el código fuente del proceso Writer, donde escribimos cosas.
- `reader.c`: y aquí está el código fuente del proceso Reader, donde leemos cosas.
- `log.txt`: un archivo para registrar los datos que el proceso Reader recibe. ¡Bello!
- `signals.txt`: otro archivo para registrar las señales que el proceso Writer recibe. ¡También bello!

---

## Función 🛠️

### writer.c
El archivo writer.c es el "¡Bello Escritor Banana!" 🍌✨ Maneja la escritura de datos en un Named FIFO. Inicia un bucle que espera ansiosamente las palabras del usuario desde la consola y atiende las señales que le lancen. Las palabras ingresadas son envueltas con un sello de tiempo y depositadas con amor en el Named FIFO. ¡Cuidado! Las señales SIGUSR1 y SIGUSR2 también son bien recibidas y registradas con emojis de celebración. El escritor también es educado y maneja la señal SIGINT (Ctrl+C) para salir con gracia y asegurar que todo quede en orden. ¡Una obra maestra del arte de la escritura! 📝🎉

### reader.c

Ahora, el reader.c, nuestro "Lector de Bananas" 📚🍌, se dedica a leer con entusiasmo los datos del Named FIFO. Los datos, ya sea mensajes de texto o señales, son tratados con respeto. Los mensajes de texto se anotan en el sagrado log.txt, mientras que las señales se guardan en el misterioso signals.txt. Este lector siempre está alerta, esperando nuevas aventuras en el Named FIFO. Juntos, writer.c y reader.c forman un equipo inseparable para una comunicación épica entre procesos. ¡Banana-tástico! 🎉🍌


---
## Instrucciones para Compilar ✨

1. Abre una terminal, ¡y asegúrate de tener tus bananas listas!
2. Compila el programa `writer.c`:

   ```bash
   gcc writer.c -o writer -Wall
   ```

3. Compila el programa reader.c:
   ```bash
   gcc reader.c -o reader -Wall
   ```
---
## Uso 🍌🤖
1. Ejecuta el programa reader para prepararlo para recibir datos:
   
```bash
./reader
¡Listo para recibir órdenes, jefe!
El proceso Reader estará esperando datos y registrará en log.txt o signals.txt según lo que reciba.
```
2. Ejecuta el programa writer en otra terminal:

```bash
./writer
El proceso Writer estará esperando tus palabras y puede recibir señales SIGUSR1 y SIGUSR2.
¡Bob dice que anotes el ID del proceso Writer que aparece en la terminal!
 ```
3. Envío de Señales 🚨

- Puedes enviar señales al proceso Writer desde otra terminal:
```bash
¡Enviar SIGUSR1!
kill -SIGUSR1 <ID_DEL_PROCESO_WRITER>

¡Enviar SIGUSR2!
kill -SIGUSR2 <ID_DEL_PROCESO_WRITER>

¡Bob dice que reemplaces <ID_DEL_PROCESO_WRITER> con el ID real del proceso Writer que anotaste!
  ```
- ¿como obtienees el ID del Proceso Writer 🕵️? puedes obtener el ID del proceso Writer ejecutando el siguiente comando en una nueva terminal:
```bash
ps aux | grep writer

¡Stuart dice que anotes el número que aparece, es el ID del proceso Writer!
  ```

<p align="center" width="70%">
    <img width="60%" src="https://github.com/Kzamudioq/SOPG/assets/138271936/c198a09d-c44d-49c0-a79e-b2de731f15fb"> 
</p>


4. Observa cómo el programa reader registra todo en log.txt y signals.txt. ¡Es como magia minion!
5. Detener la Ejecución ⛔: ¡Para la fiesta de los minions! Puedes detener la ejecución de ambos procesos presionando Ctrl + C en las terminales donde están trabajando. ¡Y listo! Ahora estás listo para jugar con la comunicación entre procesos. ¡Banana! 🍌

## Archivos generados 📁🍌

- log.txt: aquí se registran todas las aventuras épicas escritas por el writer.
- signals.txt: guarda las señales misteriosas (SIGUSR1 y SIGUSR2) que envía el writer.

## Contribuciones 🍌💬
¡Contribuciones son bienvenidas! Si encuentras algún problema, o tienes ideas para mejorar nuestras aventuras, ¡háznoslo saber!

<p align="center" width="100%">
    <img width="60%" src="https://github.com/Kzamudioq/SOPG/assets/138271936/f0635631-1a24-422c-973b-d208f038e643"> 
</p>

---

**¡Diviértete explorando y aprendiendo con este código! 🚀**

