#define BUZZER_PIN 12

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    while (true) {
        // Alternate frequencies
        // (600ms)
        for (int i = 0; i < 100; i++) {
            digitalWrite(BUZZER_PIN, HIGH);
            delay(3);
            digitalWrite(BUZZER_PIN, LOW);
            delay(3);
        }

        // (600ms)
        for (int i = 0; i < 60; i++) {
            digitalWrite(BUZZER_PIN, HIGH);
            delay(5);
            digitalWrite(BUZZER_PIN, LOW);
            delay(5);
        }
    }
} 
