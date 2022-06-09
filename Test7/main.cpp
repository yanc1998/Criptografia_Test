#include "stdio.h"
#include "iostream"
#include <math.h>
#include "vector"

using namespace std;

#define endl '\n'


void printTable(vector<vector<int>> table)
{
    for (int i = 0; i < table.size(); i++, cout << endl)
        for (int j = 0; j < table[i].size(); j++)
            cout << table[i][j] << ' ';
}

vector<vector<int>> fillTable(int N, int M, int sequence[])
{
    vector<vector<int>> table;

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
        if (block[pos + i] != B[i])
            return false;

    return true;
}

vector<int> fillWi(int m, vector<vector<int> > table, int B[])
{
    vector<int> Wi(table.size(), 0);

    for (int i = 0; i < table.size(); i++)
        for (int j = 0; j < table[i].size(); j++)
            if (IsEqual(table[i], j, B, m))
            {
                Wi[i]++;
                j += m - 1;
            }
            
    return Wi;
}


double *gammaFunction(int maxm, double t) {
    double s, term, *F;
    double maxt = 20, eps = 1e-17;
    int m;
    
    F = (double *)malloc((maxm + 1) * sizeof(double));
    
    if (t < maxt) {
        term = 1.0 / (2 * maxm + 1);
        s = term;
        m = 1;
        
        while (fabs(term) > eps) {
            term *= (2 * t) / (2 * maxm + 2 * m + 1);
            s += term;
            m++;
        }
        
        F[maxm] = s * exp(-t);

        for (m = maxm - 1; m >= 0; m--)
            F[m] = (2 * t * F[m + 1] + exp(-t)) / (2 * m + 1);
            
    } else {
        F[0] = 0.5 * sqrt(M_PI/t) * erf(sqrt(t));
        for (m = 0; m <= maxm - 1; m++)
            F[m + 1] = ((2 * m + 1) * F[m] - exp(-t)) / (2 * t);
    }
    return F;
}


float nonOverlappingTemplateMatching(int m, int n, int sequence[], int B[], int N, int M)
{
    vector<vector<int>> table = fillTable(N, M, sequence);
    vector<int> Wi = fillWi(m, table, B);

    float mu = (M - m + 1) / pow(2, m);
    float sigma2 = M * ((1 / (pow(2, m)) - ((2 * m - 1) / pow(2, 2 * m))));

    float X2 = 0;

    for (int i = 0; i < N; i++)
        X2 += pow((Wi[i] - mu), 2) / (sigma2);

    float Pvalue = (float)(*gammaFunction(N / 2, (double)(X2 / 2)));

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
    
    cout << Pvalue << endl;
    
    return 0;
}
