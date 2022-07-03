/* RLC_Contur
Этот скетч регистрирует временную зависимость напряжения на
колебательном контуре с помощью датчика напряжения
дифференциального типа, который может подключаться к портам
Analog 1 или Analog 2, поскольку с него считывается исходное
значение АЦП. Во время записи сигнала загорается светодиод
D13 на шилде Vernier Arduino. Для экономии памяти производится
перевод значения АЦП в байтовый формат.
*/
#include "VernierLib.h"
VernierLib Vernier;
int const size1=950; // размер массива
int tau1=600; // задержка цикла регистрации, мкс
int dtau=110; // время ввода отсчёта аналогового сигнала, мкс
byte array1[size1]; // массив для записи сигнала

void setup() {
Serial.begin(250000);
pinMode(13, OUTPUT);// установка режима вывода для пина 13
digitalWrite(13, HIGH); // включение светодиода на шилде
// на время регистрации
for (int i=0; i<size1; i++)
 {
  array1[i]= analogRead(A0)>>2;
  delayMicroseconds(tau1);
 }
digitalWrite(13, LOW);
for (int i=0; i<size1; i++)
 {
  float T=i/1000.0*(tau1+dtau);
  Serial.print(T, 1); // вывод текущего времени, мс
  Serial.print("\t");
  Serial.println(array1[i]);
 }
}

void loop() {
}
