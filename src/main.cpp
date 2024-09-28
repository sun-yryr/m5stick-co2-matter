#include <Arduino.h>
#include <M5Unified.h>
#include <MHZ19_uart.h>

#define RX_PIN 36
#define TX_PIN 26

MHZ19_uart mhz19;
m5::rtc_time_t now_t;

void resetScreen();

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  pinMode(36, INPUT);
  gpio_pulldown_dis(GPIO_NUM_25);
  gpio_pullup_dis(GPIO_NUM_25);

  Serial.begin(9600);
  mhz19.begin(RX_PIN, TX_PIN);
  mhz19.setAutoCalibration(true);

  M5.Display.setRotation(1);
  M5.Display.setTextSize(2.5);
  M5.Display.println("Hello. MH-Z19C is warming up.");
  delay(10 * 1000); // データシートから1分の暖機が必要
  resetScreen();
  M5.Display.println("Hello. Setup is ready.");
}

void loop() {
  resetScreen();
  int co2 = mhz19.getCO2PPM();
  int temp = mhz19.getTemperature();
  M5.Display.printf("CO2: %d\n", co2);
  M5.Display.printf("Temp: %d\n", temp);
  // M5.Rtc.getTime(&now_t);
  // M5.Display.printf("time: %02d:%02d:%02d\n", now_t.hours, now_t.minutes, now_t.seconds);
  delay(5 * 1000);
}

void resetScreen() {
  M5.Display.fillScreen(BLACK);
  M5.Display.setCursor(0, 0);
}