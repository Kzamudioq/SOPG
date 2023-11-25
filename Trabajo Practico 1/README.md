# Comunicación de Procesos con Named FIFOs 🍌🚀
`Trabajo práctico 1`

¡Hola, amiguitos! Bienvenidos al proyecto de comunicación de procesos usando Named FIFOs. ¡Prepárense para una aventura emocionante en el mundo de los códigos y las bananas! 🍌🎉
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
   gcc -o writer writer.c
   ```

3. Compila el programa reader.c:
   ```bash
   gcc -o reader reader.c
   ```
---
## Uso 🍌🤖
1. Ejecuta el programa reader para prepararlo para recibir datos:
   
   ```bash
   ./reader
    ¡Listo para recibir órdenes, jefe!
   ```
2. Ejecuta el programa writer en otra terminal:

  ```bash
   ./writer
  ```
3. Observa cómo el programa reader registra todo en log.txt y signals.txt. ¡Es como magia minion!


## Archivos generados 📁🍌

- log.txt: Aquí se registran todas las aventuras épicas escritas por el writer.
- signals.txt: Guarda las señales misteriosas (SIGUSR1 y SIGUSR2) que envía el writer.

## Contribuciones 🍌💬
¡Contribuciones son bienvenidas! Si encuentras algún problema, o tienes ideas para mejorar nuestras aventuras, ¡háznoslo saber!

<p align="center" width="100%">
    <img width="60%" src="https://github.com/Kzamudioq/SOPG/assets/138271936/f0635631-1a24-422c-973b-d208f038e643"> 
</p>

---

**¡Diviértete explorando y aprendiendo con este código! 🚀**

