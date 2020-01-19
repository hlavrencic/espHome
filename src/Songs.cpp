#include "Songs.h"
#include "Tone32.h"

Songs::Songs(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
};

void Songs::StartSong(int *melody, int *noteDurations, int totalMelodies){
  _noteIndex = 0;
  _melody = melody;
  _noteDurations = noteDurations;
  _totalMelodies = totalMelodies;
  _toneDelay.start(1);
};

bool Songs::Tone(){
  if (_toneDelay.elapsed() && _noteIndex < _totalMelodies) { // Loop through the notes in the array.
    auto noteDuration = 500/_noteDurations[_noteIndex];
    //NewTone(TONE_PIN, melody[thisNote], noteDuration); // Play thisNote for noteDuration.
    tone(_pin, _melody[_noteIndex], noteDuration, BUZZER_CHANNEL);
    //delay(noteDuration); // Wait while the tone plays in the background, plus another 33% delay between notes.
    _toneDelay.start(noteDuration);
    _noteIndex++;

    return true;
  }

  return false;
}

bool Songs::HasFinished(){
    return _noteIndex >= _totalMelodies;
}

void Songs::Finish(){
    _noteIndex = _totalMelodies;
}
