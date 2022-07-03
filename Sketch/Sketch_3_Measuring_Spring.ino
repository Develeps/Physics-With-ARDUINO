#include "VernierLib.h"
VernierLib Vernier;
const int size1=300; // число регистрируемых отсчётов
float distance, force, time1; // переменные расстояния, силы и времени
int dt=25; // дополнительная задержка регистрации в мс
float T;

void setup()
{
 Serial.begin(250000);
 Vernier.autoID(); // включение функции идентификации используемого датчика
 long startTime=micros();
   for (int i = 0; i < size1; i ++)
   {
    distance= Vernier.readMotionDetector()/10.0;// текущее расстояние, см
    force = Vernier.readSensor(); // текущее значение силы
    time1=(micros()-startTime)/1000.0; // время с начала регистрации, мс
    delay(dt); // введение задержки
    Serial.print(time1,0); // вывод времени с начала регистрации
    Serial.print("\t");
    Serial.print(distance,1);
    Serial.print("\t");
    Serial.println(force,1);    
   }
}
void loop() { // пустой цикл
}
