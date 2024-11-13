#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

// Перелік спеціальностей
enum Specialnist { KN, INF, ME, FI, TN };
string specialnistStr[] = { "Комп'ютерні науки", "Інформатика", "Економіка", "Фізика та інформатика", "Трудове навчання" };

// Структура для зберігання інформації про студента
struct Student {
    string prizv;
    int kurs;
    Specialnist specialnist;
    int ocinka_fizyka;
    int ocinka_matematyka;
    union {
        int ocinka_programuvannia;
        int ocinka_chyselni_metody;
        int ocinka_pedahohika;
    };
};

// Функція для створення масиву студентів
void CreateStudents(Student* students, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cout << " Прізвище: ";
        cin >> students[i].prizv;
        cout << " Курс: ";
        cin >> students[i].kurs;

        int specialnist;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> specialnist;
        students[i].specialnist = (Specialnist)specialnist;

        // Введення оцінок з фізики та математики
        cout << " Оцінка з фізики: ";
        cin >> students[i].ocinka_fizyka;
        cout << " Оцінка з математики: ";
        cin >> students[i].ocinka_matematyka;

        // Введення третьої оцінки залежно від спеціальності
        if (students[i].specialnist == KN) {
            cout << " Оцінка з програмування: ";
            cin >> students[i].ocinka_programuvannia;
        }
        else if (students[i].specialnist == INF) {
            cout << " Оцінка з чисельних методів: ";
            cin >> students[i].ocinka_chyselni_metody;
        }
        else {
            cout << " Оцінка з педагогіки: ";
            cin >> students[i].ocinka_pedahohika;
        }
        cout << endl;
    }
}

// Функція для виведення студентів на екран
void PrintStudents(const Student* students, const int N) {
    cout << "===============================================================================================================================" << endl;
    cout << "| № | Прізвище         | Курс | Спеціальність          | Фізика | Математика | Програмування | Чисельні методи  | Педагогіка  |" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1
            << "| " << setw(16) << left << students[i].prizv
            << " | " << setw(4) << right << students[i].kurs
            << " | " << setw(22) << left << specialnistStr[students[i].specialnist]
            << " | " << setw(6) << right << students[i].ocinka_fizyka
            << " | " << setw(10) << right << students[i].ocinka_matematyka;

        // Виведення третьої оцінки залежно від спеціальності
        if (students[i].specialnist == KN) {
            cout << " | " << setw(13) << right << students[i].ocinka_programuvannia
                << " | " << setw(16) << "-"
                << " | " << setw(11) << "-";
        }
        else if (students[i].specialnist == INF) {
            cout << " | " << setw(13) << "-"
                << " | " << setw(16) << students[i].ocinka_chyselni_metody
                << " | " << setw(11) << "-";
        }
        else {
            cout << " | " << setw(13) << "-"
                << " | " << setw(16) << "-"
                << " | " << setw(11) << students[i].ocinka_pedahohika;
        }
        cout << " |" << endl;
    }
    cout << "==============================================================================================================================" << endl;
}

// Функція для виведення прізвищ відмінників
void PrintExcellentStudents(const Student* students, const int N) {
    cout << "Студенти, які вчаться на відмінно:" << endl;
    for (int i = 0; i < N; i++) {
        double average;
        if (students[i].specialnist == KN) {
            average = (students[i].ocinka_fizyka + students[i].ocinka_matematyka + students[i].ocinka_programuvannia) / 3.0;
        }
        else if (students[i].specialnist == INF) {
            average = (students[i].ocinka_fizyka + students[i].ocinka_matematyka + students[i].ocinka_chyselni_metody) / 3.0;
        }
        else {
            average = (students[i].ocinka_fizyka + students[i].ocinka_matematyka + students[i].ocinka_pedahohika) / 3.0;
        }

        if (average >= 4.5) {
            cout << " - " << students[i].prizv << endl;
        }
    }
}

// Функція для обчислення відсотка студентів з середнім балом > 4.5
double CalculateHighAveragePercentage(const Student* students, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        double average;
        if (students[i].specialnist == KN) {
            average = (students[i].ocinka_fizyka + students[i].ocinka_matematyka + students[i].ocinka_programuvannia) / 3.0;
        }
        else if (students[i].specialnist == INF) {
            average = (students[i].ocinka_fizyka + students[i].ocinka_matematyka + students[i].ocinka_chyselni_metody) / 3.0;
        }
        else {
            average = (students[i].ocinka_fizyka + students[i].ocinka_matematyka + students[i].ocinka_pedahohika) / 3.0;
        }

        if (average > 4.5) {
            count++;
        }
    }
    return (count / (double)N) * 100;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N];

    CreateStudents(students, N);
    PrintStudents(students, N);
    PrintExcellentStudents(students, N);

    double highAvgPercentage = CalculateHighAveragePercentage(students, N);
    cout << "Процент студентів із середнім балом більше 4.5: " << highAvgPercentage << "%" << endl;

    delete[] students;
    return 0;
}
