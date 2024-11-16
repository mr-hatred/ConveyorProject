import serial
import time
import keyboard

# Настраиваем серийное соединение с Arduino
arduino = serial.Serial('COM9', 9600, timeout=1)
time.sleep(2)  # Даем время на установление соединения

print("Используйте стрелки для управления моторами. Нажмите ESC для выхода.")

try:
    while True:
        # Проверка нажатий клавиш и отправка команд
        if keyboard.is_pressed('up'):
            arduino.write(b'SERVO_UP\n')  # Плавное движение сервопривода вверх
        elif keyboard.is_pressed('down'):
            arduino.write(b'SERVO_DOWN\n')  # Плавное движение сервопривода вниз
        elif keyboard.is_pressed('left'):
            arduino.write(b'FORWARD_START\n')  # Движение шаговика вперед
        elif keyboard.is_pressed('right'):
            arduino.write(b'BACKWARD_START\n')  # Движение шаговика назад
        else:
            arduino.write(b'SERVO_STOP\n')  # Остановка сервопривода
            arduino.write(b'STOP\n')        # Остановка шаговика

        # Выход по ESC
        if keyboard.is_pressed('esc'):
            print("Завершаем управление...")
            break

finally:
    arduino.close()  # Закрываем соединение
