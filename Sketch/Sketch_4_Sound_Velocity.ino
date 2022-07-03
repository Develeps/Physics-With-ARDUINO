/* Sound_Velocity
 * Этот скетч регистрирует начало звукового сигнала по
 * уровню среднеквадратичного значения. 
 */

 /*hello word*/
#include "VernierLib.h"
VernierLib Vernier;
const byte PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
const byte PS_16 = (1 << ADPS2);
const int im=450; // число отсчётов 
byte sound1[im], sound2[im];
int i, j=0;
int threshold=10; // пороговый уровень 
float sum1, mean1, sd1, T, dt;

void setup() 
 {
  ADCSRA &= ~PS_128;  // сбросить масштаб 128
  ADCSRA |= PS_16;    // добавить масштаб 16 (1 МГц)
  Serial.begin(250000); // устанавливает скорость передачи данных
  Vernier.autoID(); // идентифицирует используемый датчик
  Serial.println(PS_128, 2);
  Serial.println(PS_16, 2);
  pinMode(13, OUTPUT);// установка режима вывода для пина 13
  digitalWrite(13, LOW); // выключение светодиода на шилде
 }

void loop() 
 {
  sum1=0;
   long startTime=micros();
    for (i = 0; i <im; i++)
     {
      sound1[i]=analogRead(A0)>>2;
      sound2[i]=analogRead(A2)>>2;
     }
    dt=(micros()-startTime)/im;
    for (i = 0; i <im; i++)
     {
      sum1+= sound1[i]; // накопление суммы 
      //показаний датчика
     }    
    mean1 = sum1/im; // расчёт среднего 
    sd1=0;
    for (i = 0; i <im; i++)
    {
     sd1+= (sound1[i]-mean1)*(sound1[i]-mean1); // сумма 
     //квадратов
    }
    sd1 = sqrt(sd1/(im-1));
    if (sd1>threshold and j==0)
    {
    digitalWrite(13, HIGH);  
    for (i = 0; i <im; i++)
     {
      T=i*dt/1000;
      Serial.print(T,3); 
      Serial.print("\t");
      Serial.print(sound1[i]);
      Serial.print("\t");
      Serial.println(sound2[i]);
     }
     j++; 
    }
   }
