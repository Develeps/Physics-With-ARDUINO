/* FreeFall
В этом скетче отсчёты расстояния до объекта сначала
регистрируются в массиве, а затем выводятся на Монитор порта
вместе с отсчётами текущего времени. Период регистрации
отсчётов определяется с помощью фиксации начального и
конечного времени в микросекундах и деления полученного
интервала на количество отсчётов.
*/
#include "VernierLib.h"
VernierLib Vernier;
const int size1=100;// число регистрируемых отсчётов
float distance[size1];// массив значений расстояния
int tau=4; // дополнительная задержка интервала регистрации в мс
float T;

void setup()
{
 Serial.begin(250000);
 Vernier.autoID(); // включение функции идентификации используемого датчика
  long startTime=micros();// регистрация текущего времени в микросекундах
   for (int i = 0; i < size1; i ++)
    {
     distance[i]= Vernier.readMotionDetector();// регистрация текущего
     // расстояния в миллиметрах
     delay(tau); // задержка, определяющая интервал регистрации отсчётов
    }
    long dT=(micros()-startTime)/size1; // период регистрации, мс
   for (int i = 0; i < size1; i ++) //вывод показаний на Последовательный монитор
    {
     T=i*dT/1000000.0; // расчёт текущего времени в секундах
     Serial.print(T, 3); // вывод текущего времени с точность до миллисекунд
     Serial.print("\t");
     Serial.println(distance[i]/1000.0,3); // вывод значений расстояния, м 
    }
}
void loop() { // пустой цикл
}
