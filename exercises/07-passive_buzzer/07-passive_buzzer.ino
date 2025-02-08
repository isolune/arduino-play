#include "pitches.h"

#define BUZZER_PIN 8
#define TEMPO 400

typedef unsigned int Milliseconds, Pitch;
typedef byte Beats;

class Note {
public:
    Pitch pitch;
    Beats beats;

    Note(Pitch pitch, Beats beats)
        : pitch(pitch), beats(beats)
    {
        // Pass
    }

    Note(Beats beats)
        : pitch(0), beats(beats)
    {
        // Pass
    }

    void play()
    {
        Milliseconds duration = this->beats * TEMPO;

        if (this->pitch) {
            tone(BUZZER_PIN, this->pitch, duration);
        }

        delay(duration);
    }
};

class Melody {
public:
    Note* notes;
    size_t length;

    Melody(Note notes[], size_t length)
        : notes(notes), length(length)
    {
        // Pass
    }

    void play()
    {
        for (size_t i = 0; i < this->length; i++) {
            Note note = this->notes[i];
            Serial.print("Playing: ");
            Serial.println(note.pitch);
            note.play();
        }
    }

    template <typename T, size_t N>
    static constexpr size_t count(T (&)[N])
    {
        return N;
    }
};

Note notes[] = {
    Note(NOTE_D3, 2),
    Note(NOTE_F3, 2),
    Note(NOTE_E3, 2),
    Note(NOTE_G3, 2),
    Note(10),
    Note(NOTE_G3, 2),
    Note(NOTE_F3, 2),
    Note(NOTE_G3, 1),
    Note(NOTE_A3, 1),
    Note(NOTE_D3, 2),
    Note(14),
};

Melody melody = Melody(notes, Melody::count(notes));

void setup()
{
    Serial.begin(9600);
    Serial.print("\nNote count: ");
    Serial.println(melody.length);
}

void loop()
{
    melody.play();
}
