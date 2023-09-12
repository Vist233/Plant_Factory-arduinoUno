#include <DHT.h>
#include <Servo.h>
#include <FastLED.h>

#define LED_PIN 2
#define LED_COUNT 10
#define DHTPIN 7
#define DHTTYPE DHT11
// 定义超声波模块的引脚
const int trigPin = 12; // 超声波模块的发送引脚
const int echoPin = 13; // 超声波模块的接收引脚
const int buzzerPin = 6; // 蜂鸣器的引脚
const int moistureSensorPin = 3; // 水分传感器引脚
const int servoPin = 9;          // 舵
const int lightSensorPin = A0; // 光传感器引脚
const int relayPin = 4;

DHT dht(DHTPIN, DHTTYPE);
Servo servo;
CRGB leds[LED_COUNT];

void setup() {
  pinMode(trigPin, OUTPUT); // 设置超声波模块发送引脚为输出
  pinMode(echoPin, INPUT); // 设置超声波模块接收引脚为输入
  pinMode(buzzerPin, OUTPUT); // 设置蜂鸣器引脚为输出
  Serial.begin(9600); // 初始化串口通信，用于调试

  dht.begin();

  pinMode(moistureSensorPin, INPUT);
  servo.attach(servoPin);
  Serial.begin(9600); // 初始化串口通信

  pinMode(lightSensorPin, INPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.clear();  // 关闭所有LED
  FastLED.show();

  // 将继电器引脚设置为输出模式
  pinMode(relayPin, OUTPUT);
}


void loop() {
  // 发送超声波信号
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 接收超声波信号并计算距离
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // 打印距离到串口
  Serial.print("Distance: ");
  Serial.println(distance);

  // 如果距离小于等于20厘米，则发出声音
  if (distance <= 4) {
    digitalWrite(buzzerPin, HIGH);
    delay(1000); // 打开蜂鸣器
    digitalWrite(buzzerPin, LOW);
  } else {
    digitalWrite(buzzerPin, LOW); // 关闭蜂鸣器
  }


  int lightValue = analogRead(lightSensorPin);
  // 如果光传感器读取的值小于某个阈值（表示没有光）
  if (lightValue < 100) {
    for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
  delay(5000);  // 保持白色亮20秒

  // 关闭所有LED
  FastLED.clear();
  FastLED.show();
  } else {


  }

  // delay(100);







  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // 打印温湿度数据到串口显示器
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (humidity < 40.00) {
    // 打开继电器，将引脚设置为高电平
    digitalWrite(relayPin, HIGH);


  } else {
    // 关闭继电器，将引脚设置为低电平
    digitalWrite(relayPin, LOW);
    delay(1000); // 延迟1秒        
  }



  int moistureValue = analogRead(moistureSensorPin);

  // 打印水分数据到串口显示器
  Serial.print("Moisture: ");
  Serial.println(moistureValue);

  // 如果水分传感器读取的值大于某个阈值（表示湿润），则舵机旋转到指定角度
  if (moistureValue > 300) {  // 关窗时候的水滴
    servo.write(90); // 舵机旋转到90度的位置
  } else {
    // 如果干燥，则舵机旋转到初始位置（例如0度）
    servo.write(0);
  }







  // 如果光传感器读取的值小于某个阈值（表示没有光），则舵机旋转到60度
  if (lightValue < 100) {
    for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
  delay(5000);  // 保持白色亮20秒

  // 关闭所有LED
  FastLED.clear();
  FastLED.show();
  } else {


  }

  // delay(100);
}

