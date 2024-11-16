#include <AFMotor.h>
const int stepsPerRevolution = 200;


AF_Stepper myStepperX(stepsPerRevolution, 2);

void setup() {
  Serial.begin(9600);
  myStepperX.setSpeed(100); // Устанавливаем скорость двигателя X
  Serial.println("Motor on m3,m4 ports initialized!");
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
  if (command == "=") { // Если команда равна "VPERED"
    VPERED(); // Выполняем функцию
  } else if (command == "-") { // Если команда равна "NAZAD"
    NAZAD();
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

