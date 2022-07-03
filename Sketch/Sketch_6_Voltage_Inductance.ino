/* Voltage_Inductance
Этот скетч регистрирует временные зависимости напряжения,
индукции и веса трубы при опускании в неё постоянного
неодимового магнита. Датчики магнитной индукции и силы
подключаются к порту Analog 1 и являются автоматически
определяемыми, а датчик напряжения дифференциального типа
подключается к порту Analog 2 и требует пересчёта показаний
с помощью калибровочных коэффициентов.
*/
#include "VernierLib.h"
VernierLib Vernier;
const int size1=100; // число регистрируемых отсчётов
float data1[size1], data2[size1]; // массивы значений величин
float slope=-2.5, intercept=6.25; // коэффициенты датчика напряжения
int tau=15; // значение задержки, мс
void setup()
{
Serial.begin(250000);
Vernier.autoID(); // функция автоматической идентификации
long startTime=micros();
for (int i = 0; i < size1; i ++)
 {
  data1[i]= Vernier.readSensor(); // показания датчика с порта Analog 1
  data2[i]= analogRead(A2)*5.0/1024.0*slope+intercept; // показания датчика с порта Analog 2
  delay(tau); // задержка, определяющая интервал регистрации отсчётов
 }
float dt=(micros()-startTime)/1000.0/size1;
Serial.println(dt);
for (int i = 0; i < size1; i ++) //вывод показаний на Монитор порта
 {
  int T=i*dt; // расчёт текущего времени в миллисекундах
  Serial.print(T); // вывод времени регистрации, мс
  Serial.print("\t");
  Serial.print(data1[i]); // вывод значений первой величины
  Serial.print("\t");
  Serial.println(data2[i]); // вывод значений второй величины
}
}
void loop() { // пустой цикл
}
