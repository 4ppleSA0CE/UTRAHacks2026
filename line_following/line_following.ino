// ===============================
// MODULE 2: IR Line Following Robot
// 2 Sensors: Left + Right
// ===============================

// Motor Driver Pins (L298N)
int ENA = 5;
int IN1 = 8;
int IN2 = 9;

int ENB = 6;
int IN3 = 10;
int IN4 = 11;

// IR Sensors
int IR_Left  = 2;
int IR_Right = 3;

// Speed Settings
int baseSpeed = 170;
float rightCorrection = 1.20;   // adjust from Module 1

void setup() {

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // IR pins
  pinMode(IR_Left, INPUT);
  pinMode(IR_Right, INPUT);

  Serial.begin(9600);
  Serial.println("Line Following Started...");
}

void loop() {

  int leftVal  = digitalRead(IR_Left);
  int rightVal = digitalRead(IR_Right);

  // Print sensor readings
  Serial.print("L: ");
  Serial.print(leftVal);
  Serial.print("  R: ");
  Serial.println(rightVal);

  // ===============================
  // LINE FOLLOWING LOGIC
  // ===============================

  // Case 1: Both sensors on WHITE → go straight
  if (leftVal == HIGH && rightVal == HIGH) {
    driveStraight();
  }

  // Case 2: Left sensor sees BLACK → line is left → turn left
  else if (leftVal == LOW && rightVal == HIGH) {
    turnLeft();
  }

  // Case 3: Right sensor sees BLACK → line is right → turn right
  else if (leftVal == HIGH && rightVal == LOW) {
    turnRight();
  }

  // Case 4: Both sensors see BLACK → stop (at intersection or end)
  else if (leftVal == LOW && rightVal == LOW) {
    stopRobot();
  }
}


// ===============================
// MOTOR CONTROL FUNCTIONS
// ===============================

void driveStraight() {

  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed * rightCorrection);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {

  // Slow left motor, speed up right motor
  analogWrite(ENA, 80);
  analogWrite(ENB, baseSpeed * rightCorrection);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {

  // Slow right motor, speed up left motor
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, 80);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopRobot() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
