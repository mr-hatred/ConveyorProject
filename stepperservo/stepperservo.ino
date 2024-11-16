#include <AFMotor.h>
#include <Servo.h>
Servo servo;
const int stepsPerRevolution = 200;


AF_Stepper myStepperX(stepsPerRevolution, 2);

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  myStepperX.setSpeed(100); // Устанавливаем скорость двигателя X
  Serial.println("Motor X initialized!");
  VPERED();
  NAZAD();
}

void loop() {
  if (Serial.available() > 0) {  // Проверяем, есть ли входящие данные
    String received = Serial.readStringUntil('\n'); // Читаем строку до символа новой строки
    received.trim();        // Удаляем пробелы и лишние символы
    received.toUpperCase(); // Приводим к верхнему регистру
    processCommand(received); // Передаем обработанную команду
  }
}

void processCommand(String command) {
  if (command == "+") { // Если команда равна "VPERED"
    VPERED(); // Выполняем функцию
  } else if (command == "-") { // Если команда равна "NAZAD"
    NAZAD();
  } else if (command == "=") { 
    VPERED();
  } else if (command == "S") { 
    servonazad();
  } else {
    Serial.println("Неизвестная команда: " + command);
  }
}

// Пример функции, которая выполняется по команде
void VPERED() {
  Serial.println("Moving X forward");
  myStepperX.step(200, FORWARD, SINGLE);
}

void NAZAD() {
  Serial.println("Moving X backward");
  myStepperX.step(200, BACKWARD, SINGLE);
}

void servovpered() {
  servo.write(0);
}
void servonazad() {
  servo.write(90);
}


