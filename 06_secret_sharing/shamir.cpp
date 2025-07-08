#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
using namespace std;

vector<long long> primes;

bool is_prime(long long a)
{
    for (long long i = 0; i < primes.size(); i++)
    {
        if (a % primes[i] == 0) return 0;
        if (primes[i] * primes[i] > a) break;
    }
    return 1;
}

void redefine_primes(vector<long long> &pri)
{
    long long div = 0;
    while (1)
    {
        if (pri[div] < 100000) div++;
        else break;
    }
    pri.erase(pri.begin(), pri.begin() + div);
}

long long mod(long long a, long long b)
{
    return (a % b + b) % b;
}

long long power_mod(long long base, long long exp, long long prime)
{
    long long result = 1;
    base = mod(base, prime);
    while (exp > 0)
    {
        if (exp % 2 == 1) result = (result * base) % prime;
        base = (base * base) % prime;
        exp = exp / 2;
    }
    return result;
}

int main()
{
    srand(time(0));
    primes.push_back(2);
    for (long long i = 3; i < 1000000; i++) if (is_prime(i)) primes.push_back(i);
    redefine_primes(primes);
    long long p, n, t, S, sum, fr;
    while (1)
    {
        p = primes[(rand() * rand()) % primes.size()];
        cout << "NUMBER OF ALL SHARES (BETWEEN 1 AND " << p - 1 << "): ";
        cin >> n;
        if (n < 1 || n > p - 1) return 0;
        cout << "NUMBER OF NEEDED SHARES (BETWEEN 1 AND " << n << "): ";
        cin >> t;
        if (t < 1 || t > n) return 0;
        cout << "SECRET (BETWEEN 0 AND " << p - 1 << "): ";
        cin >> S;
        if (S < 0 || S > p - 1) return 0;
        vector<long long> coeff, shares;
        coeff.resize(t);
        shares.resize(n);
        for (long long i = 1; i < t; i++) coeff[i] = rand() % 1000;
        cout << "ALL SHARES:" << endl;
        for (long long i = 0; i < n; i++)
        {
            sum = S;
            for (long long j = 1; j < t; j++) sum = (sum + coeff[j] * power_mod(i + 1, j, p)) % p;
            shares[i] = sum;
            cout << "sh" << i + 1 << "\t: (" << i + 1 << ", " << shares[i] << ")" << endl;
        }
        set<long long> used;
        while (used.size() < t) used.insert((rand() * rand()) % n);
        cout << endl;
        cout << "SELECTED SHARES:" << endl;
        sum = 0;
        for (long long i : used)
        {
            cout << "sh" << i + 1 << "\t: (" << i + 1 << ", " << shares[i] << ")" << endl;
            fr = 1;
            for (long long j : used)
            {
                if (i != j)
                {
                    long long cur = 0 - j - 1;
                    cur = mod(cur, p);
                    fr = fr * cur;
                    fr = mod(fr, p);
                    cur = power_mod(i - j, p - 2, p);
                    fr = fr * cur;
                    fr = mod(fr, p);
                }
            }
            fr = mod(fr * shares[i], p);
            sum = mod(sum + fr, p);
        }
        cout << endl;
        cout << "CALCULATED SECRET = " << sum << endl;
        if (sum == S) cout << "OK";
        else cout << "ERROR";
        cout << endl << endl;
    }
}
