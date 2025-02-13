#include "src/provided/Servo.h"

#define SERVO_PIN 9
#define PRINTF(format, ...) do { \
    char buffer[128]; \
    snprintf(buffer, sizeof(buffer), format, ##__VA_ARGS__); \
    Serial.println(buffer); \
} while (0)

Servo servo;

enum MotorState {
    Ascending,
    Descending
} motor_state;

int motor_angle = 0;
// Valid: [0..180]

void setup()
{
    Serial.begin(9600);
    servo.attach(SERVO_PIN);
}

void loop()
{
    while (Serial.available()) {
        char typed = Serial.read();

        switch (typed) {
            case 'a':
                motor_state = MotorState::Ascending;
                Serial.println("TX: Ascending");
                break;
            case 'd':
                motor_state = MotorState::Descending;
                Serial.println("TX: Descending");
                break;
            case 'r':
                PRINTF("TX: Motor angle = %d degrees", servo.read());
                break;
            case 'R':
                PRINTF("TX: Pulse width = %d microseconds", servo.readMicroseconds());
                break;
        }
    }

    switch (motor_state) {
        case MotorState::Ascending:
            if (motor_angle < 180) {
                motor_angle++;
                update_servo();
            }
            break;
        case MotorState::Descending:
            if (motor_angle > 0) {
                motor_angle--;
                update_servo();
            }
            break;
    }
}

void update_servo()
{
    servo.write(motor_angle);
    delay(15);
}
