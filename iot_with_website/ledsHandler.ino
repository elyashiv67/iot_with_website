
void led_setup(){
  pinMode(redL, OUTPUT);
  pinMode(blueL, OUTPUT);
  pinMode(greenL, OUTPUT);
  pinMode(yellowL, OUTPUT);
}

void changeState(int pin, int state){
  digitalWrite(pin, !state);
}
void leds_loop(){
}
