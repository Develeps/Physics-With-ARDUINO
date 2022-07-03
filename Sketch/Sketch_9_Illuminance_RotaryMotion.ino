/* Illuminance&RotaryMotion
 Этот скетч определяет зависимость освещённости на выходе
 двух поляризаторов при их взаимном повороте. Угол поворота
 контролируется датчиком вращательного движения Vernier, 
 который возвращает угловое значение каждые 0,5 с. Включен
 режим высокого разрешения (изменения на 0,25 градуса).
 Датчик вращательного движения вставляется в цифровой порт
 Digital 1 интерфейсного шилда Vernier Arduino.
 */
#include "VernierLib.h"
VernierLib Vernier;
int size1=30;
boolean highResOn = true; // глобальная переменная для режима разрешения (normal=false, high=true)
float angleChange; // глобальная переменная для угловых показаний
const int encoderPinCCW = 2; // глобальная переменная для связывания вывода с направлением вращения против часовой стрелки
const int encoderPinCW = 3; // глобальная переменная для связывания вывода с направлением вращения по часовой стрелке
const int resPin = 5; // глобальная переменная для связывания вывода с режимом разрешения
volatile int encoderPos = 0; // глобальная переменная для связывания вывода с положением (переменные, измененные
// в прерываниях, являются неустойчивыми)

void setup() {
Serial.begin(9600); // устанавливает скорость передачи данных
pinMode(encoderPinCCW, INPUT_PULLUP); //устанавливает режим вывода CCW
pinMode(encoderPinCW, INPUT_PULLUP); // устанавливает режим вывода CW
pinMode (resPin, OUTPUT); //устанавливает вывод для режима разрешения
 if(highResOn) angleChange = 0.25; //проверяет включение режима высокого разрешения (угол=0,25 градуса)
 else angleChange = 1; //устанавливает нормальное угловое разрешение 1 градус
 digitalWrite(resPin,highResOn); //инициализирует режим разрешения
 digitalWrite(encoderPinCCW, LOW); //инициализирует состояние вывода CCW
 digitalWrite(encoderPinCW, HIGH); // инициализирует состояние вывода CW
 attachInterrupt(digitalPinToInterrupt(encoderPinCCW), doEncoderCCW, RISING);
 // запускает, когда вывод переходит из состояния LOW в HIGH
 attachInterrupt(digitalPinToInterrupt(encoderPinCW), doEncoderCW, FALLING);
 //запускает, когда вывод переходит из состояния HIGH в LOW
 
for (int i=0; i < size1; i++) 
  {
  Serial.print(encoderPos*angleChange); // угол в градусах
  Serial.print("\t"); 
  float light = Vernier.readSensor();
  Serial.println(light); // регистрация освещённости
  delay(500); // ожидание 0,5 секунды
  }
 }



void doEncoderCCW() {//создаёт функцию для измерения углового положения при вращении против часовой стрелки
  encoderPos++; //подсчитывает показания в сторону нарастания
}
void doEncoderCW() { // создаёт функцию для измерения углового положения при вращении по часовой стрелке
  encoderPos--; //подсчитывает показания в сторону убывания
}

void loop() {
}
