#include <math.h>
#include "vector"
#include <iostream>

using namespace std;

#define endl '\n'


vector<float> re, im;

vector<float> specificModule(int n)
{
    vector<float> modules_return;
    
    for (int i = 0; i < n; i++)
    {
        float real = re[i];
        float imag = im[i];
        float abs = sqrt(real * real + imag * imag);
        
        modules_return.push_back(abs);
    }
    
    return modules_return;
}

// Function to calculate the DFT
void calculateDFT(int len, int xn[])
{
    im.clear();
    re.clear();    

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

    for(int i = 0; i < N; ++i) {
	im.push_back(Xi[i]);
	re.push_back(Xr[i]);
    }

}

// n is the length of the bit string  secuence is de random secuences of ceros and ones
float DiscreteFourierTransform(int n, int secuence[])
{

    int X[n]; // transform de secuence in ceros and ones

    for (int i = 0; i < n; i++)
        X[i] = 2 * secuence[i] - 1;

    calculateDFT(n, X);
    
    //for (int i = 0; i < n; i++)
    //{
    //    cout << re[i] << endl;
    //    cout << im[i] << endl;
    //}

    vector<float> modules = specificModule((int)(n / 2));

    
    //for (int i = 0; i < n; i++)
    //    cout << modules[i] << endl;


    float T = sqrt(log(1 / 0.05) * n);
    float N0 = 0.95 * (n / 2);

    int N1 = 0;
    
    for (int i = 0; i < modules.size(); i++)
        if (modules[i] < T)
            N1++;

    float d = (N1 - N0) / (sqrt(n * 0.95 * 0.05 / 4));
    float p_value = erfc(abs(d) / sqrt(2));

    return p_value;
}


int main()
{
    // 100111
    int n = 6;
    int a[6] = {1, 0, 0, 1, 1, 1};
    
    float p_value = DiscreteFourierTransform(n, a);
    
    cout << "p_value: " << p_value << endl;
    
    
    return 0;
}
