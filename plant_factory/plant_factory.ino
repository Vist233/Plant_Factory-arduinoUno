#include <DHT.h>
#include <Servo.h>
#include <FastLED.h>

#define LED_PIN 2
#define LED_COUNT 10
#define DHTPIN 7
#define DHTTYPE DHT11
// Define pins for the ultrasonic module
const int trigPin = 12; // Ultrasonic module trigger pin
const int echoPin = 13; // Ultrasonic module echo pin
const int buzzerPin = 6; // Buzzer pin
const int moistureSensorPin = 3; // Moisture sensor pin
const int servoPin = 9;          // Servo pin
const int lightSensorPin = A0; // Light sensor pin
const int relayPin = 4;

DHT dht(DHTPIN, DHTTYPE);
Servo servo;
CRGB leds[LED_COUNT];

void setup() {
  pinMode(trigPin, OUTPUT); // Set ultrasonic module trigger pin as output
  pinMode(echoPin, INPUT); // Set ultrasonic module echo pin as input
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  Serial.begin(9600); // Initialize serial communication for debugging

  dht.begin();

  pinMode(moistureSensorPin, INPUT);
  servo.attach(servoPin);
  Serial.begin(9600); // Initialize serial communication

  pinMode(lightSensorPin, INPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.clear();  // Turn off all LEDs
  FastLED.show();

  // Set relay pin as output mode
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Send ultrasonic signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Receive ultrasonic signal and calculate distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // If distance is less than or equal to 20 cm, sound the buzzer
  if (distance <= 4) {
    digitalWrite(buzzerPin, HIGH);
    delay(1000); // Turn on the buzzer
    digitalWrite(buzzerPin, LOW);
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }

  int lightValue = analogRead(lightSensorPin);
  // If the light sensor reads a value less than a certain threshold (indicating no light)
  if (lightValue < 100) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB::White;
    }
    FastLED.show();
    delay(5000);  // Keep the LEDs white for 20 seconds

    // Turn off all LEDs
    FastLED.clear();
    FastLED.show();
  } else {
    // Do nothing
  }

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Print temperature and humidity data to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (humidity < 40.00) {
    // Turn on the relay by setting the pin high
    digitalWrite(relayPin, HIGH);
  } else {
    // Turn off the relay by setting the pin low
    digitalWrite(relayPin, LOW);
    delay(1000); // Delay for 1 second        
  }

  int moistureValue = analogRead(moistureSensorPin);

  // Print moisture data to serial monitor
  Serial.print("Moisture: ");
  Serial.println(moistureValue);

  // If the moisture sensor reads a value greater than a certain threshold (indicating wetness), rotate the servo to a specified angle
  if (moistureValue > 300) {  // Close window when there are water droplets
    servo.write(90); // Rotate the servo to 90 degrees
  } else {
    // If dry, rotate the servo to the initial position (e.g., 0 degrees)
    servo.write(0);
  }

  // If the light sensor reads a value less than a certain threshold (indicating no light), rotate the servo to 60 degrees
  if (lightValue < 100) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB::White;
    }
    FastLED.show();
    delay(5000);  // Keep the LEDs white for 20 seconds

    // Turn off all LEDs
    FastLED.clear();
    FastLED.show();
  } else {
    // Do nothing
  }
}