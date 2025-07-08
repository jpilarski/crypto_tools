#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

vector<long long> primes;
string dialog;
long long users, n, g, private_keys[20], calculated_values[20], new_values[20];
bool check = true;

bool prime(long long a)
{
    for (long long i = 2; i * i <= a; i++) if (a % i == 0) return false;
    return true;
}

long long power(long long base, long long exp, long long mod)
{
    long long result = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

void prime_and_primitive(long long &n, long long &g)
{
    bool run = true;
    n = primes[rand() % primes.size()];
    g = n;
    while (run)
    {
        g--;
        vector<bool> check;
        check.resize(n);
        run = false;
        for (long long i = 1; i < n; i++)
        {
            long long pow = power(g, i, n);
            if (check[pow])
            {
                run = true;
                break;
            }
            check[pow] = true;
        }
    }
}

int main()
{
    srand(time(0));
    for (long long i = 1000; i < 10000; i++) if (prime(i)) primes.push_back(i);
    while (1)
    {
        cout << "Enter the number of participants for the Diffie-Hellman algorithm (2 to 20): ";
        cin >> dialog;
        cout << endl;
        for (char c : dialog) if(!isdigit(c)) return 0;
        users = stoi(dialog);
        if (users < 2 || users > 20) return 0;
        prime_and_primitive(n, g);
        for (long long u = 0; u < users; u++)
        {
            private_keys[u] = rand() % 9000 + 1000;
            calculated_values[u] = g;
        }
        for (long long round = 0; round < users; round++)
        {
            for (long long u = 0; u < users; u++)
            {
                calculated_values[u] = power(calculated_values[u], private_keys[u], n);
                new_values[(u+1)%users] = calculated_values[u];
            }
            for (long long u = 0; u < users; u++) calculated_values[u] = new_values[u];
        }
        cout << users << " users" << endl;
        cout << "Prime numeber:  n = " << n << endl;
        cout << "Primitive root: g = " << g << endl;
        for (long long u = 0; u < users; u++)
        {
            cout << "User " << char('A' + u) << " private key " << char('a' + u) << " = " << private_keys[u] << " and session key K = " << calculated_values[u] << endl;
        }
        check = true;
        for (long long u = 0; u < users - 1; u++)
        {
            if (calculated_values[u] != calculated_values[u+1]) check= false;
        }
        if (check) cout << "Session key correct" << endl << endl;
        else cout << "Session key incorrect" << endl << endl;
    }
}
