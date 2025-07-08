#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int mod(int a, int b)
{
    int r = a % b;
    if (r < 0) r += abs(b);
    return r;
}
int main()
{
    srand(time(0));
    int n, k, S, s, sum;
    while (1)
    {
        sum = 0;
        cout << "NUMBER OF SHARES: ";
        cin >> n;
        if (n < 1) return 0;
        cout << "MAXIMAL SECRET: ";
        cin >> k;
        if (k < 1) return 0;
        cout << "SECRET (BETWEEN 0 AND " << k - 1 << "): ";
        cin >> S;
        if (S < 0 || S >= k) return 0;
        for (int i = 0; i < n - 1; i++)
        {
            s = (rand() * rand()) % k;
            sum += s;
            cout << "sh" << i + 1 << "\t: " << s << endl;
        }
        cout << "sh" << n << "\t: " << mod(S - sum, k) << endl;
        sum += mod(S - sum, k);
        cout << "CALCULATED SECRET = " << sum % k << endl;
        if (sum % k == S) cout << "OK";
        else cout << "ERROR";
        cout << endl << endl;
    }
}
