# Comunicación de Procesos con Named FIFOs 🍌🚀
`Trabajo práctico 1`

¡Hola, amiguitos! Bienvenidos al proyecto de comunicación de procesos usando Named FIFOs. ¡Prepárense para una aventura emocionante en el mundo de los códigos y las bananas! 🍌🎉
---

## Requisitos del Sistema 🖥️

- Sistema operativo minion-compatible (algo como Unix, ¡banana Unix!).
- Compilador de C que hable el idioma minion.
---

## Instrucciones para Compilar 🛠️

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
   ```
  ¡Listo para recibir órdenes, jefe!
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

---

**¡Diviértete explorando y aprendiendo con este código! 🚀**

