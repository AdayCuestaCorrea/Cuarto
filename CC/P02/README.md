# PRÁCTICA 2: Programar un simulador de un autómata con pila
## Aday Cuesta Correa - alu0101483887

## Objetivo
El objetivo de la práctica consiste en programar un simulador de un autómata
con pila, realizando un diseño orientado a objetos.

## Como Compilar y Ejecutar el Programa
Gracias al archivo makefile la compilación del programa es sencilla, tan solo escriba en la consola:

```bash
make
```

Y se creará el ejecutable del programa. También puede compilar el programa en modo traza, para ello hay que hacer lo siguiente:

```bash
make traza
```

en ambos casos se creará el mismo ejecutable, para utilizar el programa hay que ejecutar:

```bash
./PushDownAutomata <Nombre_Del_Archivo_Con_El_Autómata>
```