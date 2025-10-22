#include <bits/stdc++.h>
using namespace std;
double f(double x)
{
    //return 3 * x - cos(x) - 1;
    return x*x-4*x-10;
}
bool stop(double prev, double curr, double tol)
{
    return fabs(prev - curr) < tol;
}
vector<double> Bisection(double l, double u, double tol, double step)
{
    vector<pair<double, double>> intervals;
    vector<double> roots;
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
        if (fa * fb > 0)
        {
            cout << "invalid interval\n";
            continue;
        }
        double prev = a;
        double mid = (a + b) / 2.0;
        int max_iter = 1000;
        int iter = 0;
        while (!stop(prev, mid, tol) && iter < max_iter)
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
            mid = (a + b) / 2.0;
            iter++;
        }
        roots.push_back(mid);
    }
    sort(roots.begin(), roots.end());
    roots.erase(unique(roots.begin(), roots.end(), [tol](double a, double b)
                       { return fabs(a - b) < tol; }),
                roots.end());

    return roots;
}
int main()
{
    double l, u, tol;
    cout << "Enter lower bound: ";
    cin >> l;
    cout << l << endl;
    cout << "Enter upper bound: ";
    cin >> u;
    cout << u << endl;
    cout << "Enter tolerance: ";
    cin >> tol;
    cout << tol << endl;
    cout << "Enter step size: ";
    double step;
    cin >> step;
    cout<< step << endl;
    vector<double> roots = Bisection(l, u, tol, step);
    cout << "Roots found:\n";
    for (double root : roots)
    {
        cout << root << "\n";
    }
    return 0;
}
