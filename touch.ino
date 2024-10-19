const int Touch1_Pin = 27;
const int Touch2_Pin = 33;

// Touch sensor threshold
#define threshold 20

// Flags for touch detection
volatile int touch1detected = 0;
volatile int touch2detected = 0;

void TouchSetup() {
  touchAttachInterrupt(Touch1_Pin, gotTouch1, threshold);
  touchAttachInterrupt(Touch2_Pin, gotTouch2, threshold);
}

void gotTouch1() {
  touch1detected = 1;
}

void gotTouch2() {
  touch2detected = 1;
}

void resetTouch() {
  if(touchRead(Touch1_Pin) > threshold){
    touch1detected = 0;
  }
  if(touchRead(Touch2_Pin) > threshold){
    touch2detected = 0;
  }
}
