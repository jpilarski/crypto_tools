#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

vector<long long> primes;
string dialog;
long long D, E, N;

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        a = a % b;
        swap(a, b);
    }
    return a;
}

bool prime(long long a)
{
    for (long long i = 2; i * i <= a; i++) if (a % i == 0) return false;
    return true;
}

void keys(long long &d, long long &e, long long &n)
{
    long long p, q, phi, iter = 2;
    bool run = true;
    p = primes[rand() % primes.size()];
    do q = primes[rand() % primes.size()];
    while (abs(p - q) < 2000);
    n = p * q;
    phi = (p - 1) * (q - 1);
    while (run)
    {
        if (prime(iter) && gcd(iter, phi) == 1)
        {
            e = iter;
            run = false;
        }
        iter++;
    }
    iter = 0;
    run = true;
    while (run)
    {
        if ((iter * phi + 1) % e == 0)
        {
            d = (iter * phi + 1) / e;
            run = false;
        }
        iter++;
    }
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

void cipher(string message, long long d, long long e, long long n)
{
    vector<long long> ciphered_message;
    string output = "";
    cout << "Message to encrypt:" << endl;
    cout << message << endl << endl;
    cout << "Public key:" << endl;
    cout << "E = " << e << endl;
    cout << "N = " << n << endl << endl;
    cout << "Encrypted message:" << endl;
    for (long long i = 0; i < message.size(); i++)
    {
        ciphered_message.push_back(power(int(message[i]), e, n));
        cout << ciphered_message[i] << " ";
    }
    cout << endl << endl;
    cout << "Private key:" << endl;
    cout << "D = " << d << endl;
    cout << "N = " << n << endl << endl;
    cout << "Decrypted message:" << endl;
    for (long long i = 0; i < ciphered_message.size(); i++) output = output + char(power(ciphered_message[i], d, n));
    cout << output << endl << endl;
    if (message == output) cout << "Decryption successful" << endl << endl;
    else cout << "Decryption failed" << endl << endl;
}

int main()
{
    srand(time(0));
    for (int i = 1000; i < 10000; i++) if (prime(i)) primes.push_back(i);
    while (1)
    {
        keys(D, E, N);
        cout << "Choose operating mode:" << endl;
        cout << "A) Enter message to encrypt" << endl;
        cout << "B) Random message" << endl;
        cout << "Your choice: ";
        cin >> dialog;
        cout << endl;
        if (dialog == "A")
        {
            cout << "Enter message (only letters and spaces): ";
            cin.ignore();
            getline(cin, dialog);
            cout << endl;
            for (int i = 0; i < dialog.size(); i++)
            {
                if (dialog[i] < int(' ') ||
                    (dialog[i] > int(' ') && dialog[i] < int('A')) ||
                    (dialog[i] > int('Z') && dialog[i] < int('a')) ||
                    dialog[i] > int('z'))
                    return 0;
            }
            cipher(dialog, D, E, N);
        }
        else if (dialog == "B")
        {
            dialog = "";
            for (int i = 0; i < 50; i++)
            {
                int r = rand() % 53;
                if (r == 0) dialog = dialog + ' ';
                else if (r <= 26) dialog = dialog + char(r + 'A' - 1);
                else dialog = dialog + char(r + 'a' - 27);
            }
            cipher(dialog, D, E, N);
        }
        else return 0;
    }
}
