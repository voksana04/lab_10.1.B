#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

// ������ ��������������
enum Specialnist { KN, INF, ME, FI, TN };
string specialnistStr[] = { "����'����� �����", "�����������", "��������", "Գ���� �� �����������", "������� ��������" };

// ��������� ��� ��������� ���������� ��� ��������
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

// ������� ��� ��������� ������ ��������
void CreateStudents(Student* students, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cout << " �������: ";
        cin >> students[i].prizv;
        cout << " ����: ";
        cin >> students[i].kurs;

        int specialnist;
        cout << " ������������ (0 - ����'����� �����, 1 - �����������, 2 - ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> specialnist;
        students[i].specialnist = (Specialnist)specialnist;

        // �������� ������ � ������ �� ����������
        cout << " ������ � ������: ";
        cin >> students[i].ocinka_fizyka;
        cout << " ������ � ����������: ";
        cin >> students[i].ocinka_matematyka;

        // �������� ������ ������ ������� �� ������������
        if (students[i].specialnist == KN) {
            cout << " ������ � �������������: ";
            cin >> students[i].ocinka_programuvannia;
        }
        else if (students[i].specialnist == INF) {
            cout << " ������ � ��������� ������: ";
            cin >> students[i].ocinka_chyselni_metody;
        }
        else {
            cout << " ������ � ���������: ";
            cin >> students[i].ocinka_pedahohika;
        }
        cout << endl;
    }
}

// ������� ��� ��������� �������� �� �����
void PrintStudents(const Student* students, const int N) {
    cout << "===============================================================================================================================" << endl;
    cout << "| � | �������         | ���� | ������������          | Գ���� | ���������� | ������������� | ������� ������  | ���������  |" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1
            << "| " << setw(16) << left << students[i].prizv
            << " | " << setw(4) << right << students[i].kurs
            << " | " << setw(22) << left << specialnistStr[students[i].specialnist]
            << " | " << setw(6) << right << students[i].ocinka_fizyka
            << " | " << setw(10) << right << students[i].ocinka_matematyka;

        // ��������� ������ ������ ������� �� ������������
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

// ������� ��� ��������� ������ ��������
void PrintExcellentStudents(const Student* students, const int N) {
    cout << "��������, �� ������� �� ������:" << endl;
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

// ������� ��� ���������� ������� �������� � ������� ����� > 4.5
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
    cout << "������ ������� ��������: ";
    cin >> N;

    Student* students = new Student[N];

    CreateStudents(students, N);
    PrintStudents(students, N);
    PrintExcellentStudents(students, N);

    double highAvgPercentage = CalculateHighAveragePercentage(students, N);
    cout << "������� �������� �� ������� ����� ����� 4.5: " << highAvgPercentage << "%" << endl;

    delete[] students;
    return 0;
}
