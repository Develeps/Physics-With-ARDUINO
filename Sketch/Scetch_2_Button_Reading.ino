#include "VernierLib.h"
VernierLib Vernier;
int buttonState1=0;// переменная для считывания состояния кнопки
int reading1;         // текущее состояние выходного пина
int lastButtonState = 0;   // предыдущее считывание состояния кнопки
unsigned long lastDebounceTime = 0;  // время последнего переключения выходного пина
unsigned long debounceDelay = 50; // время задержки антидребезга, мс
const int size1  = 10; // число регистрируемых отсчётов
float distance[size1]; // массив значений расстояния
float force[size1]; // массив значений силы
float slope=-4.9, intercept=12.25; // диапазон 10 Н 
//float slope=-24.5, intercept=61.25; // диапазон 50 Н 
int i=0; // обнуление номера измерения

void setup()
{
 Serial.begin(250000);
 Vernier.autoID(); // включение функции идентификации используемого датчика
 pinMode(12, INPUT_PULLUP);// установка режима ввода для пина 12 (кнопка)
 pinMode(13, OUTPUT);// установка режима вывода для пина 13 (светодиод)
 digitalWrite(13, 0); // выключение светодиода:   
}

void loop() 
{ 
 reading1 = digitalRead(12); // считывание состояния кнопки 
 if (reading1 != lastButtonState) // проверка изменения состояния кнопки 
  {
    lastDebounceTime = millis();// сброс таймера антидребезга
  }
 if ((millis() - lastDebounceTime) > debounceDelay) 
   {
    // проверка превышения текущего времени заданного интервала антидребезга
    if (reading1 != buttonState1) // если состояние кнопки изменилось
    {    
      buttonState1 = reading1; // запоминает изменившееся состояние      
      if (buttonState1 == 0) 
      {
      digitalWrite(13,1);
      distance[i]= Vernier.readMotionDetector()/10.0; // текущее расстояние, см
      force[i] = analogRead(A0)*5.0/1024.0*slope + intercept;// текущая сила, Н
      Serial.print(i);
      Serial.print("\t");
      Serial.println(distance[i],1); 
      Serial.print("\t");  
      Serial.println(force[i],2); 
      i++;
      digitalWrite(13,0);
      }
    }
   }
  lastButtonState = reading1;
}
