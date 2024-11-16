#include <AFMotor.h>
#include <Servo.h>

Servo servo;
const int stepsPerRevolution = 200;
AF_Stepper myStepperX(stepsPerRevolution, 2);
int servoPos = 90;  // Начальная позиция сервопривода

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  servo.write(servoPos); // Устанавливаем сервопривод в начальное положение
  myStepperX.setSpeed(100); // Скорость шагового двигателя
  Serial.println("Motor X initialized!");
}

void loop() {
  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n');
    received.trim();
    received.toUpperCase();
    processCommand(received);
  }
}

void processCommand(String command) {
  if (command == "FORWARD_START") {
    myStepperX.onestep(BACKWARD, SINGLE); // Начать движение шаговика вперед
  } else if (command == "BACKWARD_START") {
    myStepperX.onestep(FORWARD, SINGLE); // Начать движение шаговика назад
  } else if (command == "STOP") {
    myStepperX.release(); // Остановить шаговик
  } else if (command == "SERVO_UP") {
    moveServo(1);  // Плавно двигать сервопривод вверх
  } else if (command == "SERVO_DOWN") {
    moveServo(-1); // Плавно двигать сервопривод вниз
  } else if (command == "SERVO_STOP") {
    // Ничего не делаем - это просто для остановки при отпускании кнопки
  }
}

void moveServo(int direction) {
  servoPos += direction;
  servoPos = constrain(servoPos, 0, 120); // Ограничиваем позицию между 0 и 180
  servo.write(servoPos);
  delay(5); // Задержка для плавности
}



