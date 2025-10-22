#include <bits/stdc++.h>
using namespace std;
double f(double x)
{
    return x * x * x * x - 5 * x * x + 4;
}
bool stop(double prev, double curr, double tol)
{
    return fabs(prev - curr) < tol;
}
void Bisection(double l, double u, double tol, double step, vector<pair<double, double>> &intervals, vector<double> &roots,vector<double> &iteration)
{

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
        double  mid = a-f(a)*((b-a)/(f(b)-f(a)));
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
             mid = a-f(a)*((b-a)/(f(b)-f(a)));
            iter++;
        }
        iteration.push_back(iter);
        roots.push_back(mid);
    }
    //sort(roots.begin(), roots.end());
    //roots.erase(unique(roots.begin(), roots.end(), [tol](double a, double b)
     //                  { return fabs(a - b) < tol; }),
       //         roots.end());

    return ;
}
int main()
{
    double l, u, tol, X_max = 0.0;
    vector<pair<double, double>> intervals;
    vector<double> roots,iteration;

    X_max = fabs(sqrtf((-2) * (-5 / 1)));
    l = -X_max;
    cout << l << endl;
    u = X_max;
    cout << u << endl;
    tol = 0.0001;
    cout << tol << endl;
    double step;
    step = 0.5;
    cout << step << endl;
    Bisection(l, u, tol, step, intervals, roots, iteration);
    cout << "Roots found:\n";
    for (int i = 0; i < roots.size(); i++)
    {
        cout <<"In interval ("<< intervals[i].first << ", " << intervals[i].second << ") found root: " << roots[i] << " in " << iteration[i] << " iterations\n";
    }
    return 0;
}
