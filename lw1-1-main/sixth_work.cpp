#include <iostream>
#include <math.h>


using namespace std;


double s(double x, int n)
{
    double s = 0; double r = -1;
    for (int k = 1; k <= n; k++)
    {
        r = -r * x * x;
        s += r / (4 * k * k - 2 * k);
    }
    return s;
}


double y(double x, int n) { return x * atan(x) - log(pow(1 + x * x, 1 / 2.)); }


double sy(double x, int n) { return fabs(y(x,n) - s(x,n));} 


void Out_Rez(double a, double h, double b, int n)
{
    for (double x = a; x <= b; x += h)
    {
        cout << "x=" << x;
        cout << "\t";
        cout << "s(x)=" << s;
        cout << "\t";
        cout << "y(x)=" << y;
        cout << "\t";
        cout << "\t|s-y(x)|=" << fabs(y(x, n) - sy(x, n)) << endl;
    }
}


int main()
{
    double a, b, h;
    int n;

    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;
    cout << "Input h: ";
    cin >> h;
    cout << "Input n: ";
    cin >> n;

    Out_Rez(a, h, b, n);
    system("pause");
    return 0;
}
