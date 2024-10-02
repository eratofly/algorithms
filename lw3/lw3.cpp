#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <climits>

/*
    Охотникова Дарья Сергеевна
    ПС-22
    Задание 20
    VS Code 1.15.1
    24. В  листьях  И-ИЛИ  дерева,  соответствующего некоторому
    множеству  конструкций,  заданы   значения   массы.   Известно
    максимально допустимое значение массы изделия. Требуется усечь
    дерево   так,   чтобы   дерево    включало    все    элементы,
    соответствующие  допустимым  значениям массы,  но не содержало
    "лишних" вершин.  Конечное дерево выдать на экран в  наглядном
    виде (13).
*/

using namespace std;

struct Node
{
    char key;
    int min;
    int max;
    int acceptableMin = 0;
    Node *fath;
    vector<Node *> sons;
    bool isOverweight;
    bool isOrNode;
    int height;
};

void setWeight(Node *node)
{
    bool flag = false;
    if (!node->isOverweight)
    {
        if (!node->sons.empty())
        {
            for (Node *&son : node->sons)
            {
                if (!son->sons.empty())
                {
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                for (Node *&son : node->sons)
                {
                    setWeight(son);
                }
            }
            if (node->isOrNode)
            {
                int max = INT_MIN;
                int min = INT_MAX;
                for (Node *&son : node->sons)
                {
                    if (!son->isOverweight)
                    {
                        if (son->max > max)
                        {
                            max = son->max;
                        }
                        if (son->min < min)
                        {
                            min = son->min;
                        }
                    }
                }
                node->max = max;
                node->min = min;
            }
            else
            {
                int sumMax = 0;
                int sumMin = 0;
                for (Node *&son : node->sons)
                {
                    if (!son->isOverweight)
                    {
                        sumMax += son->max;
                        sumMin += son->min;
                    }
                }
                node->max = sumMax;
                node->min = sumMin;
            }
        }
        else if (!node->isOverweight)
        {
            if (node->fath->isOrNode)
            {
                if (node->fath->max < node->max)
                {
                    node->fath->max = node->max;
                }
                if (node->fath->min > node->min)
                {
                    node->fath->min = node->min;
                }
            }
            else
            {
                node->fath->max += node->max;
                node->fath->min += node->min;
            }
        }
    }
}

void printNodes(ofstream &fout, Node *node)
{
    if (!node->isOverweight)
    {
        for (int i = 0; i < node->height; i++)
        {
            fout << '.';
        }
        fout << node->key << ' ';
        fout << node->min << ' ';
        fout << node->max << ' ';
        if (!node->sons.empty())
        {
            if (node->isOrNode)
            {
                fout << 'o' << endl;
            }
            else
            {
                fout << 'a' << endl; 
            }
        }
        else
        {
            fout << endl;
        }
       
        for (Node *&son : node->sons)
        {
            printNodes(fout, son);
        }
    }
}

int checkTree(ofstream &fout, Node *node, int maxWeight)
{
    if (node->min > maxWeight)
    {
        fout << "Максимальный вес меньше минимального веса корня" << endl;
        return -1;
    }
    if (node->max < maxWeight)
    {
        fout << "Максимальный вес больше максимального веса корня" << endl;
        return -1;
    }
}

void setAcceptableMin(Node *node, int maxWeight)
{
    if (!node->isOrNode)
    {
        for (Node *&son : node->sons)
        {
            if (!son->sons.empty())
            {
                int sumMinSons = 0;
                for (Node *&sonT : node->sons)
                {
                    if (sonT->key != son->key)
                    {
                        sumMinSons += sonT->min;
                    }
                }
                son->acceptableMin += maxWeight - sumMinSons;
                setAcceptableMin(son, son->acceptableMin);
            }
        }
    }
    else
    {
        for (Node *&son : node->sons)
        {
            if (!son->sons.empty())
            {
                son->acceptableMin = son->fath->acceptableMin;
                setAcceptableMin(son, son->acceptableMin);
            }
        }
    }
}

void setTruncatedTree(Node *node)
{
    for (Node *&son : node->sons)
    {
        if (son->min > son->fath->acceptableMin || (son->fath->isOverweight && !son->fath->isOrNode))
        {
            son->isOverweight = true;
            son->min = 0;
            son->max = 0;
        }
        if (!son->sons.empty())
        {
            setTruncatedTree(son);
        }
    }
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int maxWeight = 0;
    string strFin;
    string finName;
    string foutName;

    cout << "Введите имя входного файла: ";
    cin >> finName;

    ifstream fin;
    fin.open(finName);

    if (!fin.is_open())
    {
        cout << "Файл " << finName << " не открывается" << endl;
        return -1;
    }

    cout << "Введите имя выходного файла: ";
    cin >> foutName;

    Node *prevNode = new Node;
    Node *root = new Node;
    if (getline(fin, strFin))
    {
        maxWeight = stoi(strFin);
    }
    while (getline(fin, strFin))
    {
        string num = "";
        Node *node = new Node;
        node->isOverweight = false;
        node->height = 0;
        for (const char ch : strFin)
        {
            if (ch == '.')
            {
                node->height += 1;
            }
            if ((ch >= 'a') && (ch <= 'z'))
            {
                node->key = ch;
                node->isOrNode = false;
            }
            if ((ch >= 'A') && (ch <= 'Z'))
            {
                node->key = ch;
                node->isOrNode = true;
            }
            if ((ch >= '0') and (ch <= '9'))
            {
                num += ch;
            }
        }
        node->min = stoi(num);
        node->max = stoi(num);
        if (node->height == 0)
        {
            node->fath = nullptr;
            root = node;
            root->acceptableMin = maxWeight;
        }
        else if (node->height - prevNode->height == 1)
        {
            node->fath = prevNode;
            prevNode->sons.push_back(node);
        }
        else if (node->height - prevNode->height == 0)
        {
            node->fath = prevNode->fath;
            prevNode->fath->sons.push_back(node);
        }
        else if (node->height - prevNode->height <= -1)
        {
            int deltaHeight = prevNode->height - node->height;
            for (int i = 0; i <= deltaHeight; i++)
            {
                node->fath = prevNode->fath;
                prevNode = prevNode->fath;
            }
            node->fath->sons.push_back(node);
        }
        prevNode = node;
    }

    ofstream fout;
    fout.open(foutName);
    if (!fout.is_open())
    {
        cout << "Файл " << foutName << " не открывается" << endl;
        return -1;
    }

    if (root == nullptr)
    {
        return -1;
    }

    setWeight(root);

    if (checkTree(fout, root, maxWeight) == -1)
    {
        return -1;
    }

    setAcceptableMin(root, maxWeight);
    setTruncatedTree(root);
    setWeight(root);

    printNodes(fout, root);

    return 0;
}