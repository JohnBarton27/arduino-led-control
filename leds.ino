#include <FastLED.h>

// Define the number of LEDs in your strand
#define NUM_LEDS 572
#define PITCH_END 423
#define GARAGE_END 200

// Define the data pin for your LED strand
#define DATA_PIN 7

// Create an array of CRGB objects to represent each LED
CRGB leds[NUM_LEDS];

// Set the stripe width (adjust as needed)
int stripeWidth = 10; // Change this value to adjust the width of the stripes

void setup() {
  Serial.begin(9600);
  // Initialize FastLED with the LED data pin
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  set_full_color(0, 0, 0);
}

void demo() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0);
  }
  FastLED.show();
  delay(1000);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 255, 0);
  }
  FastLED.show();
  delay(1000);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 255);
  }
  FastLED.show();
  delay(1000);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(1000);
}

void set_garage(int r, int g, int b) {
  for (int i = 0; i < GARAGE_END; i++) {
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
}

void wipe(int r, int g, int b, bool reverse) {
  if (reverse) {
    for (int i = NUM_LEDS; i >= 0; i -= 2) {
      leds[i] = CRGB(r, g, b);
      if (i >= 1) {
        leds[i-1] = CRGB(r, g, b);
      }
      FastLED.show();
    } 
  } else {
    for (int i = 0; i < NUM_LEDS; i += 2) {
      leds[i] = CRGB(r, g, b);
      leds[i+1] = CRGB(r, g, b);
      FastLED.show();
    }
  }
}

void red_green_wipe() {
  while (true) {
    wipe(255, 0, 0, false);
    delay(2000);
    wipe(0, 255, 0, true);
    delay(2000);
  }
}

void candy_cane(int stripe_width) {
  int offset = 0;

  for (int i = 0; i < NUM_LEDS; i++) {
    int num_to_check = (i + offset) / stripe_width;
    if (num_to_check % 2 == 0) {
        leds[i] = CRGB(255, 0, 0);  // Red
    } else {
        leds[i] = CRGB(255, 255, 255); // White
    }
  }
  FastLED.show();
}

void amber_twinkle() {
  // 255, 120, 10
  int start_r = 64;
  int start_g = 30;
  int start_b = 2;
  int target_r = 255;
  int target_g = 120;
  int target_b = 10;

  int fade_steps = 25;

  set_full_color(0, 0, 0);
  for (int i = 0; i < NUM_LEDS; i += 3) {
    leds[i] = CRGB(start_r, start_g, start_b);
  }

  FastLED.show();

  while (true) {
    int num_sparkles = random(30, 80);
    int sparkle_indices[num_sparkles];

    for (int i = 0; i < num_sparkles; i++) {
      int randomIndex = random((NUM_LEDS / 3) + 1);
      sparkle_indices[i] = randomIndex * 3;
    }

    float r_per_step = (float(target_r) - start_r) / fade_steps;
    float g_per_step = (float(target_g) - start_g) / fade_steps;
    float b_per_step = (float(target_b) - start_b) / fade_steps;

    // Fade to white
    for (float i = 0.0; i < fade_steps; i++) {
      for (int s = 0; s < num_sparkles; s++) {
        leds[sparkle_indices[s]] = CRGB(start_r + (r_per_step * i), start_g + (g_per_step * i), start_b + (b_per_step * i));
      }
      FastLED.show();
    }
    for (int s = 0; s < num_sparkles; s++) {
      leds[sparkle_indices[s]] = CRGB(target_r, target_g, target_b);
    }
    FastLED.show();

    delay(100);
    // Fade back to amber
    for (float i = 0; i < fade_steps; i++) {
      for (int s = 0; s < num_sparkles; s++) {
        leds[sparkle_indices[s]] = CRGB(target_r - (r_per_step * i), target_g - (g_per_step * i), target_b - (b_per_step * i));
      }
      FastLED.show();
    }

    for (int s = 0; s < num_sparkles; s++) {
      leds[sparkle_indices[s]] = CRGB(start_r, start_g, start_b);
    }
    FastLED.show();

    delay(1000);
  }
}

void set_full_color(int r, int g, int b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
}

void fade(int r, int g, int b) {
  int num_steps = 100;
  
  // Fade In
  for (int step = 0; step < num_steps; step++) {
    set_full_color(r / num_steps * step, g / num_steps * step, b / num_steps * step);
    delay(2);
  }
  set_full_color(r, g, b);

  delay(1000);

  // Fade Out
  for (int step = num_steps; step > 0; step--) {
    set_full_color(r / num_steps * step, g / num_steps * step, b / num_steps * step);
    delay(2);
  }
  set_full_color(0, 0, 0);

  delay(1000);
}

void loop() {

  // demo();
  // set_full_color(255, 255, 255);
  // delay(1000);


  candy_cane(10);
  // amber_twinkle();
  delay(20000);

  // fade(255, 255, 255);
  // fade(255, 0, 0);
  // fade(0, 255, 0);
  // fade(0, 0, 255);
}