#include <bits/stdc++.h>
using namespace std;
vector<double> coef;
int degree;
double f(double x)
{
    double value = 0.0;
    for (int i = 0; i <= degree; i++)
    {
        value += coef[i] * pow(x, degree - i);
    }
    return value;
}
void print_function()
{
    if (coef[0] != 0)
    {
        cout << coef[0] << "x^" << degree;
    }
    for (int i = 1; i <= degree; i++)
    {
        if (coef[i] == 0)
        {
            continue;
        }
        if (coef[i] > 0)
        {
            cout << "+";
        }
        cout << coef[i] << "x^" << degree - i;
    }
    cout << endl;
}
vector<pair<double, double>> ranges(double step)
{
    vector<pair<double, double>> res;
    double dmax = 0.0;
    for (int i = 0; i <= degree; i++)
    {
        dmax = max(dmax, fabs(coef[i] / coef[0]));
    }
    double low = -(1 + dmax);
    double high = (1 + dmax);
    while (low < high)
    {
        if (f(low) * f(low + step) < 0)
        {
            res.push_back({low, low + step});
        }
        low += step;
    }
    return res;
}
pair<double, int> secant(double x0, double tol)
{
    double f0 = f(x0);
    double x1 = x0 + 1e-12;
    double f1 = f(x1);
    if (fabs(f0) < 1e-12)
    {
        return {x0, 0};
    }
    if (fabs(f1) < 1e-12)
    {
        return {x1, 0};
    }
    int iter = 0;
    while (fabs(x1 - x0) >= tol && fabs(f1) >= tol)
    {
        iter++;
        double x2 = x1 - f1 * ((x1 - x0) / (f1 - f0));
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f(x1);
        if (fabs(f1) < 1e-12)
        {
            return {x1, iter};
        }
    }
    return {x1, iter};
}
int main()
{
    cin >> degree;
    coef.resize(degree + 1);
    for (int i = 0; i <= degree; i++)
    {
        cin >> coef[i];
    }
    print_function();

    double tol = 1e-3;
    vector<pair<double, int>> roots;
    vector<pair<double, double>> rgs = ranges(0.45);

    for (auto rg : rgs)
    {

        pair<double, int> root = secant(rg.first, tol);
        bool unique = true;
        for (auto r : roots)
            if (fabs(r.first - root.first) < tol)
                unique = false;

        if (unique)
            roots.push_back(root);
    }
    cout << "Root\t\tIterations\t\tRange" << endl;

   for(int i=0;i<roots.size();i++)
   {
        cout << roots[i].first << "\t\t" << roots[i].second << "\t\t\t";
        cout << "[" << rgs[i].first << ", " << rgs[i].second << "]" << endl;
   }

    return 0;
}