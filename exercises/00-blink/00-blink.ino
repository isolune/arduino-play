bool on = true;

void setup()
{
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    while (Serial.available()) {
        Serial.print("RX: ");
        Serial.println((char) Serial.read());
    }

    on = !on;

    if (on) {
        Serial.println("TX: On");
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        Serial.println("TX: Off");
        digitalWrite(LED_BUILTIN, LOW);
    }

    delay(3000);
}

