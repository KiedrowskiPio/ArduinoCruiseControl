// Numer analogowego pinu do którego podłączony jest potencjometr
#define POTENCJOMETR_PIN 0

void setup()
{
  // Ustawienie komunikacji z komputerem na 57600 bodów
  Serial.begin(57600);

  // Oczekiwanie na uaktywnienie portu w Arduino Leonardo
  while (!Serial);
}

void loop()
{
  // Odczyt wartości z potencjometru
  int value = analogRead(POTENCJOMETR_PIN);

  // Wysłanie wartości do komputera
  Serial.println(value, DEC);

  // Oczekiwanie 20 ms czyli wysyłanie 50x na sekundę
  delay(1000);
}