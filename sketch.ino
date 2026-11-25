// Control de 2 LED por enlace serie (equivalente a un modulo HC-05)
// Comandos: V/v = LED verde on/off, R/r = LED rojo on/off, E = estado
// Respuesta por cada caracter: tiempo_ms,comando,accion,verde,rojo

// Pines de salida (cada LED con resistencia de 220 ohm a GND)
const int ledVerde = 8;
const int ledRojo = 9;

void setup() {
  // Configura los pines de los LED como salidas
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  // 9600 bps, igual al HC-05 en modo de datos
  Serial.begin(9600);

  // Encabezado del registro
  Serial.println("tiempo_ms,comando,accion,verde,rojo");
}

void loop() {
  // Procesa un caracter solo si hay datos disponibles
  if (Serial.available() > 0) {
    char c = Serial.read();

    // Ignora los fines de linea (\n y \r)
    if (c == '\n' || c == '\r') return;

    // Accion por defecto: caracter no valido
    const char* accion = "desconocido";

    if (c == 'V') {            // Enciende el LED verde
      digitalWrite(ledVerde, HIGH);
      accion = "verde_on";
    } else if (c == 'v') {     // Apaga el LED verde
      digitalWrite(ledVerde, LOW);
      accion = "verde_off";
    } else if (c == 'R') {     // Enciende el LED rojo
      digitalWrite(ledRojo, HIGH);
      accion = "rojo_on";
    } else if (c == 'r') {     // Apaga el LED rojo
      digitalWrite(ledRojo, LOW);
      accion = "rojo_off";
    } else if (c == 'E') {     // Consulta el estado sin modificar las salidas
      accion = "estado";
    }

    // Registro: tiempo,comando,accion,estado verde,estado rojo
    Serial.print(millis());
    Serial.print(",");
    Serial.print(c);
    Serial.print(",");
    Serial.print(accion);
    Serial.print(",");
    Serial.print(digitalRead(ledVerde));
    Serial.print(",");
    Serial.println(digitalRead(ledRojo));
  }
}