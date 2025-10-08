#include <iostream>  // Для ввода/вывода через консоль (cin, cout)
#include <fstream>   // Для работы с файлами (ifstream, ofstream)
#include <cstring>   // Для работы со строками (char[])
#include <iomanip>   // Для красивого форматирования вывода (setw, left)
#include <string>


using namespace std; // Чтобы не писать std:: перед каждым cout, cin и т.д.
// использование стандартного пространства имен,избегание конфликта имен
const int MAX_BOOKS = 1000; // Максимальное количество книг, которые можем сохранить

// Структура для одной книги
struct Book
//struct (структура) — это составной тип данных в C++,
// который позволяет объединять несколько переменных разных типов под одним именем.
{
    char title[101];    // Строка для названия книги (до 100 символов)
    char author[51];    // Строка для автора (до 50 символов)
    int year;           // Год прочтения
    float rating;       // Оценка по 10-балльной шкале
};

// Глобальный массив для хранения всех книг
Book books[MAX_BOOKS];
int bookCount = 0; // Текущее количество записей книг

// --- Функция для загрузки книг из файла ---
void loadBooks(const char *filename)
{
    ifstream fin(filename); // Открываем файл на чтение
    //ifstream - класс для чтения из файлов,fin - имя объекта (можно любое),filename - путь к файлу с данными книг
    if (!fin)
        return; // Если файл не найден — выходим из функции

    // Чтение данных построчно, пока есть что читать
    while (fin >> books[bookCount].title >> books[bookCount].author >> books[bookCount].year >> books[bookCount].rating)
    //цикл выполняется, пока оператор >> успешно читает все 4 поля
    //books[0] → {title, author, year, rating}
    {
        bookCount++; // Увеличиваем счётчик после успешного чтения
    }

    fin.close(); // Закрываем файл
}

// --- Функция для сохранения одной книги в файл ---
void saveBookToFile(const char *filename, Book b)
//void - функция не возвращает значение
{
    ofstream fout(filename, ios::app); // Открываем файл в режиме добавления (append)
    //ofstream - класс для записи в файлы,ios::app - режим добавления в конец файла (не перезаписывает существующие данные)
    if (!fout)
    {
        cout << "Ошибка при сохранении файла!" << endl;
        //<<-----Направляет" данные в поток вывода
        //cout---вывод в консоль, объект вывода
        //Добавляет символ новой строки \n
        return;
    }

    // Записываем название, автора, год и оценку в файл через пробел
    fout << b.title << " " << b.author << " " << b.year << " " << b.rating << endl;
    //<< добавляет очередной фрагмент данных в файл
    //
    fout.close(); // Закрываем файл
}

// --- Функция для добавления новой книги ---
void addBook()
{
    // Проверяем, не превышен ли лимит
    if (bookCount >= MAX_BOOKS)
    {
        cout << "Превышен лимит книг!" << endl;// cout-стандартный вывод
        return;
    }

    Book b; // Создаём новую переменную для книги

    // Считываем данные от пользователя
    cout << "Введите название книги: ";
    cin.ignore(); // Очищаем буфер перед чтением строки(в буфере ввода остается символ переноса строки \n)
    cin.getline(b.title, 100);
    //Читает всю строку,100 - максимальное количество символов (включая нулевой символ \0)
    cout << "Введите автора: ";
    cin.getline(b.author, 50);

    cout << "Год прочтения: ";
    cin >> b.year;

    cout << "Ваша оценка (0-10): ";
    cin >> b.rating;

    // Проверяем корректность оценки
    if (b.rating < 0 || b.rating > 10)//||-или
    {
        cout << "Оценка должна быть в диапазоне от 0 до 10!" << endl;
        return;
    }

    // Добавляем в массив и сохраняем в файл
    books[bookCount++] = b;
    //обращаемся к ячейке bookCount, записываем b, обновляем счетчик
    saveBookToFile("books.txt", b);

    cout << "Книга добавлена!\n";
}
// --- Функция для отображения всех книг ---
void showAllBooks()
{
    if (bookCount == 0)
    {
        cout << "Нет данных о книгах.\n";
        return;
    }

    // Заголовок таблицы
    cout << "\n--- Все книги ---\n";
    string header = "Название               Автор             Год       Оценка";
    cout << header << "\n";
    cout << "----------------------------------------------------------\n";

    // Находим позиции первых букв каждого столбца в заголовке
    int titlePos = 0; // 'Н' названия
    int authorPos = header.find("Автор"); // 'А' автора
    int yearPos = header.find("Год"); // 'Г' года  
    int ratingPos = header.find("Оценка"); // 'О' оценки

    // Выводим каждую запись
    for (int i = 0; i < bookCount; i++)
    {
        // Название - выводим с начала строки
        cout << books[i].title;
        // Добавляем пробелы до позиции автора
        int currentPos = strlen(books[i].title);
        for (int j = currentPos; j < authorPos-1; j++) cout << " ";
        
        // Автор
        cout << books[i].author;
        // Добавляем пробелы до позиции года
        currentPos = authorPos + strlen(books[i].author);
        for (int j = currentPos; j < yearPos; j++) cout << " ";
        
        // Год
        cout << books[i].year;
        // Добавляем пробелы до позиции оценки
        currentPos = yearPos + to_string(books[i].year).length();
        for (int j = currentPos; j < ratingPos-1; j++) cout << " ";
        
        // Оценка
        cout << books[i].rating << "/10\n";
    }
}
//--- Функция для вывода статистики ---
void showStats()
{
    if (bookCount == 0)
    {
        cout << "Нет данных для анализа.\n";
        return;
    }

    float totalRating = 0;           // Общая сумма оценок
    float maxRating = books[0].rating; // Самая высокая оценка (начинаем с первой)
    int bestBookIndex = 0;           // Индекс книги с самой высокой оценкой

    // Считаем сумму оценок и находим максимальную оценку
    for (int i = 0; i < bookCount; i++)
    {
        totalRating += books[i].rating;

        if (books[i].rating > maxRating)
        {
            maxRating = books[i].rating;
            bestBookIndex = i;
        }
    }

    float averageRating = totalRating / bookCount; // Средняя оценка

    // Выводим статистику
    cout << "\n--- Статистика ---\n";
    cout << "Количество прочитанных книг: " << bookCount << "\n";
    cout << "Средняя оценка: " << fixed << setprecision(1) << averageRating << "/10\n";
    //fixed - фиксация формата вывода,фиксирует точку
    //setprecision(1)-1 - количество цифр после десятичной точки
    cout << "Самая высоко оценённая книга: \"" << books[bestBookIndex].title 
         << "\" (" << books[bestBookIndex].author << ") - " 
         << books[bestBookIndex].rating << "/10\n";
}

// --- Функция для отображения меню пользователя ---
void showMenu()
{
    cout << "\n=== Трекер книг ===\n";
    cout << "1. Добавить книгу\n";
    cout << "2. Показать все книги\n";
    cout << "3. Показать статистику\n";
    cout << "4. Выход\n";
    cout << "Выберите пункт: ";
}

// --- Главная функция программы ---
int main()
{
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif

    loadBooks("books.txt"); // Загружаем данные из файла (если он есть)

    int choice; // Переменная для хранения выбора пользователя

    // Основной цикл меню
    do
    {
        showMenu();    // Показываем меню
        cin >> choice; // Считываем выбор

        // Выполняем действия по выбору
        switch (choice)
        //switch - это оператор множественного выбора
        {
        case 1:
            addBook(); // Добавить книгу
            break;
        case 2:
            showAllBooks(); // Показать все книги
            break;
        case 3:
            showStats(); // Показать статистику
            break;
        case 4:
            cout << "Выход из программы.\n"; // Завершение
            break;
        default:
            cout << "Неверный выбор.\n"; // Ошибка выбора
        }

    } while (choice != 4); // Пока пользователь не выбрал "Выход"

    return 0; // Возвращаем 0 — признак успешного завершения
}