#define ECHO_PIN 11
#define TRIGGER_PIN 12

float compute_distance(unsigned int timeout_ms = 50);
unsigned long cm_to_us(float centimeters);
float us_to_cm(unsigned long microseconds);

void setup()
{
    Serial.begin(9600);

    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);

    delay(1000);
}

void loop()
{
    const float distance = compute_distance();

    Serial.print(distance);
    Serial.println("cm");

    delay(1500);
}

float compute_distance(unsigned int timeout_ms)
{
    unsigned long microseconds;

    digitalWrite(TRIGGER_PIN, LOW);     // Ensure pin at rest
    delayMicroseconds(2);               // Wait an instant, stabilize
    digitalWrite(TRIGGER_PIN, HIGH);    // Emit pulse
    delayMicroseconds(10);              // Hold for 10 microseconds
    digitalWrite(TRIGGER_PIN, LOW);     // Stop pulse
    delayMicroseconds(2);               // Wait an instant, stabilize

    // In sync with the emitted wave, the echo pin is set to `HIGH` and will go
    // `LOW` as soon as it detects the return wave.  `pulseIn()` times this
    // round trip (`HIGH` to `LOW`).
    microseconds = pulseIn(ECHO_PIN, HIGH);

    // This function won't work on immediate successive calls, maybe due to
    // residual waves or sensor activity, so enforce a time out
    delay(timeout_ms);

    // Convert the round-trip microseconds to obstacle distance
    return us_to_cm(microseconds);
}

unsigned long cm_to_us(float centimeters)
{
    // Inverse of `us_to_cm()`
    return (2000.0 * centimeters) / 34.0;
}

float us_to_cm(unsigned long microseconds)
{
    // Speed of sound: 340m/s = 34cm/ms
    // `microseconds` represents a round trip, so divide by 2
    return 34.0 * (microseconds / 1000.0) / 2.0;
}
