#include "stdio.h"
#include "iostream"
#include <math.h>
#include "vector"

using namespace std;

struct ImaginarieNumbers
{
    float *re;
    float *im;
    /* data */
};

vector<float> mymodule(ImaginarieNumbers numbers, int n)
{
    vector<float> modules_return;
    for (int i = 0; i < n; i++)
    {
        float real = numbers.re[i];
        float imag = numbers.im[i];
        float abs = sqrt(real * real + imag * imag);
        modules_return.push_back(abs);
    }
    return modules_return;
}

// Function to calculate the DFT
ImaginarieNumbers calculateDFT(int len, int xn[])
{
    float Xr[len];
    float Xi[len];
    int i, k, n = 0;

    int N = len;

    for (k = 0; k < N; k++)
    {
        Xr[k] = 0;
        Xi[k] = 0;
        for (n = 0; n < len; n++)
        {
            Xr[k] = (Xr[k] + xn[n] * cos(2 * 3.141592 * k * n / N));
            Xi[k] = (Xi[k] + xn[n] * sin(2 * 3.141592 * k * n / N));
        }
    }
    ImaginarieNumbers ret;
    ret.im = Xi;
    ret.re = Xr;
    return ret;
}

// n is the length of the bit string  secuence is de random secuences of ceros and ones
float DiscreteFourierTransform(int n, int secuence[])
{

    int d = 0;
    int X[n]; // transform de secuence in ceros and ones

    for (int i = 0; i < n; i++)
        X[i] = 2 * secuence[i] - 1;

    ImaginarieNumbers S = calculateDFT(n, X);
    for (int i = 0; i < n; i++)
    {
        cout << S.re[i] << '\n';
        cout << S.im[i] << '\n';
    }

    vector<float> modules = mymodule(S, (int)(n / 2));

    float T = sqrt(log(1 / 0.05) * n);

    float N0 = 0.95 * (n / 2);

    int N1 = 0;
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i] < T)
            N1++;
    }

    float d = (N1 - N0) / (sqrt(n * 0.95 * 0.05 / 4));

    float p_value = erfc(abs(d) / sqrt(2));

    return p_value;
    // for (int i = 0; i < (int)(n / 2); i++)
    // {
    //     cout << modules[i] << '\n';
    // }
}

// Driver Code
int main()
{
    // 100111
    int n = 6;
    int a[6] = {1, 0, 0, 1, 1, 1};
    DiscreteFourierTransform(n, a);
    return 0;
    // 2.0
    // 3.4641016151377544
    // 2.0

    // 0:(2+0j)
    // 1:3.4641016151377544j
    // 2:(2+0j)
    // 3:-2.220446049250313e-16j
    // 4:(2+0j)
    // 5:-3.4641016151377544j
}
