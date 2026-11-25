const int ledVerde = 8;
const int ledRojo = 9;

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  Serial.begin(9600);          // velocidad por defecto del HC-05 en modo datos
  Serial.println("tiempo_ms,comando,accion,verde,rojo");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') return;   // ignora el fin de línea

    const char* accion = "desconocido";
    if (c == 'V') { digitalWrite(ledVerde, HIGH); accion = "verde_on"; }
    else if (c == 'v') { digitalWrite(ledVerde, LOW); accion = "verde_off"; }
    else if (c == 'R') { digitalWrite(ledRojo, HIGH); accion = "rojo_on"; }
    else if (c == 'r') { digitalWrite(ledRojo, LOW); accion = "rojo_off"; }
    else if (c == 'E') { accion = "estado"; }

    Serial.print(millis());   Serial.print(",");
    Serial.print(c);          Serial.print(",");
    Serial.print(accion);     Serial.print(",");
    Serial.print(digitalRead(ledVerde)); Serial.print(",");
    Serial.println(digitalRead(ledRojo));
  }
}|  