const int servoPins[] = {2, 4, 17, 16, 5, 18, 19, 23};  // Array of servo pins

const int ledcChannels[] = {0, 1, 2, 3, 4, 5, 6, 7};   // Array of LEDC channels for each servo
const int frequency = 50;                              // Frequency for the servo (50Hz for standard servo)
const int resolution = 16;                             // Resolution of the PWM (16-bit)

const int minPulseWidth = 1000;  // Minimum pulse width in microseconds (1ms)
const int maxPulseWidth = 2000;  // Maximum pulse width in microseconds (2ms)
const int pwmPeriod = 20000;     // Period of the PWM signal in microseconds (50Hz = 20ms)

// Convert 1000-2000 value to 16-bit duty cycle for the LEDC
int convertToDutyCycle(int pulseWidth) {
  return (pulseWidth * 65535) / pwmPeriod;  // Scale the 1000-2000 value to 16-bit PWM duty cycle
}

// Attach all servos
void ServoAttach() {
  // Initialize LEDC for all servos
  for (int i = 0; i < 8; i++) {
    ledcSetup(ledcChannels[i], frequency, resolution);    // Set up each channel
    ledcAttachPin(servoPins[i], ledcChannels[i]);         // Attach each pin to corresponding channel
  }
}

// Detach all servos
void ServoDetach() {
  for (int i = 0; i < 8; i++) {
    ledcDetachPin(servoPins[i]);                          // Detach each servo pin from LEDC
  }
}

// Control individual servo by specifying the channel and pulse width
void controlServo(int channel, int pulseWidth) {
  int dutyCycle = convertToDutyCycle(pulseWidth);         // Convert pulse width to duty cycle
  ledcWrite(channel, dutyCycle);                          // Write duty cycle to the specified channel
}
