# EchoQuant_Arduino_Project

Light Automation system with Counter, Ultrasonic Sensors and LCD Display for Energy saving

This project implements a people-counting system using two ultrasonic sensors and an LCD display. It detects entries and exits by monitoring the sequence in which the sensors are triggered and maintains a real-time count of people inside a room. When the count is above zero, a light turns on; otherwise, it remains off.

---
## Table of Contents
1. [Hardware Components]
2. [Circuit & Flowchart]
3. [Software Requirements]
4. [Flowchart Explanation]
5. [Code Breakdown]
    - [1. Libraries and Variable Declarations]
    - [2. Setup Function]
    - [3. Main Loop]
    - [4. Helper Functions]
6. [Usage Instructions]
7. [Contributing]
8. [License]

---
## Hardware Components
- Arduino Uno (or compatible)
- 2 × HC-SR04 Ultrasonic Distance Sensors
- 16×2 LCD Display (with I²C interface)
- 1 × LED (with resistor)
- Jumper wires
- Breadboard

---
## Flowchart Explanation
1. **Start:** Begin execution when the Arduino powers up.
2. **Initialize Modules:** Set pin modes for sensors and LED; initialize LCD and ultrasonic modules.
3. **Measure Distances:** Continuously read distances from Sensor 1 and Sensor 2.
4. **Determine Direction:** 
   - If Sensor 1 is triggered (distance < 10 cm) before Sensor 2, increment the counter (entry).
   - If Sensor 2 is triggered before Sensor 1, decrement the counter (exit).
5. **Update Display:** Show the current count on the LCD.
6. **Control Light:** Turn the LED on if the count > 0; otherwise, turn it off.
7. **Repeat:** Loop back to measuring distances.

---
## Code Breakdown

### 1. Libraries and Variable Declarations
```cpp
#include <LiquidCrystal_I2C.h>     // I2C LCD library

// Ultrasonic sensor pins
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;

// LED indicator pin
const int ledPin = 9;

// Variables for distance measurement
long duration1, distance1;
long duration2, distance2;

// People counter
int peopleCount = 0;

// LCD address 0x27, 16 cols × 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

### 2. Setup Function
```cpp
void setup() {
  // Initialize serial communication (optional)
  Serial.begin(9600);

  // Configure sensor and LED pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Show welcome message
  lcd.setCursor(0, 0);
  lcd.print("People Counter");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}
```

### 3. Main Loop
```cpp
void loop() {
  readDistances();        // Measure both sensors
  updateCounter();        // Adjust counter based on sequence
  displayCount();         // Show count on LCD
  controlLight();         // Turn LED on/off
  delay(200);             // Small delay for stability
}
```

### 4. Helper Functions
```cpp
void readDistances() {
  // Sensor 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Sensor 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
}

void updateCounter() {
  static bool sensor1Triggered = false;
  static bool sensor2Triggered = false;

  if (distance1 < 10 && !sensor1Triggered) {
    sensor1Triggered = true;
  }
  if (distance2 < 10 && sensor1Triggered && !sensor2Triggered) {
    peopleCount++;
    sensor2Triggered = true;
  }
  // Reverse for exit
  if (distance2 < 10 && !sensor2Triggered) {
    sensor2Triggered = true;
  }
  if (distance1 < 10 && sensor2Triggered && !sensor1Triggered) {
    peopleCount = max(0, peopleCount - 1);
    sensor1Triggered = true;
  }
  // Reset triggers when both clear
  if (distance1 > 10 && distance2 > 10) {
    sensor1Triggered = sensor2Triggered = false;
  }
}

void displayCount() {
  lcd.setCursor(0, 0);
  lcd.print("Inside:");
  lcd.setCursor(9, 0);
  lcd.print(peopleCount);
}

void controlLight() {
  if (peopleCount > 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
```

---

## 👨‍💻 Author

**Aakash**  
M.Sc. Physics, IIT Bombay  
Business & Data Analyst | SQL Enthusiast  
📧 aakash.1attri@gmail.com  
