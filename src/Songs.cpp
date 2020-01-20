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
  if(_noteIndex >= _totalMelodies){
    return false;
  }

  if(!_toneDelay.elapsed()){
    return false;
  }

  auto noteDuration = 500/_noteDurations[_noteIndex];
  tone(_pin, _melody[_noteIndex], noteDuration, BUZZER_CHANNEL);
  _toneDelay.start(noteDuration);
  _noteIndex++;

  return true;
}

bool Songs::HasFinished(){
    return _noteIndex >= _totalMelodies;
}

void Songs::Finish(){
    _noteIndex = _totalMelodies;
}
