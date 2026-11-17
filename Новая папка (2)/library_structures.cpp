#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

// Об'єднання (union) для зберігання ваги фізичної книги або розміру файлу електронної
union BookFormatDetails {
    int weightGrams;      // Вага у грамах (для фізичних книг)
    double fileSizeMB;    // Розмір файлу в МБ (для електронних книг)
};

// Структура "Книга"
struct Book {
    string title;                  // Назва книги
    string author;                 // Автор
    string publisher;              // Видавництво
    string genre;                  // Жанр
    int year;                      // Рік видання
    unsigned int pages : 15;       // Бітове поле: кількість сторінок (до 32767)
    bool isElectronic;             // Ознака формату: true - електронна, false - фізична
    BookFormatDetails details;     // Об'єднання з вагою або розміром файлу
};

// Функція виведення інформації про одну книгу
void printBook(const Book& b, int index) {
    cout << "--------------------------------------------------\n";
    cout << "Книга #" << index + 1 << ": «" << b.title << "»\n";
    cout << "  Автор:        " << b.author << '\n';
    cout << "  Видавництво:  " << b.publisher << " (" << b.year << " р.)\n";
    cout << "  Жанр:         " << b.genre << '\n';
    cout << "  Сторінок:     " << b.pages << '\n';

    if (b.isElectronic) {
        cout << "  Формат:       Електронна книга\n";
        cout << "  Розмір файлу: " << fixed << setprecision(2) << b.details.fileSizeMB << " МБ\n";
    } else {
        cout << "  Формат:       Фізичне видання\n";
        cout << "  Вага:         " << b.details.weightGrams << " г\n";
    }
}

// Функція додавання нової книги з клавіатури
void inputBook(Book& b) {
    cout << "Введіть назву книги: ";
    getline(cin, b.title);

    cout << "Введіть автора: ";
    getline(cin, b.author);

    cout << "Введіть видавництво: ";
    getline(cin, b.publisher);

    cout << "Введіть жанр: ";
    getline(cin, b.genre);

    cout << "Введіть рік видання: ";
    cin >> b.year;

    // Зчитування у тимчасову змінну перед записом у бітове поле
    unsigned int tempPages;
    cout << "Введіть кількість сторінок (1 - 32767): ";
    cin >> tempPages;
    b.pages = tempPages;

    int formatChoice;
    cout << "Оберіть тип книги (0 - фізична, 1 - електронна): ";
    cin >> formatChoice;
    b.isElectronic = (formatChoice == 1);

    if (b.isElectronic) {
        cout << "Введіть розмір файлу (МБ): ";
        cin >> b.details.fileSizeMB;
    } else {
        cout << "Введіть вагу книги (г): ";
        cin >> b.details.weightGrams;
    }
    cin.ignore(); // Очищення буфера після введення чисел
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const int LIBRARY_SIZE = 3;
    Book library[LIBRARY_SIZE];

    // Ініціалізація перших двох книг у бібліотеці для демонстрації
    library[0].title = "Кобзар";
    library[0].author = "Тарас Шевченко";
    library[0].publisher = "А-БА-БА-ГА-ЛА-МА-ГА";
    library[0].genre = "Поезія";
    library[0].year = 2019;
    library[0].pages = 704;
    library[0].isElectronic = false;
    library[0].details.weightGrams = 980;

    library[1].title = "Мова програмування C++";
    library[1].author = "Б'ярн Страуструп";
    library[1].publisher = "Addison-Wesley";
    library[1].genre = "Технічна література";
    library[1].year = 2013;
    library[1].pages = 1376;
    library[1].isElectronic = true;
    library[1].details.fileSizeMB = 18.45;

    // Введення третьої книги користувачем
    cout << "=== Додавання нової книги до бібліотеки ===\n";
    inputBook(library[2]);

    // Виведення всіх книг бібліотеки
    cout << "\n=== Каталог бібліотеки ===\n";
    for (int i = 0; i < LIBRARY_SIZE; i++) {
        printBook(library[i], i);
    }
    cout << "--------------------------------------------------\n";
    cout << "Розмір union BookFormatDetails у пам'яті: " << sizeof(BookFormatDetails) << " байт(ів)\n";

    return 0;
}