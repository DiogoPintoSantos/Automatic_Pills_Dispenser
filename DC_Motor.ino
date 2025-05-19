void motor();
void motor() {
  // Set the speed (adjust as needed)
  myStepper.setSpeed(60);
  rotateStepper();
  delay(500);
}

void rotateStepper() {
  // Step sequence to make one full rotation
  myStepper.step(stepsPerRevolution);
}
