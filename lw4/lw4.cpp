#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
#define vertexes 5

int checkNumber(int numb)
{
    int count = 0;
    while (numb)
    {
        numb /= 10;
        count++;
    }
    return count;
}

void printStartTable()
{
    cout << "N......";
    for (int i = 0; i < vertexes; i++)
    {
        cout << i + 1;
        if (i != vertexes - 1)
        {
            cout << "......";
        }
    }
    cout << endl;
    int index = 0;
    cout << index << "......";
    for (int i = 0; i < vertexes; i++)
    {
        cout << "inf";
        if (i != vertexes - 1)
        {
            cout << "....";
        }
    }

    cout << endl;
}

bool isValidEdge(int u, int v, vector<bool> inMST)
{
    if (u == v)
        return false;
    if (inMST[u] == false && inMST[v] == false)
        return false;
    else if (inMST[u] == true && inMST[v] == true)
        return false;
    return true;
}

void primMST(int cost[][vertexes])
{
    vector<bool> inMST(vertexes, false);

    inMST[0] = true;

    int edgeCount = 0, minCost = 0;
    printStartTable();
    int v = 1;
    int currVertex = 1;
    int step = 0;
    while (edgeCount < vertexes - 1)
    {
        // Find minimum weight valid edge.
        int min = INT_MAX, a = -1, b = -1;

        for (int i = 0; i < vertexes; i++)
        {
            for (int j = 0; j < vertexes; j++)
            {
                if (cost[i][j] < min)
                {
                    if (isValidEdge(i, j, inMST))
                    {
                        min = cost[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }

        step++;
        cout << step;
        for (int i = 0; i < 7 - checkNumber(step); i++)
        {
            cout << ".";
        }
        for (int i = currVertex - 1; i < currVertex; i++)
        {
            for (int j = 0; j < vertexes; j++)
            {
                if (cost[i][j] == INT_MAX)
                {
                    cout << "inf....";
                }
                else
                {
                    cout << cost[i][j];
                    cout << "(" << a + 1 << ")";
                    for (int k = 0; k < 4 - checkNumber(cost[i][j]); k++)
                    {
                        cout << ".";
                    }
                }
            }
        }

        // for (int i = 0; i < 7 - checkNumber(step); i++)
        // {
        //     cout << ".";
        // }

        step++;
        cout << endl;
        cout << step;
        for (int i = 0; i < 7 - checkNumber(step); i++)
        {
            cout << ".";
        }

        for (int i = currVertex - 1; i < currVertex; i++)
        {
            for (int j = 0; j < vertexes; j++)
            {
                if (cost[i][j] == INT_MAX)
                {
                    cout << "inf....";
                }
                else
                {
                    cout << cost[i][j];
                    cout << "(" << a + 1 << ")";
                    if (cost[i][j] == min)
                    {
                        cout << "!";
                        for (int k = 0; k < 3 - checkNumber(cost[i][j]); k++)
                        {
                            cout << ".";
                        }
                    }
                    else
                    {
                        for (int k = 0; k < 4 - checkNumber(cost[i][j]); k++)
                        {
                            cout << ".";
                        }
                    }
                }
            }
        }

        if (a != -1 && b != -1)
        {
            printf("Edge %d:(%d, %d) cost: %d \n",
                   edgeCount++, a, b, min);
            minCost = minCost + min;
            inMST[b] = inMST[a] = true;
        }
        v++;
        step++;
    }
    printf("\n Minimum cost= %d \n", minCost);
}

// driver program to test above function
int main()
{
    /* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
    int cost[][vertexes] = {
        {INT_MAX, 2, INT_MAX, 6, INT_MAX},
        {2, INT_MAX, 3, 8, 5},
        {INT_MAX, 3, INT_MAX, INT_MAX, 7},
        {6, 8, INT_MAX, INT_MAX, 9},
        {INT_MAX, 5, 7, 9, INT_MAX},
    };

    // Print the solution
    primMST(cost);

    return 0;
}