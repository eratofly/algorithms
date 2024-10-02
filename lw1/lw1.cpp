#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <windows.h>

/*
    Охотникова Дарья Сергеевна
    ПС-22
    Задание 27
    VS Code 1.15.1
    На вход подаются сведения о сдаче экзаменов учениками 9-х
    классов некоторой средней школы. В первой строке сообщается 
    количество учеников N, которое не меньше 10, но не превосходит
    100, каждая из следующих N строк имеет следующий формат:
    <Фамилия> <Имя> <оценки>, где <Фамилия> – строка, состоящая не 
    более чем из 20 символов, <Имя> – строка, состоящая не более чем
    из 15 символов <оценки> – через пробел три целых числа, 
    соответствующие оценкам по пятибалльной системе. <Фамилия> и 
    <Имя>, а также <Имя> и <оценки> разделены одним пробелом. 
    Пример входной строки: Иванов Петр 4 5 4
    Требуется написать программу, которая будет выводить на экран 
    фамилии и имена трех лучших по среднему баллу учеников. Если 
    среди остальных есть ученики, набравшие тот же средний балл, 
    что и один из трех лучших, то следует вывести и их фамилии и 
    имена. Требуемые имена и фамилии можно выводить в произвольном 
    порядке (8).
*/

using namespace std;

const int minStudents = 10;
const int maxStudents = 100;

string finName;
string foutName;
string strFin;
int n;
set<char> marks{'1', '2', '3', '4', '5'};
bool isSpace;
struct Student
{
    vector<char> lastName;
    vector<char> firstName;
    int maxMark;
};

int countStudents = 0;

main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("chcp 1251");

    cout << "Введите имя входного файла: ";
    cin >> finName;

    ifstream fin;
    fin.open(finName);

    if (!fin.is_open())
    {
        cout << "Файл" << finName << " не удалось открыть!\n";
        return -1;
    }

    cout << "Введите имя выходного файла: ";
    cin >> foutName;

    if (getline(fin, strFin))
    {
        n = stoi(strFin);
    }
    int k = 0;
    if ((n >= minStudents) && (n <= maxStudents))
    {
        Student arrayStudents[n];
        for (int i = 0; i < n; i++)
        {
            arrayStudents[i].maxMark = 0;
        }
        while (getline(fin, strFin))
        {
            arrayStudents[k].maxMark = 0;
            int i = 0;
            isSpace = false;
            for (const char ch : strFin)
            {
                if (ch == ' ')
                {
                    isSpace = true;
                }
                if (marks.count(ch))
                {
                    arrayStudents[k].maxMark += (strFin[i] - '0');
                }
                else if ((ch != ' ') && !isSpace)
                {
                    arrayStudents[k].lastName.push_back(ch);
                }
                else if ((ch != ' ') && isSpace)
                {
                    arrayStudents[k].firstName.push_back(ch);
                }
                i++;
            }
            k++;
        }
        for (int i = 0; i < n; i++)
        {
            bool flag = true;
            for (int j = 0; j < n - (i + 1); j++)
            {
                if (arrayStudents[j].maxMark < arrayStudents[j + 1].maxMark)
                {
                    flag = false;
                    int tempMark = arrayStudents[j].maxMark;
                    arrayStudents[j].maxMark = arrayStudents[j + 1].maxMark;
                    arrayStudents[j + 1].maxMark = tempMark;
                    vector<char> tempLastName = arrayStudents[j].lastName;
                    arrayStudents[j].lastName = arrayStudents[j + 1].lastName;
                    arrayStudents[j + 1].lastName = tempLastName;
                    vector<char> tempFirstName = arrayStudents[j].firstName;
                    arrayStudents[j].firstName = arrayStudents[j + 1].firstName;
                    arrayStudents[j + 1].firstName = tempFirstName;
                }
            }
            if (flag)
            {
                break;
            }
        }
        for (char j : arrayStudents[3].lastName)
        {
            cout << j;
        }
        int deltaMark = 0;
        ofstream fout;
        fout.open(foutName);
        if (!fout.is_open())
        {
            cout << "Файл " << foutName << " не удалось открыть!\n";
            return -1;
        }
        for (int i = 0; i < n; i++)
        {
            if ((arrayStudents[i].maxMark == arrayStudents[i + 1].maxMark) && ((deltaMark <= 2)))
            {
                for (char j : arrayStudents[i].lastName)
                {
                    fout << j;
                }
                fout << ' ';
                for (char j : arrayStudents[i].firstName)
                {
                    fout << j;
                }
                countStudents++;
                // cout << "cs " << countStudents << ' ';
                // cout << "del " << deltaMark << endl;
                fout << ' ' << arrayStudents[i].maxMark;
                fout << endl;
            }
            else if ((arrayStudents[i].maxMark != arrayStudents[i + 1].maxMark) && ((countStudents <= 3) || (deltaMark <= 2)))
            {
                for (char j : arrayStudents[i].lastName)
                {
                    fout << j;
                }
                fout << ' ';
                for (char j : arrayStudents[i].firstName)
                {
                    fout << j;
                }
                fout << ' ' << arrayStudents[i].maxMark;
                fout << endl;
                countStudents++;
                deltaMark++;
                if (deltaMark > 2)
                {
                    break;
                }
                // cout << "cs " << countStudents << ' ';
                // cout << "del " << deltaMark << endl;
                if ((countStudents > 3))
                {
                    break;
                }
            }
        }
    }
    else
    {
        cout << "Количество учеников не соответсвует условию задачи" << endl;
        return -1;
    }
}