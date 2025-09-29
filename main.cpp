#include <iostream> // Для ввода/вывода через консоль (cin, cout)
#include <fstream>  // Для работы с файлами (ifstream, ofstream)
#include <cstring>  // Для работы со строками (char[])
#include <iomanip>  // Для красивого форматирования вывода (setw, left)

using namespace std; // Чтобы не писать std:: перед каждым cout, cin и т.д.

const int MAX_EXPENSES = 1000; // Максимальное количество расходов, которые можем сохранить

// Структура для одного расхода
struct Expense
{
    char date[11];     // Строка для даты (формат: "дд.мм.гггг", например: "24.09.2025")
    char category[30]; // Строка для категории (например: "еда", "транспорт")
    float amount;      // Сумма расхода в рублях
};

// Глобальный массив для хранения всех расходов
Expense expenses[MAX_EXPENSES];
int expenseCount = 0; // Текущее количество записей расходов

// --- Функция для загрузки расходов из файла ---
void loadExpenses(const char *filename)
{
    ifstream fin(filename); // Открываем файл на чтение

    if (!fin)
        return; // Если файл не найден — выходим из функции

    // Чтение данных построчно, пока есть что читать
    while (fin >> expenses[expenseCount].date >> expenses[expenseCount].category >> expenses[expenseCount].amount)
    {
        expenseCount++; // Увеличиваем счётчик после успешного чтения
    }

    fin.close(); // Закрываем файл
}

// --- Функция для сохранения одного расхода в файл ---
void saveExpenseToFile(const char *filename, Expense e)
{
    ofstream fout(filename, ios::app); // Открываем файл в режиме добавления (append)

    if (!fout)
    {
        cout << "Ошибка при сохранении файла!" << endl;
        return;
    }

    // Записываем дату, категорию и сумму в файл через пробел
    fout << e.date << " " << e.category << " " << e.amount << endl;

    fout.close(); // Закрываем файл
}

// --- Функция для добавления нового расхода ---
void addExpense()
{
    // Проверяем, не превышен ли лимит
    if (expenseCount >= MAX_EXPENSES)
    {
        cout << "Превышен лимит расходов!" << endl;
        return;
    }

    Expense e; // Создаём новую переменную для расхода

    // Считываем данные от пользователя
    cout << "Введите дату (дд.мм.гггг): ";
    cin >> e.date;

    cout << "Введите категорию: ";
    cin >> e.category;

    cout << "Введите сумму: ";
    cin >> e.amount;

    // Добавляем в массив и сохраняем в файл
    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    cout << "Расход добавлен!\n";
}

// --- Функция для отображения всех расходов ---
void showAllExpenses()
{
    if (expenseCount == 0)
    {
        cout << "Нет данных о расходах.\n";
        return;
    }

    // Заголовок таблицы
    cout << "\n--- Все расходы ---\n";
    cout << left << setw(12) << "Дата"
         << setw(15) << "Категория"
         << "Сумма\n";
    cout << "------------------------------\n";

    // Выводим каждую запись
    for (int i = 0; i < expenseCount; i++)
    {
        cout << left << setw(12) << expenses[i].date
             << setw(15) << expenses[i].category
             << expenses[i].amount << " руб.\n";
    }
}

// --- Функция для вывода статистики ---
void showStats()
{
    if (expenseCount == 0)
    {
        cout << "Нет данных для анализа.\n";
        return;
    }

    float total = 0;                // Общая сумма
    float max = expenses[0].amount; // Самая большая трата (начинаем с первой)

    // Считаем сумму и находим максимум
    for (int i = 0; i < expenseCount; i++)
    {
        total += expenses[i].amount;

        if (expenses[i].amount > max)
        {
            max = expenses[i].amount;
        }
    }

    float average = total / expenseCount; // Среднее значение

    // Выводим статистику
    cout << "\n--- Статистика ---\n";
    cout << "Всего потрачено: " << total << " руб.\n";
    cout << "Средняя трата: " << average << " руб.\n";
    cout << "Максимальная трата: " << max << " руб.\n";
}

// --- Функция для отображения меню пользователя ---
void showMenu()
{
    cout << "\n=== Трекер расходов ===\n";
    cout << "1. Добавить расход\n";
    cout << "2. Показать все расходы\n";
    cout << "3. Показать статистику\n";
    cout << "4. Выход\n";
    cout << "Выберите пункт: ";
}

// --- Главная функция программы ---
int main()
{
    loadExpenses("expenses.txt"); // Загружаем данные из файла (если он есть)

    int choice; // Переменная для хранения выбора пользователя

    // Основной цикл меню
    do
    {
        showMenu();    // Показываем меню
        cin >> choice; // Считываем выбор

        // Выполняем действия по выбору
        switch (choice)
        {
        case 1:
            addExpense(); // Добавить расход
            break;
        case 2:
            showAllExpenses(); // Показать все расходы
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
