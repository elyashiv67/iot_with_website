const int redL = 1;
const int blueL = 2;
const int greenL = 3;
const int yellowL = 4;

int redState = LOW;
int blueState = LOW;
int greenState = LOW;
int yellowState = LOW;

void setup() {
  // put your setup code here, to run once:
  wifi_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  wifi_loop();
}
