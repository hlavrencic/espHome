#include "avdweb_VirtualDelay.h"

class Songs{
  public:
    Songs(int pin);
    void StartSong(int *melody, int *noteDurations, int totalMelodies);
    bool Tone();
    bool HasFinished();
    void Finish();
  private:
    int _pin;
    const int BUZZER_CHANNEL = 0;
    VirtualDelay _toneDelay;
    int *_melody;
    int *_noteDurations;
    int _noteIndex;
    int _totalMelodies;
};