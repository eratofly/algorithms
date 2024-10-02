#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <windows.h>

/*
    Охотникова Дарья Сергеевна
    ПС-22
    Задание 20
    VS Code 1.15.1
    20. Организовать  в основной  памяти  с помощью указателей
    очередь  из  стеков. Обеспечить  операции  ведения  стека  из
    начала  очереди, дополнения  и  продвижения  очереди,  выдачи
    содержимого очереди (9).
*/

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
void viewS(Stack *topS);
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

void deleteFromQ(Queue *&topQ)
{
    Stack *topS = topQ->pointerS;
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
        cout << t->key << ": ";
        Stack *topS = t->pointerS;
        viewS(topS);
        t = t->nextQ;
        cout << endl;
    }
}

void push(Queue *&topQ, int elem)
{
    Stack *topS = topQ->pointerS;
    Stack *t = new Stack;
    t->key = elem;
    t->nextS = topS;
    topS = t;
    topQ->pointerS = topS;
}

void pop(Queue *&topQ)
{
    Stack *topS = topQ->pointerS;
    if (topS)
    {
        Stack *t = topS;
        topS = topS->nextS;
        delete t;
        topQ->pointerS = topS;
    }
    else
    {
        cout << "Стек пуст" << endl;
    }
}

void clearS(Queue *&topQ)
{
    Stack *topS = topQ->pointerS;
    while (topS)
    {
        Stack *t = topS;
        topS = topS->nextS;
        delete t;
        topQ->pointerS = topS;
    }
}

void viewS(Stack *topS)
{
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
        cout << "Введите 0, чтобы продолжить ";
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

    while (answer != 6)
    {
        cout << "1 Включение в очередь" << endl;
        cout << "2 Удаление из очереди" << endl;
        cout << "3 Выдача очереди" << endl;
        cout << "4 Очистка очереди" << endl;
        cout << "5 Перейти к работе со стеком" << endl;
        cout << "6 Конец" << endl;
        cout << "Ваш выбор? ";
        cin >> answer;
        cout << endl;
        switch (answer)
        {
        case 1:
        {
            int num;
            int agree = 1;
            cout << "Введите целое число: ";
            cin >> num;
            addInQ(top, bottom, num);
            cout << "Число " << num << " добавилось в очередь" << endl;
            Sleep(timeDelay);
            while (agree != 2)
            {
                cout << "Хотите добавить элемент в стек?" << endl;
                cout << "1 Да" << endl;
                cout << "2 Нет" << endl;
                cout << "Ваш ответ: ";
                cin >> agree;
                switch (agree)
                {
                case 1:
                    int numS;
                    cout << "Введите целое число: ";
                    cin >> numS;
                    push(bottom, numS);
                    cout << "Число " << numS << " добавилось в стек" << endl;
                    Sleep(timeDelay);
                    cout << endl;
                    break;
                case 2:
                    break;
                }
            }
            cout << endl;
            break;
        }
        case 2:
            if (top)
            {
                deleteFromQ(top);
                cout << "Очередь сдвинулась" << endl;
            }
            else
            {
                cout << "Очердь пустая" << endl;
            }
            cout << endl;
            Sleep(timeDelay);
            break;
        case 3:
            if (top)
            {
                viewQ(top);
                continueProcess();
            }
            else
            {
                cout << "Очередь пустая" << endl;
                Sleep(timeDelay);
            }
            cout << endl;
            break;
        case 4:
        {
            if (top)
            {
                while (top)
                {
                    deleteFromQ(top);
                }
                top = 0;
                cout << "Очередь очистилась" << endl;
            }
            else
            {
                cout << "Очередь уже пустая" << endl;
            }
            cout << endl;
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
                    cout << "1 Добавление элемента в стек" << endl;
                    cout << "2 Удаление из стека" << endl;
                    cout << "3 Выдача стека" << endl;
                    cout << "4 Очистка стека" << endl;
                    cout << "5 Выход из редактора стека" << endl;
                    cout << "Ваш выбор? ";
                    cin >> answerStack;
                    cout << endl;
                    Stack *topS = top->pointerS;

                    switch (answerStack)
                    {
                    case 1:
                        int numS;
                        cout << "Введите целое число: ";
                        cin >> numS;
                        push(top, numS);
                        cout << "Число " << numS << " добавилось в стек" << endl;
                        Sleep(timeDelay);
                        cout << endl;
                        break;
                    case 2:
                        pop(top);
                        cout << "Стек сдвинулся" << endl;
                        cout << endl;
                        Sleep(timeDelay);
                        break;
                    case 3:
                        if (topS)
                        {
                            cout << "Ваш стек: ";
                            viewS(topS);
                            cout << endl;
                            continueProcess();
                        }
                        else
                        {
                            cout << "Cтек пуст" << endl;
                            Sleep(timeDelay);
                        }
                        cout << endl;
                        break;
                    case 4:
                        if (topS)
                        {
                            clearS(top);
                            cout << "Cтек очистился" << endl;
                        }
                        else
                        {
                            cout << "Cтек пуст" << endl;
                        }
                        cout << endl;
                        Sleep(timeDelay);
                        break;
                    case 5:
                        cout << "Вы вышли из редактора стека" << endl;
                        cout << endl;
                        Sleep(timeDelay);
                        break;
                    }
                }
            }
            else
            {
                cout << "Вы не можете добавить элемент в стек, так как очередь пустая" << endl;
                cout << endl;
            }
        }
        break;
        case 6:
            while (top)
            {
                deleteFromQ(top);
            }
            top = 0;
            cout << "Конец" << endl;
            break;
        }
    }
    return 0;
}