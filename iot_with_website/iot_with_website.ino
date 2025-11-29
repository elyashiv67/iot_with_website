const int redL = 5;
const int blueL = 4;
const int greenL = 0;
const int yellowL = 2;

int redState = 0;
int blueState = 0;
int greenState = 0;
int yellowState = 0;

void setup() {
  // put your setup code here, to run once:
  wifi_setup();
  led_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  wifi_loop();
}
