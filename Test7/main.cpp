#include "stdio.h"
#include "iostream"
#include <math.h>
#include "vector"
using namespace std;

void printTable(vector<vector<int> > table)
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            cout << table[i][j] << ' ';
        }
        cout << '\n';
    }
}

vector<vector<int> > fillTable(int N, int M, int sequence[])
{
    vector<vector<int> > table;

    int k = 0;

    for (int i = 0; i < N; i++)
    {
        vector<int> block;
        for (int j = 0; j < M; j++)
            block.push_back(sequence[k + j]);

        k += M;
        table.push_back(block);
    }
    return table;
}

bool IsEqual(vector<int> block, int pos, int B[], int m)
{
    for (int i = 0; i < m; i++)
    {
        if (block[pos + i] != B[i])
            return false;
    }
    return true;
}

vector<int> fillWi(int m, vector<vector<int> > table, int B[])
{
    vector<int> Wi(table.size(), 0);

    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            if (IsEqual(table[i], j, B, m))
            {
                Wi[i]++;
                j += m - 1;
            }
        }
    }
    return Wi;
}

float nonOverlappingTemplateMatching(int m, int n, int sequence[], int B[], int N, int M)
{
    vector<vector<int> > table = fillTable(N, M, sequence);
    vector<int> Wi = fillWi(m, table, B);

    float mu = (M - m + 1) / pow(2, m);
    float sigma2 = M * ((1 / (pow(2, m)) - ((2 * m - 1) / pow(2, 2 * m))));

    float X2 = 0;

    for (int i = 0; i < N; i++)
    {
        X2 += pow((Wi[i] - mu), 2) / (sigma2);
    }

    float Pvalue = 3; // llamar a la funcion igamac(N/2,X2/2)

    printTable(table);
    printTable(vector<vector<int> >(1, Wi));

    return Pvalue;
}

// Driver Code
int main()
{
    int seq[20] = {1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0};
    int B[3] = {0, 0, 1};
    float Pvalue = nonOverlappingTemplateMatching(3, 20, seq, B, 2, 10);
    cout << Pvalue << '\n';
    return 0;
}
