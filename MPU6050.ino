#include <Adafruit_MPU6050.h>
#include <math.h>

// Initialize MPU6050
Adafruit_MPU6050 mpu;

// Define a handle for the task
TaskHandle_t TaskMPU6050;

// Calibration offsets
float accelBiasX = 0;
float gyroBiasZ = 0;

// X-axis Speed and Distance variables
float velocityX = 0.0;    // in m/s
float distanceX = 0.0;    // in meters

// Orientation variables
float yaw = 0.0;          // in degrees

// Timing variables
unsigned long lastTime = 0;
float deltaTime = 0.0;

// Filtering coefficients
const float alpha_accel = 0.6;    // Low-pass filter for acceleration
const float alpha_gyro = 0.98;    // Complementary filter coefficient

// Previous acceleration for filtering
float prevAccelX = 0.0;

// Lower the threshold for more sensitivity
const float accelThreshold = 0.01; // m/s², reduced for more sensitivity

void MPU6050Task(void *parameter) {
  for(;;) {
    // Get current time and compute deltaTime
    unsigned long currentTime = millis();
    deltaTime = (currentTime - lastTime) / 1000.0; // Convert to seconds
    lastTime = currentTime;

    // Read sensor data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Apply calibration offsets
    float accelX_raw = a.acceleration.x - accelBiasX;
    float gyroZ_raw = g.gyro.z - gyroBiasZ;

    // Apply low-pass filter to smooth acceleration
    float accelX = alpha_accel * accelX_raw + (1.0 - alpha_accel) * prevAccelX;
    prevAccelX = accelX;

    // Compute speed and distance with drift correction
    computeSpeedAndDistance(accelX_raw, deltaTime);

    // Compute orientation (yaw) using gyroscope
    computeOrientation(gyroZ_raw, deltaTime);

    // Delay between readings (adjust as needed)
    vTaskDelay(100);
  }
}

void computeSpeedAndDistance(float accelX, float deltaTime) {
  // Use absolute value of acceleration to ensure it's always treated as forward
  velocityX += abs(accelX) * deltaTime;

  // Implement zero-velocity update to correct drift
  if (abs(accelX) < accelThreshold) {
    velocityX = 0.0;
  }

  // Integrate velocity to get distance (always positive)
  distanceX += abs(velocityX) * deltaTime;
}

void computeOrientation(float gyroZ, float deltaTime) {
  // Reverse the sign of gyroZ to change the yaw direction
  yaw -= gyroZ * deltaTime * (180.0 / PI); // Convert rad/s to degrees

  // Keep yaw within [0, 360) degrees
  if (yaw >= 360.0)
    yaw -= 360.0;
  else if (yaw < 0.0)
    yaw += 360.0;
}

void MPU6050Setup() {
  // Initialize MPU6050
  mpu.begin();

  // MPU6050 settings
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);     // Set accelerometer range to ±2G
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);          // Set gyroscope range to ±250°/s
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);        // Set filter bandwidth to 5Hz

  // Allow sensor to stabilize
  delay(1000);

  // Perform calibration
  calibrateSensor();

  // Initialize timing
  lastTime = millis();

  // Create the MPU6050 task on Core 1
  xTaskCreatePinnedToCore(
      MPU6050Task,        // Task function
      "MPU6050 Task",     // Task name
      8192,               // Stack size (8 KB)
      NULL,               // Parameter to pass to task
      1,                  // Task priority
      &TaskMPU6050,       // Task handle
      1                   // Core 0 (PRO Core)
  );
}

void calibrateSensor() {
  const int numSamples = 2000;
  float accelX_sum = 0;
  float gyroZ_sum = 0;

  Serial.println("Calibrating... Please keep the RC car stationary.");
  for (int i = 0; i < numSamples; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    accelX_sum += a.acceleration.x;
    gyroZ_sum += g.gyro.z;

    delay(1); // Adjust delay as needed
  }

  // Calculate average biases
  accelBiasX = accelX_sum / numSamples;
  gyroBiasZ = gyroZ_sum / numSamples;

  Serial.println("Calibration complete.");
  Serial.print("Accel X Bias: ");
  Serial.println(accelBiasX);
  Serial.print("Gyro Z Bias: ");
  Serial.println(gyroBiasZ);
}
