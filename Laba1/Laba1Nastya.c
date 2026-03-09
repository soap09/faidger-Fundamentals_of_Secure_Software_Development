#include <stdio.h>
// для выравнивания, считает цифры числа в выбранной СС
int digitsCount(int n, int base) {
    if (n == 0) return 1;
    int count = 0;
    while (n > 0) {
        n /= base;
        count++;
    }
    return count;
}

// вывод числа n в системе счисления base
void numeralSystems(int n, int base) {
    if (n >= base) {
        numeralSystems(n / base, base); 
    }
    int digit = n % base;
    if (digit < 10) {
        printf("%d", digit);
    } else {
        printf("%c", 'A' + (digit - 10));
    }
}

int main() {
    int base = 0;
    while (base < 2 || base > 16) {
        printf("========================================================\n");
        printf("Введите систему счисления (2 - 16): ");
        if (scanf("%d", &base) != 1) {
            printf("Ошибка ввода: пожалуйста, введите число.\n");
            while(getchar() != '\n'); 
            continue;
        }
        if (base < 2 || base > 16) {
            printf("Ошибка ввода: система должна быть в диапазоне от 2 до 16.\n");
        }
    }       
    printf("========================================================");

    printf("\n\n\nТАБЛИЦА СЛОЖЕНИЯ В %d-ИЧНОЙ СИСТЕМЕ\n", base);
    printf("========================================================\n");
    printf("  +   ║");
    for (int x = 0; x < base; x++) printf(" %2X ", x);
    printf("\n======║=================================================\n");

    for (int x = 0; x < base; x++) {
        printf(" %2X   ║", x);
        for (int y = 0; y < base; y++) {
            int result = x + y;
            // если число однозначное - печатаем доп. пробел для выравнивания
            if (result < base) printf("  "); 
            else printf(" "); 
            
            numeralSystems(result, base);
            printf(" ");
        }
        printf("\n");
    }
    printf("========================================================");

    printf("\n\n\nТАБЛИЦА УМНОЖЕНИЯ В %d-ИЧНОЙ СИСТЕМЕ\n", base);
    printf("========================================================\n");
    printf("  x   ║");
    for (int x = 0; x < base; x++) printf(" %2X ", x);
    printf("\n======║=================================================\n");

    for (int x = 0; x < base; x++) {
        printf(" %2X   ║", x);
        for (int y = 0; y < base; y++) {
            int result = x * y;

            // может получиться трехзначное число (F*F = E1 в 16-ричной)
            if (result < base) printf("  "); // 1 цифра
            else if (result < base * base) printf(" "); // 2 цифры
            // иначе 3 цифры = пробелы не нужны
            
            numeralSystems(result, base);
            printf(" ");
        }
        printf("\n");
    }
    printf("========================================================");

    // демо умножения
    char choice;
    do {
        printf("\nПосмотреть демонстрацию умножения? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            int a, b;
            printf("Введите 1-й множитель (в десятичной): ");
            if (scanf("%d", &a) != 1) { while(getchar() != '\n'); continue; }
            printf("Введите 2-й множитель (в десятичной): ");
            if (scanf("%d", &b) != 1) { while(getchar() != '\n'); continue; }

            printf("\nУМНОЖЕНИЕ СТОЛБИКОМ В %d-ИЧНОЙ СИСТЕМЕ\n\n", base);

            int padding = 15; // отступ для выравнивания вывода

            // первый множитель
            int lenA = digitsCount(a, base);
            for(int i = 0; i < (padding - lenA); i++) printf(" ");
            numeralSystems(a, base); printf("\n");

            // второй множитель
            int lenB = digitsCount(b, base);
            for(int i = 0; i < (padding - lenB - 2); i++) printf(" ");
            printf("x "); 
            numeralSystems(b, base); printf("\n");

            for(int i = 0; i < (padding - 10); i++) printf(" ");
            printf("----------\n");

            int tempB = b;
            int shift = 0; 

            // промежуточные слагаемые
            while (tempB > 0) {
                int digit = tempB % base;
                if (digit > 0) {
                    int part = a * digit;
                    int lenPart = digitsCount(part, base);
                    
                    // чем больше shift, тем меньше отступ для сдвига
                    // вычитаем длину самого числа lenPart для выравнивания
                    for (int i = 0; i < (padding - lenPart - shift); i++) {
                        printf(" ");
                    }

                    numeralSystems(part, base);
                    
                    // нолики для наглядности
                    for(int s = 0; s < shift; s++) printf("0"); 
                    printf("\n");
                }
                tempB /= base;
                shift++;
            }

            for(int i = 0; i < (padding - 10); i++) printf(" ");
            printf("----------\n");

            // результат
            int finalRes = a * b;
            int lenRes = digitsCount(finalRes, base);
            for(int i = 0; i < (padding - lenRes); i++) printf(" ");
            numeralSystems(finalRes, base);
            printf("\n");
        }
    } while (choice == 'y' || choice == 'Y');

    printf("\nПрограмма завершена.\n");
    return 0;
}
