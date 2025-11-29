
void led_setup(){
  pinMode(redL, OUTPUT);
  pinMode(blueL, OUTPUT);
  pinMode(greenL, OUTPUT);
  pinMode(yellowL, OUTPUT);
}

void changeRedState(int state){
  digitalWrite(redL, state);
  redState = state;
}
void changeBlueState(int state){
  digitalWrite(blueL, state);
  blueState = state;
}
void changeGreenState(int state){
  digitalWrite(greenL,state);
  greenState = state;
}
void changeYellowState(int state){
  digitalWrite(yellowL, state);
  yellowState = state;
}
void leds_loop(){
}
