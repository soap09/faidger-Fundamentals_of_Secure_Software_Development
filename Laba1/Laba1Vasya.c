#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 
// Возвращает числовое значение римской цифры
int romanValue(char c) {
   switch (c) {
       case 'I': return 1;
       case 'V': return 5;
       case 'X': return 10;
       case 'L': return 50;
       case 'C': return 100;
       case 'D': return 500;
       case 'M': return 1000;
       default: return 0;  // недопустимый символ
   }
}
 
// Проверяет, допустимо ли вычитание (например, IV, IX — да; IL, IC — нет)
bool validSubtraction(char a, char b) {
   if (a == 'I' && (b == 'V' || b == 'X')) return true;
   if (a == 'X' && (b == 'L' || b == 'C')) return true;
   if (a == 'C' && (b == 'D' || b == 'M')) return true;
   return false;
}
 
// Основная функция преобразования
int romanToArabic(const char* s) {
   int len = strlen(s);
   if (len == 0) {
       printf("Ошибка: пустая строка\n");
       return -1;
   }
 
   int total = 0;
   int i = 0;
 
   while (i < len) {
       char current = s[i];
       int val = romanValue(current);
       if (val == 0) {
           printf("Ошибка: недопустимый символ '%c'\n", current);
           return -1;
       }
 
       // Подсчёт повторов текущего символа
       int repeat = 1;
       while (i + repeat < len && s[i + repeat] == current) {
           repeat++;
       }
 
       // V, L, D не могут повторяться
       if ((current == 'V' || current == 'L' || current == 'D') && repeat > 1) {
           printf("Ошибка: символ '%c' не может повторяться\n", current);
           return -1;
       }
 
       // I, X, C, M не могут повторяться более 3 раз
       if (repeat > 3) {
           printf("Ошибка: слишком много повторов символа '%c'\n", current);
           return -1;
       }
 
       // Проверка на вычитание (например, IV = 4)
       if (i + 1 < len) {
           char next = s[i + 1];
           int nextVal = romanValue(next);
           if (nextVal == 0) {
               printf("Ошибка: недопустимый символ '%c'\n", next);
               return -1;
           }
 
           if (val < nextVal) {
               if (!validSubtraction(current, next)) {
                   printf("Ошибка: недопустимое вычитание '%c%c'\n", current, next);
                   return -1;
               }
               total += (nextVal - val);
               i += 2;  // пропускаем оба символа
               continue;
           }
       }
 
       // Обычное сложение (без вычитания)
       for (int j = 0; j < repeat; j++) {
           total += val;
       }
       i += repeat;
   }
 
   // Проверка диапазона: только 1–3999
   if (total < 1 || total > 3999) {
       printf("Ошибка: число должно быть от 1 до 3999\n");
       return -1;
   }
 
   return total;
}
 
// Главная функция
int main() {
   char roman[50];
   printf("Введите римское число (от I до MMMCMXCIX): ");
   scanf("%49s", roman);  // Защита от переполнения буфера
 
   int result = romanToArabic(roman);
   if (result != -1) {
       printf("Арабское число: %d\n", result);
   }
 
   return 0;
}
