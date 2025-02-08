#define RED_PIN_NO 6
#define GREEN_PIN_NO 5
#define BLUE_PIN_NO 3

enum Color {
    Red,
    Green,
    Blue,
};

typedef unsigned int Milliseconds;
typedef byte PinNumber, PinValue;

class Pin {
public:
    static const Milliseconds FadeDelay = 10;

    PinNumber pin;
    Color color;
    PinValue value;

    Pin(PinNumber pin, Color color, PinValue value)
        : pin(pin), color(color), value(value)
    {
        // Unsure if too early to `prepare()` (pre-setup)
    }

    static Pin On(PinNumber pin, Color color)
    {
        return Pin(pin, color, 255);
    }

    static Pin Off(PinNumber pin, Color color)
    {
        return Pin(pin, color, 0);
    }

    void fade_to(Pin* pair)
    {
        while (this->value) {
            this->write(this->value - 1);
            pair->write(pair->value + 1);

            delay(Pin::FadeDelay);
        }
    }

    void prepare()
    {
        pinMode(this->pin, OUTPUT);

        this->write(this->value);
    }

    void update()
    {
        analogWrite(this->pin, this->value);
    }

    void write(byte value)
    {
        this->value = value;
        this->update();
    }
};

Pin red   = Pin::On(RED_PIN_NO,    Red);
Pin blue  = Pin::Off(BLUE_PIN_NO,  Blue);
Pin green = Pin::Off(GREEN_PIN_NO, Green);

void setup()
{
    Serial.begin(9600);
    Serial.println();

    red.prepare();
    green.prepare();
    blue.prepare();
}

void loop()
{
    Serial.println("R->G");
    red.fade_to(&green);
    Serial.println("G->B");
    green.fade_to(&blue);
    Serial.println("B->R");
    blue.fade_to(&red);
}

