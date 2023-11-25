# Comunicación de Procesos con Named FIFOs 🍌🚀
`Trabajo práctico 1`

¡Hola, amiguitos! Bienvenidos al proyecto de comunicación de procesos usando Named FIFOs. ¡Prepárense para una aventura emocionante en el mundo de los códigos y las bananas! 🍌🎉
---

![minions](https://github.com/Kzamudioq/SOPG/assets/138271936/de274c78-c5b1-4ec7-9dfb-88a55dcb7fcb)


## Requisitos del Sistema 🖥️

- Sistema operativo minion-compatible (algo como Unix, ¡banana Unix!).
- Compilador de C que hable el idioma minion.

![friends-clipart-minion-8](https://github.com/Kzamudioq/SOPG/assets/138271936/bb4a8578-0adb-4d01-b9e4-c2181c62017a)

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
![minions_PNG18](https://github.com/Kzamudioq/SOPG/assets/138271936/f0635631-1a24-422c-973b-d208f038e643)

---

**¡Diviértete explorando y aprendiendo con este código! 🚀**

