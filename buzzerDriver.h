#ifndef buzzerDriver_h
#define buzzerDriver_h

#define PIN_BUZZER 6

#define BZ_BEEP_FREQ_HZ 2000
#define BZ_BEEP_DURATION_MS 100
#define BZ_CHIME_DURATION_MS 1000

void BZ_beep()
{
  tone(PIN_BUZZER,BZ_BEEP_FREQ_HZ,BZ_BEEP_DURATION_MS);
}

void BZ_alarm(bool on)
{
  if(on)
    tone(PIN_BUZZER,BZ_BEEP_FREQ_HZ);
  else
    noTone(PIN_BUZZER);
}

void BZ_init()
{
  pinMode(PIN_BUZZER,OUTPUT);
  BZ_beep();
}

#endif
