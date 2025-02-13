#define LED_PIN 5
#define BUTTON_A_PIN 9
#define BUTTON_B_PIN 8

typedef byte PinNumber;

bool led_on = false;

void setup() 
{
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
}

void loop()
{
    if (is_pressed(BUTTON_A_PIN) && !led_on) {
        toggle_led();
    }

    if (is_pressed(BUTTON_B_PIN) && led_on) {
        toggle_led();
    }
}

bool is_pressed(PinNumber button_pin)
{
    return digitalRead(button_pin) == LOW;
}

void toggle_led()
{
    led_on = !led_on;

    if (led_on) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Light on");
    } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("Light off");
    }
}
