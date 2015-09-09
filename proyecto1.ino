#include "pitches.h"

// Score
const char led_e = 10; // e
const char led_d = 3; // d
const char led_c = 4; // c
const char led_dp = 5; // digital point
const char led_b = 6; // b
const char led_a = 7; // a
const char led_f = 8; // f
const char led_g = 9; // g

// balero
const char speaker_melody = 11;
const char light_potency = 1;

// visual out
const char led_win = 12;
const char led_lose = 13;

// game states
const char NONE = 0;
const char SETUP = 1;
const char IN_GAME = 2;
const char WAITING = 3;
const char WIN = 4;
const char LOSE = 5;

// time vars
long timeToPlay = 15000;
unsigned long timeOnDark = 0;
unsigned long lastTimeRead;

// songs
int start_melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int duration[] = {4, 8, 8, 4, 4, 4, 4, 4};

// vars
char state = SETUP;
char score = 0;
int light_read = 0;

void setup() {
  Serial.begin(9600);
  lastTimeRead = millis();
  //Score
  pinMode(led_e,OUTPUT);
  pinMode(led_d,OUTPUT);
  pinMode(led_c,OUTPUT);
  pinMode(led_dp,OUTPUT);
  pinMode(led_b,OUTPUT);
  pinMode(led_a,OUTPUT);
  pinMode(led_f,OUTPUT);
  pinMode(led_g,OUTPUT);

  digitalWrite(led_e, LOW);
  digitalWrite(led_d, LOW);
  digitalWrite(led_c, LOW);
  digitalWrite(led_dp, LOW);
  digitalWrite(led_b, LOW);
  digitalWrite(led_a, LOW);
  digitalWrite(led_f, LOW);
  digitalWrite(led_g, LOW);

  // Leds
  pinMode(led_win,OUTPUT);
  pinMode(led_lose,OUTPUT);

  // Speakers
  pinMode(speaker_melody,OUTPUT);
}

unsigned long delta() {
  unsigned long deltaTime = lastTimeRead - millis();
  lasTimeRead = millis();
  return deltaTime;
}

bool has_time(unsigned long deltaTime) {
  timeToPlay -= deltaTime;
  if(timeToPlay <= 0)
  {
    if(score > 0)
    {
      state = WIN;
    }
    else
    {
      state = LOSE;
    }
    return false;
  }

  return true;
}

void loop() {
  unsigned long deltaTime = delta();
  switch (state)
  {
    case IN_GAME:
      if (has_time(deltaTime))
      {
        light_read = analogRead(light_potency);
        light_read = map(light_read,0,1023,0,255);
        // Serial.println(light_read);
        if (light_read < 32)
        {
          timeOnDark += deltaTime;
          if(timeOnDark > 2000)
          {
            score++;
            display_number(score % 10);
            timeOnDark = 0;
            state = WAITING;
          }
        }
        else
        {
          timeOnDark = 0;
        }
      }
      break;

    case WAITING:
      if (has_time(deltaTime))
      {
        light_read = analogRead(light_potency);
        light_read = map(light_read,0,1023,0,255);
        if (light_read > 200)
        {
          state = IN_GAME;
        }
      }
      break;

    case WIN:
      // play win sound
      // flash win led
      break;

    case LOSE:
      // play lose sound
      // flash lose led
      break;

    case SETUP:
      score = 0;
      display_number(score);
      play_sound(melody, duration, 8, speaker_melody);
      state = IN_GAME;
      break;

    case NONE:
    default:
      break;
  }
}

void display_number(char num) {
  switch(num)
  {
    case 0:
      digitalWrite(led_e, HIGH);
      digitalWrite(led_d, HIGH);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, HIGH);
      digitalWrite(led_a, HIGH);
      digitalWrite(led_f, HIGH);
      digitalWrite(led_g, LOW);
      break;
    case 1:
      digitalWrite(led_e, LOW);
      digitalWrite(led_d, LOW);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, HIGH);
      digitalWrite(led_a, LOW);
      digitalWrite(led_f, LOW);
      digitalWrite(led_g, LOW);
      break;
    case 2:
      digitalWrite(led_e, HIGH);
      digitalWrite(led_d, HIGH);
      digitalWrite(led_c, LOW);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, HIGH);
      digitalWrite(led_a, HIGH);
      digitalWrite(led_f, LOW);
      digitalWrite(led_g, HIGH);
      break;
    case 3:
      digitalWrite(led_e, LOW);
      digitalWrite(led_d, HIGH);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, HIGH);
      digitalWrite(led_a, HIGH);
      digitalWrite(led_f, LOW);
      digitalWrite(led_g, HIGH);
      break;
    case 4:
      digitalWrite(led_e, LOW);
      digitalWrite(led_d, LOW);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, HIGH);
      digitalWrite(led_a, LOW);
      digitalWrite(led_f, HIGH);
      digitalWrite(led_g, HIGH);
      break;
    case 5:
      digitalWrite(led_e, LOW);
      digitalWrite(led_d, HIGH);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, LOW);
      digitalWrite(led_a, HIGH);
      digitalWrite(led_f, HIGH);
      digitalWrite(led_g, HIGH);
      break;
    case 6:
      digitalWrite(led_e, HIGH);
      digitalWrite(led_d, HIGH);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, LOW);
      digitalWrite(led_a, HIGH);
      digitalWrite(led_f, HIGH);
      digitalWrite(led_g, HIGH);
      break;
    case 7:
      digitalWrite(led_e, LOW);
      digitalWrite(led_d, LOW);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, HIGH);
      digitalWrite(led_a, HIGH);
      digitalWrite(led_f, LOW);
      digitalWrite(led_g, LOW);
      break;
    case 8:
      digitalWrite(led_e, HIGH);
      digitalWrite(led_d, HIGH);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, HIGH);
      digitalWrite(led_a, HIGH);
      digitalWrite(led_f, HIGH);
      digitalWrite(led_g, HIGH);
      break;
    case 9:
      digitalWrite(led_e, LOW);
      digitalWrite(led_d, HIGH);
      digitalWrite(led_c, HIGH);
      digitalWrite(led_dp, LOW);
      digitalWrite(led_b, HIGH);
      digitalWrite(led_a, HIGH);
      digitalWrite(led_f, HIGH);
      digitalWrite(led_g, HIGH);
      break;
    default:
      digitalWrite(led_e, LOW);
      digitalWrite(led_d, LOW);
      digitalWrite(led_c, LOW);
      digitalWrite(led_dp, HIGH);
      digitalWrite(led_b, LOW);
      digitalWrite(led_a, LOW);
      digitalWrite(led_f, LOW);
      digitalWrite(led_g, LOW);
  }
}

void play_sound(int* melody, int* duration, int m_size, char speaker_pin) {
  for (int note = 0; note < m_size; note++)
  {
    int note_duration = 1000/duration[note];
    tone(speaker_pin, melody[note], note_duration);
    int pause_note = note_duration * 1.3;
    delay(pause_note);
    noTone(speaker_pin);
  }
}
