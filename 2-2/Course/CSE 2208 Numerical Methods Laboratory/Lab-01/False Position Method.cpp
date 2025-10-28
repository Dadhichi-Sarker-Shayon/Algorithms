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
vector<pair<double, int>> False_position(double l, double u, double tol, double step,vector<pair<double, double>> &intervals)
{
    
    vector<pair<double, int>> roots;
    double x = l;
    while (x <= u)
    {
        if (f(x) * f(x + step) < 0)
        {
            intervals.push_back({x, x + step});
        }
        x = x + step;
    }
    for (auto interval : intervals)
    {

        double a = interval.first;
        double b = interval.second;

        double fa = f(a);
        double fb = f(b);

        double prev = a;
        double mid = a - f(a) * ((b - a) / (f(b) - f(a)));
        int iter = 0;
        while (fabs(mid - prev) >= tol )
        {

            double fmid = f(mid);
            if (fmid == 0.0)
            {
                break;
            }
            if (fa * fmid < 0)
            {
                b = mid;
                fb = fmid;
            }
            else if (fb * fmid < 0)
            {
                a = mid;
                fa = fmid;
            }
            prev = mid;
            mid = a - f(a) * ((b - a) / (f(b) - f(a)));
            iter++;
        }
        roots.push_back({mid, iter});
    }
    return roots;
}
int main()
{
    degree = 4;
    coef.resize(degree + 1);
    for (int i = 0; i <= degree; i++)
    {
        cin >> coef[i];
    }

    vector<pair<double, int>> roots;
    vector<pair<double, double>> ranges;
    double tol = 1e-4;
    double l = -sqrt(((coef[1] / coef[0]) * (coef[1] / coef[0])) - 2 * (coef[2] / coef[0]));
    double u = -1 * l;
    cout << l << " " << u << endl;
    roots = False_position(l, u, tol, 0.5, ranges);
    cout << "Roots\t\t\tIterations\t\t\tRanges" << endl;
    for (int i = 0; i < roots.size(); i++)
    {
        cout << roots[i].first << "\t\t\t" << roots[i].second<< "\t\t\t"<< ranges[i].first << " - " << ranges[i].second << endl;
    }
    return 0;
}
