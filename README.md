# Plant Factory in Arduino

This project is a smart home system that uses various sensors and actuators to monitor and control the environment. The system includes an ultrasonic sensor, a DHT11 temperature and humidity sensor, a moisture sensor, a light sensor, a servo motor, a buzzer, an LED strip, and a relay.

![Plant Factory](fig/Plant%20Factory.jpg)

## Components

- **Ultrasonic Sensor (HC-SR04)**: Measures distance to detect obstacles.
- **DHT11 Sensor**: Measures temperature and humidity.
- **Moisture Sensor**: Measures soil moisture level.
- **Light Sensor**: Detects ambient light levels.
- **Servo Motor**: Controls mechanical movement (e.g., opening/closing a window).
- **Buzzer**: Provides audible alerts.
- **LED Strip (WS2812)**: Provides visual feedback.
- **Relay**: Controls high-power devices.

## Pin Configuration

- `trigPin (12)`: Ultrasonic sensor trigger pin
- `echoPin (13)`: Ultrasonic sensor echo pin
- `buzzerPin (6)`: Buzzer pin
- `moistureSensorPin (3)`: Moisture sensor pin
- `servoPin (9)`: Servo motor pin
- `lightSensorPin (A0)`: Light sensor pin
- `relayPin (4)`: Relay pin
- `LED_PIN (2)`: LED strip data pin
- `LED_COUNT (10)`: Number of LEDs in the strip
- `DHTPIN (7)`: DHT11 sensor pin
- `DHTTYPE (DHT11)`: DHT11 sensor type

## Setup

1. Connect the components to the corresponding pins on the Arduino board.
2. Install the necessary libraries:
   - `DHT.h`
   - `Servo.h`
   - `FastLED.h`
3. Upload the code to the Arduino board.

## Code Explanation

- **Ultrasonic Sensor**: Measures the distance to an object and triggers the buzzer if the distance is less than or equal to 4 cm.
- **Light Sensor**: Turns on the LED strip if the ambient light is below a certain threshold.
- **DHT11 Sensor**: Reads temperature and humidity values and controls the relay based on humidity levels.
- **Moisture Sensor**: Reads soil moisture levels and controls the servo motor to open/close a window based on the moisture level.
- **LED Strip**: Provides visual feedback based on the light sensor readings.

## Usage

1. Power on the Arduino board.
2. The system will start monitoring the environment using the connected sensors.
3. The buzzer will sound if an object is detected within 4 cm.
4. The LED strip will turn on if the ambient light is below the threshold.
5. The relay will be activated if the humidity is below 40%.
6. The servo motor will adjust based on the soil moisture level.

## Grove Develop Kit

![Grove Develop Kit](./fig/Grove%20Develop%20Kit.jpg)


## License

This project is licensed under the MIT License. See the LICENSE file for more details.

## Acknowledgments

- [DHT Sensor Library](vscode-file://vscode-app/c:/Users/86138/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html)
- [FastLED Library](vscode-file://vscode-app/c:/Users/86138/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html)
- [Servo Library](vscode-file://vscode-app/c:/Users/86138/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html)

Feel free to modify and expand this project to suit your needs. Happy coding!
