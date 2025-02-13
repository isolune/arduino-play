#define SWITCH_PIN 2

bool current_state = HIGH;
unsigned int debounce_millis = 0;

bool debounce();
bool debounce_done();
void debounce_reset();
void debounce_start();
void set_state(int state);

void setup()
{
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    // Pin state is `HIGH` (off) by default, and `LOW` (on) when the ball in
    // the switch is prong-side and completes the circuit
}

void loop()
{
    const int state = digitalRead(SWITCH_PIN);

    if (state != current_state) {
        // "Switch bouncing" will cause rapid-fire on-off behavior on switch
        // state transition (not perceptible on the LED) until the connection
        // is stable
        //
        // This logic "debounces" the switch firmware-side by doing nothing
        // until the switch is steady for a time (50ms)
        if (debounce()) {
            set_state(state);
        }
    } else {
        debounce_reset();
    }
}

bool debounce()
{
    if (debounce_millis == 0) {
        debounce_start();
    } else if (debounce_done()) {
        debounce_reset();
        return true;
    }

    return false;
}

bool debounce_done()
{
    return millis() - debounce_millis > 50;
    // `true` if > 50ms elapsed since `debounce_start()`
}

void debounce_reset()
{
    debounce_millis = 0;
}

void debounce_start()
{
    debounce_millis = millis();
}

void set_state(int state)
{
    if (state == LOW) {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("TX: On");
    } else {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("TX: Off");
    }

    current_state = state;
}

