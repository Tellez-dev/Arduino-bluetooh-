# Enlace serie tipo Bluetooth con Arduino Uno

Control de dos LED (verde y rojo) con una placa Arduino Uno mediante comandos de un solo carácter enviados por un enlace serie a 9600 bps. El enlace es equivalente al de un módulo Bluetooth HC-05, que actúa como puente serie transparente. El circuito se simuló en Wokwi, donde el monitor serie hace las veces de terminal Bluetooth.

Proyecto de la **Entrega 5** (artículo en formato IEEE): *Enlace serie tipo Bluetooth con Arduino Uno: estado del arte, implementación y pruebas de conectividad en simulación*.

- **Autor:** Jhoan Sebastian Tellez Perez
- **Institución:** Politécnico Grancolombiano
- **Circuito en Wokwi:** https://wokwi.com/projects/481587520199403521

## Contenido del repositorio

| Archivo | Descripción |
|---|---|
| `sketch.ino` | Programa de control, con comentarios |
| `diagram.json` | Descripción del circuito en Wokwi |
| `wokwi-project.txt` | https://wokwi.com/projects/481587520199403521 |
| `registro_monitor_serie.txt` | Registro del monitor serie de una ejecución de prueba (17 registros) |

## Circuito

| Elemento | Conexión |
|---|---|
| LED verde | Pin 8, con resistencia de 220 Ω en serie; cátodo a GND |
| LED rojo | Pin 9, con resistencia de 220 Ω en serie; cátodo a GND |
| Enlace serie | Monitor serie de Wokwi a 9600 bps |

En un montaje físico con HC-05: TXD del módulo al pin 0 (RX) de la placa y RXD del módulo al pin 1 (TX) a través de un divisor de tensión (el pin RX del HC-05 trabaja a 3.3 V). Los pines 0 y 1 comparten el puerto con la conexión USB, así que el módulo debe desconectarse mientras se carga el programa. Otra opción es usar la biblioteca `SoftwareSerial` en otros pines.

## Protocolo de comandos

El terminal envía un carácter por orden. El programa ignora los fines de línea (`\n` y `\r`).

| Comando | Acción |
|---|---|
| `V` / `v` | Enciende / apaga el LED verde |
| `R` / `r` | Enciende / apaga el LED rojo |
| `E` | Consulta el estado de ambos LED sin modificarlos |
| Otro | Responde `desconocido` y no cambia las salidas |

Por cada carácter recibido, el programa responde con una línea de cinco campos:

```
tiempo_ms,comando,accion,verde,rojo
```

Ejemplo: `93002,V,verde_on,1,0`

> El archivo `registro_monitor_serie.txt` corresponde a una ejecución de prueba. Las cifras de la sección de resultados provienen de la ejecución de 79 líneas analizada en el artículo.

## Cómo reproducirlo

1. Abre el circuito en Wokwi con el enlace de arriba. También puedes crear un proyecto nuevo con la placa Arduino Uno y copiar en él `diagram.json` y `sketch.ino` de este repositorio.
2. Revisa que el circuito coincida con la tabla de conexiones.
3. Inicia la simulación.
4. En el campo de entrada del monitor serie, escribe comandos individuales (por ejemplo `V`) o varios caracteres a la vez (por ejemplo `VRvr`).
5. Copia el registro del monitor serie para analizarlo.

## Resultados de las pruebas

- 79 líneas de registro; la simulación se reinició cuatro veces.
- Los 54 comandos válidos dejaron las salidas en el estado esperado.
- Los 25 caracteres no válidos fueron rechazados sin alterar las salidas.
- En envíos de varios caracteres, el intervalo entre comandos procesados se estabilizó en 24.9 ms, frente a los 24.6 ms teóricos de transmitir cada respuesta a 9600 bps. Los intervalos individuales variaron entre 20 y 27 ms.

## Limitaciones

- Wokwi no simula el radioenlace: no hay emparejamiento, pérdida de paquetes ni interferencia.
- `millis()` en Wokwi mide tiempo simulado.
- El análisis de tiempos se basa en dos envíos de 16 caracteres (24 intervalos), por lo que los resultados son indicativos.

Como trabajo futuro se propone repetir las pruebas con un módulo HC-05 físico, un divisor de tensión y un teléfono.

