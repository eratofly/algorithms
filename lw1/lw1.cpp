#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <windows.h>

/*
    ���������� ����� ���������
    ��-22
    ������� 27
    VS Code 1.15.1
    �� ���� �������� �������� � ����� ��������� ��������� 9-�
    ������� ��������� ������� �����. � ������ ������ ���������� 
    ���������� �������� N, ������� �� ������ 10, �� �� �����������
    100, ������ �� ��������� N ����� ����� ��������� ������:
    <�������> <���> <������>, ��� <�������> � ������, ��������� �� 
    ����� ��� �� 20 ��������, <���> � ������, ��������� �� ����� ���
    �� 15 �������� <������> � ����� ������ ��� ����� �����, 
    ��������������� ������� �� ������������ �������. <�������> � 
    <���>, � ����� <���> � <������> ��������� ����� ��������. 
    ������ ������� ������: ������ ���� 4 5 4
    ��������� �������� ���������, ������� ����� �������� �� ����� 
    ������� � ����� ���� ������ �� �������� ����� ��������. ���� 
    ����� ��������� ���� �������, ��������� ��� �� ������� ����, 
    ��� � ���� �� ���� ������, �� ������� ������� � �� ������� � 
    �����. ��������� ����� � ������� ����� �������� � ������������ 
    ������� (8).
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

    cout << "������� ��� �������� �����: ";
    cin >> finName;

    ifstream fin;
    fin.open(finName);

    if (!fin.is_open())
    {
        cout << "����" << finName << " �� ������� �������!\n";
        return -1;
    }

    cout << "������� ��� ��������� �����: ";
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
            cout << "���� " << foutName << " �� ������� �������!\n";
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
        cout << "���������� �������� �� ������������ ������� ������" << endl;
        return -1;
    }
}