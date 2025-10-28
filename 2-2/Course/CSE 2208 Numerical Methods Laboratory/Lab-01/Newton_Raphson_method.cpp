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
double df(double x)
{
    double value = 0.0;
    for (int i = 0; i < degree; i++)
    {
        value += coef[i] * (degree - i) * pow(x, degree - i - 1);
    }
    return value;
}
void print_function()
{
    cout << "f(x)=";
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
vector<double> rangess(double n)
{
    double dmax =0.0;
    for (int j = 0; j <= degree; j++)
    {
        dmax = max(dmax, fabs(coef[j] / coef[0]));
    }
    double low = -(1 + dmax);
    double high = (1 + dmax);

    vector<double> res;
    while ( low < high)
    {
        if (f(low) * f(low + n) < 0)
        {
            if (fabs(f(low)) < fabs(f(low + n)))
            {
                res.push_back(low);
            }
            else
            {
                res.push_back(low + n);
            }
        }
        low += n;
    }
    return res;
}
pair<double, int> newton_raphson(double initial_guess, double tol)
{
    double x0 = initial_guess;
    double fx = f(x0);
    if (fabs(fx) < 1e-12)
    {
        return {x0, 0};
    }
    double dfx = df(x0);
    if (fabs(dfx) <= 1e-12)
    {
        return {NAN, -1};
    }
    double x1 = x0 - fx / dfx;

    int iter = 0;
    while (fabs(x1 - x0) >= tol)
    {
        iter++;
        x0 = x1;
        fx = f(x0);
        if (fabs(fx) < 1e-12)
        {
            return {x0, iter};
        }
        dfx = df(x0);
        if (fabs(dfx) <= 1e-12)
        {
            return {NAN, -1};
        }
        x1 = x0 - fx / dfx;
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
    vector<pair<double, int>> roots;
    vector<double> initial_guesses = rangess(0.45);
    double tol = 1e-6;
    for (double guess : initial_guesses)
    {
        pair<double, int> root = newton_raphson(guess, tol);
        if (isnan(root.first))
            continue;
        bool unique = true;
        for (int i = 0; i < roots.size(); i++)
        {
            if (fabs(root.first - roots[i].first) < tol)
                unique = false;
        }
        if (unique)
            roots.push_back(root);
    }
    cout << "Roots\t\t\tIterations" << endl;
    for (int i = 0; i < roots.size(); i++)
    {
        cout << roots[i].first << "\t\t\t" << roots[i].second << endl;
    }
    return 0;
}