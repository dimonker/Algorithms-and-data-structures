#include <fstream>
#include <iomanip>
#include <cassert>

using namespace std;

int main()
{
    //ifstream fin("garland.in");
    //ofstream out("garland.out");
    ifstream fin("input.txt");
    ofstream out("output.txt");
    double height, result;
    int n;

    fin >> n >> height;

    double l = 0, r = height;

    while ((r - l) > 0.01 / (n - 1))
    {
        double mid = (l + r) / 2;
        double prev = height;
        double curr = mid;
        bool flag;
        if (mid > 0)
            flag = true;
        else
            flag = false;

        for (int i = 3; i <= n; i++)
        {
            double next = 2 * curr - prev + 2;
            if (flag && next > 0)
                flag = true;
            else flag = false;
            prev = curr;
            curr = next;
        }
        if (flag)
        {
            r = mid;
            result = curr;
        }
        else
            l = mid;
    }
    out << fixed << setprecision(2) << result;

    return 0;
}