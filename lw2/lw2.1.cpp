#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <windows.h>

using namespace std;

struct Stack
{
    int key;
    Stack *nextS;
};

struct Queue
{
    int key;
    Stack *pointerS;
    Queue *nextQ;
};

void addInQ(Queue *&top, Queue *&bottom, int elem);
void deleteFromQ(Queue *&topQ);
void viewQ(Queue *&topQ);
void push(Queue *&topQ, int elem);
void pop(Queue *&topQ);
void viewS(Queue *topQ);
void clearS(Queue *&topQ);

void addInQ(Queue *&top, Queue *&bottom, int elem)
{
    Queue *t = new Queue;
    t->key = elem;
    t->pointerS = nullptr;
    if (top)
    {
        bottom->nextQ = t;
        bottom = t;
        bottom->nextQ = nullptr;
    }
    else
    {
        bottom = t;
        top = t;
        top->nextQ = nullptr;
        bottom->nextQ = nullptr;
    }
}

void deleteFromQ(Queue *&topQ) //������������ ��� �����
{
    // Stack *topS = topQ->pointerS;
    clearS(topQ);
    Queue *t = new Queue;
    t = topQ;
    topQ = t->nextQ;
    delete t;
}

void viewQ(Queue *&topQ)
{
    Queue *t = new Queue;
    t = topQ;
    while (t)
    {
        cout << t->key;
        viewS(t);
        t = t->nextQ;
        cout << endl;
    }
}

void push(Queue *&topQ, int elem) // ��������� � ����
{
    Stack *topS = topQ->pointerS;
    if (topS)
    {

        Stack *t = new Stack;
        t->key = elem;
        t->nextS = topS;
        topS = t;
    }
    else
    {
        Stack *t = new Stack;
        t->key = elem;
        t->nextS = nullptr;
        topS = t;
    }
    topQ->pointerS = topS;
}

void pop(Queue *&topQ)
{
    Stack *topS = topQ->pointerS;
    Stack *t = topS;
    topS = topS->nextS;
    delete t;
}

void clearS(Queue *&topQ)
{
    Stack *topS = topQ->pointerS;
    while (topS)
    {
        Stack *t = topS;
        topS = topS->nextS;
        delete t;
    }
}

void viewS(Queue *topQ)
{
    Stack *topS = topQ->pointerS;
    // Stack *t = topS;
    while (topS)
    {
        cout << topS->key << " ";
        topS = topS->nextS;
    }
}

void continueProcess()
{
    int y = 1;
    while (y != 0)
    {
        cout << "������� 0, ����� ���������� ";
        cin >> y;
        cout << endl;
    }
}

int main()
{
    int answer = 1;
    int timeDelay = 1000;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Queue *top = nullptr;
    Queue *bottom = nullptr;

    while (answer != 7)
    {
        cout << "1 ��������� � �������" << endl;
        cout << "2 �������� �� �������" << endl;
        cout << "3 ������ �������" << endl;
        cout << "4 ������� �������" << endl;
        cout << "5 ���������� � ����" << endl;
        cout << "6 �����" << endl;
        cout << "��� �����? ";
        cin >> answer;
        cout << endl;
        switch (answer)
        {
        case 1: // ��������� � �������
            int num;
            cout << "������� ����� �����: ";
            cin >> num;
            addInQ(top, bottom, num);
            cout << "����� " << num << " ���������� � �������" << endl;
            Sleep(timeDelay);
            break;
        case 2: // �������� �� �������
            if (top)
            {
                deleteFromQ(top);
                cout << "������� ����������" << endl;
            }
            else
            {
                cout << "������ ������" << endl;
            }
            Sleep(timeDelay);
            break;
        case 3: // ����� ������� �� �����
            if (top)
            {
                viewQ(top);
                continueProcess();
            }
            else
            {
                cout << "������� ������" << endl;
                Sleep(timeDelay);
            }
            break;
        case 4: //������� �������
        {
            if (top)
            {
                while (top)
                {
                    deleteFromQ(top);
                }
                top = 0;
                cout << "������� ����������" << endl;
            }
            else
            {
                cout << "������� ��� ������";
            }
            Sleep(timeDelay);
            break;
        }
        case 5:
        {
            int answerStack = 1;
            if (top)
            {
                while (answerStack != 5)
                {
                    cout << "1 ���������� �������� � ����" << endl;
                    cout << "2 �������� �� �����" << endl;
                    cout << "3 ������ �����" << endl;
                    cout << "4 ������� �����" << endl;
                    cout << "5 ����� �� ��������� �����" << endl;
                    cout << "��� �����? ";
                    cin >> answerStack;
                    cout << endl;
                    // Stack *topS = top->pointerS;

                    switch (answerStack)
                    {
                    case 1: // ��������� � �������
                        int numS;
                        cout << "������� ����� ����� ";
                        cin >> numS;
                        push(bottom, numS);
                        cout << "����� " << numS << " ���������� � ����" << endl;
                        Sleep(timeDelay);
                        break;
                    case 2:
                        if (topS)
                        {
                            pop(topQ);
                            cout << topS->key;
                            cout << "���������  ������ �����" << endl;
                        }
                        else
                        {
                            cout << "C��� ����" << endl;
                        }
                        Sleep(timeDelay);
                        break;
                    case 3:
                        cout << "��� ����: ";
                        viewS(top);
                        cout << endl;
                        continueProcess();
                        break;
                    case 4:
                        if (topS)
                        {
                            clearS(topS);
                            cout << "C��� ���������" << endl;
                        }
                        else
                        {
                            cout << "C��� ����" << endl;
                        }
                        Sleep(timeDelay);
                        break;
                    case 5:
                        topS = 0;
                        cout << "�� ����� �� ��������� �����" << endl;
                        Sleep(timeDelay);
                        break;
                    }
                }
            }
        }
        break;
        case 6:
            // clear(tops); // ������� ������� �����
            top = 0; // ������� clear �� ���������� top!
            cout << "�����";
            break;
        }
    }
    return 0;
}