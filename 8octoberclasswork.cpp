#include <stdio.h>
#include <iostream>  // Для ввода/вывода через консоль (cin, cout)
#include <fstream>   // Для работы с файлами (ifstream, ofstream)
#include <cstring>   // Для работы со строками (char[])
#include <iomanip>   // Для красивого форматирования вывода (setw, left)
#include <string>
void hanoi(int n, int from, int to, int temp) {
    if (n == 1) {
        printf("%d>>%d\n", from, to);
        return;
    }
    
    hanoi(n - 1, from, temp, to);
    printf("%d>>%d\n", from, to);
    hanoi(n - 1, temp, to, from);
}

int main() {

    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    int n;
    
    printf("Введите количество колец: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Количество колец должно быть положительным числом\n");
        return 1;
    }
    
    printf("Перемещения для %d колец:\n", n);
    hanoi(n, 1, 3, 2);
    
    return 0;
}