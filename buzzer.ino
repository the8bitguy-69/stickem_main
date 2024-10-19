const int BUZZER_PIN = 25;  // Buzzer connected to GPIO 25

int BuzzerChannel = 8; // Use LEDC channel 8 for the buzzer

void BuzzerSetup() {
  ledcSetup(BuzzerChannel, 1000, 8);  // Set the buzzer to use LEDC channel 8 with 2 kHz frequency and 8-bit resolution
  ledcAttachPin(BUZZER_PIN, BuzzerChannel);  // Attach the buzzer pin to the LEDC channel
}

void buzzerTone(int frequency, int duration) {
  ledcWriteTone(BuzzerChannel, frequency);  // Generate the tone on the buzzer
  delay(duration);  // Play the tone for the specified duration
  ledcWriteTone(BuzzerChannel, 0);  // Stop the tone after the duration
}
