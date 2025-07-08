#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

vector<int> primes[8];
vector<bool> bytes;
string dialog;
int sizeofprime, repeats, result;

int gcd(int a, int b)
{
    while (b != 0)
    {
        a = a % b;
        swap(a, b);
    }
    return a;
}

void generator(int sprime, vector<bool> &bytes, bool interface)
{
    long long int p, q, N, x, X;
    bytes.clear();
    p = primes[sprime][rand() % primes[sprime].size()];
    do q = primes[sprime][rand() % primes[sprime].size()];
    while (p == q);
    N = p * q;
    do x = rand() % 90 + 10;
    while (gcd(x, N) != 1);
    x = primes[2][rand() % primes[2].size()];
    if (interface)
    {
        cout << "p = " << p << endl;
        cout << "q = " << q << endl;
        cout << "N = " << N << endl;
        cout << "x = " << x << endl;
        cout << "Generating sequence..." << endl;
    }
    for (int i = 0; i < 20000; i++)
    {
        X = (x * x) % N;
        if (X & 1) bytes.push_back(true);
        else bytes.push_back(false);
        x = X;
    }
    if (interface)
    {
        cout << "Sequence generated" << endl << endl;
        for (int i = 0; i < 20000; i++)
        {
            if (bytes[i]) cout << char(219);
            else cout << " ";
            if (i % 100 == 99) cout << endl;
        }
        cout << endl;
    }
}

int tests(vector<bool> bytes, bool interface)
{
    int ones = 0, current = 0, maximum = 0, sum = 0;
    int sequences[2][7] = {};
    int poker[16] = {};
    double x;
    bool prev = false;
    bool results[4] = {false, true, false, false};
    for (int i = 0; i < bytes.size(); i++)
    {
        if (bytes[i]) ones++;
        if (prev)
        {
            if (bytes[i]) current++;
            else
            {
                maximum = max(current, maximum);
                if (current < 6) sequences[1][current]++;
                else sequences[1][6]++;
                current = 1;
            }
        }
        else
        {
            if (!bytes[i]) current++;
            else
            {
                maximum = max(current, maximum);
                if (current < 6) sequences[0][current]++;
                else sequences[0][6]++;
                current = 1;
            }
        }
        prev = bytes[i];
        if (i % 4 == 0) poker[bytes[i] * 8 + bytes[i + 1] * 4 + bytes[i + 2] * 2 + bytes[i + 3]]++;
    }
    maximum = max(current, maximum);
    if (prev)
    {
        if (current < 6) sequences[1][current]++;
        else sequences[1][6]++;
    }
    else
    {
        if (current < 6) sequences[0][current]++;
        else sequences[0][6]++;
    }
    for (int i = 0; i < 16; i++) sum += poker[i] * poker[i];
    sum = sum * 16;
    x = double(sum) / 5000.0 - 5000.0;
    if (9725 < ones && ones < 10275) results[0] = true;
    if (sequences[0][1] < 2315 || 2685 < sequences[0][1]) results[1] = false;
    if (sequences[1][1] < 2315 || 2685 < sequences[1][1]) results[1] = false;
    if (sequences[0][2] < 1114 || 1386 < sequences[0][2]) results[1] = false;
    if (sequences[1][2] < 1114 || 1386 < sequences[1][2]) results[1] = false;
    if (sequences[0][3] < 527 || 723 < sequences[0][3]) results[1] = false;
    if (sequences[1][3] < 527 || 723 < sequences[1][3]) results[1] = false;
    if (sequences[0][4] < 240 || 384 < sequences[0][4]) results[1] = false;
    if (sequences[1][4] < 240 || 384 < sequences[1][4]) results[1] = false;
    if (sequences[0][5] < 103 || 209 < sequences[0][5]) results[1] = false;
    if (sequences[1][5] < 103 || 209 < sequences[1][5]) results[1] = false;
    if (sequences[0][6] < 103 || 209 < sequences[0][6]) results[1] = false;
    if (sequences[1][6] < 103 || 209 < sequences[1][6]) results[1] = false;
    if (maximum < 26) results[2] = true;
    if (2.16 < x && x < 46.17) results[3] = true;
    if (interface)
    {
        cout << "Monobit test" << endl;
        cout << "For sequence of 20,000 bits expected between 9725 and 10275 of ones" << endl;
        cout << "Number of ones: " << ones << endl;
        if (results[0]) cout << "Test passed" << endl << endl;
        else cout << "Test failed" << endl << endl;

        cout << "Runs test" << endl;
        cout << "In a sequence of 20,000 bits there should be:" << endl;
        cout << "Between 2315 and 2685 runs of lenght 1" << endl;
        cout << "Between 1114 and 1386 runs of lenght 2" << endl;
        cout << "Between 527 and 723 runs of lenght 3" << endl;
        cout << "Between 240 and 384 runs of lenght 4" << endl;
        cout << "Between 103 and 209 runs of lenght 5" << endl;
        cout << "Between 103 and 209 runs of lenght 6" << endl;
        cout << "Results:" << endl;
        cout << "\"0\" runs with lenght 1: " << sequences[0][1] << "\t\"1\" runs with length 1: " << sequences[1][1] << endl;
        cout << "\"0\" runs with lenght 2: " << sequences[0][2] << "\t\"1\" runs with length 2: " << sequences[1][2] << endl;
        cout << "\"0\" runs with lenght 3: " << sequences[0][3] << "\t\"1\" runs with length 3: " << sequences[1][3] << endl;
        cout << "\"0\" runs with lenght 4: " << sequences[0][4] << "\t\"1\" runs with length 4: " << sequences[1][4] << endl;
        cout << "\"0\" runs with lenght 5: " << sequences[0][5] << "\t\"1\" runs with length 5: " << sequences[1][5] << endl;
        cout << "\"0\" runs with lenght 6 and more: " << sequences[0][6] << "\t\"1\" runs with length 6 and more: " << sequences[1][6] << endl;
        if (results[1]) cout << "Test passed" << endl << endl;
        else cout << "Test failed" << endl  << endl;

        cout << "Long runs test" << endl;
        cout << "In a sequence of 20,000 bits longest run should be shorter than 26" << endl;
        cout << "Longest run: " << maximum << endl;
        if (results[2]) cout << "Test passed" << endl << endl;
        else cout << "Test failed" << endl << endl;

        cout << "Poker test" << endl;
        cout << "After dividing the 20,000-bit sequence into 5,000 4-bit groups, the value x, based on the frequency of each of the 16 possible 4-bit combinations, should fall between 2.16 and 46.17" << endl;
        cout << "x = " << x << endl;
        if (results[3]) cout << "Test passed" << endl << endl;
        else cout << "Test failed" << endl << endl;

        if (results[0] && results[1] && results[2] && results[3]) cout << "All tests passed" << endl << endl;
        else if(results[0] || results[1] || results[2] || results[3]) cout << "Some tests failed" << endl << endl;
        else cout << "All tests failed" << endl << endl;
    }
    return results[0] * 8 + results[1] * 4 + results[2] * 2 + results[3];
}

int main()
{
    srand(time(0));
    cout << "Generating prime numbers (about 5 seconds)..." << endl;
    for (int i = 2; i < 10000000; i++)
    {
        bool ok = true;
        for (int j = 2; j * j <= i && ok; j++)
            if (i % j == 0) ok = false;
        if (ok && i % 4 == 3) primes[int(log10(i)) + 1].push_back(i);
    }

    while (1)
    {
        cout << "Choose operating mode" << endl;
        cout << "A) Generate 20,000 bits" << endl;
        cout << "B) Test the generator" << endl;
        cout << "Your choice: ";
        cin >> dialog;
        cout << endl;
        if (dialog == "A")
        {
            cout << "Enter the length of the prime numbers (1 to 7): ";
            cin >> dialog;
            cout << endl;
            if (dialog == "1") sizeofprime = 1;
            else if (dialog == "2") sizeofprime = 2;
            else if (dialog == "3") sizeofprime = 3;
            else if (dialog == "4") sizeofprime = 4;
            else if (dialog == "5") sizeofprime = 5;
            else if (dialog == "6") sizeofprime = 6;
            else if (dialog == "7") sizeofprime = 7;
            else return 0;
            generator(sizeofprime, bytes, true);
            cout << "Running test for this sequence" << endl << endl;
            result = tests(bytes, true);
        }
        else if (dialog == "B")
        {
            cout << "Generating and testing sequences..." << endl;
            int wyniki[7][5] = {};
            for (sizeofprime = 1; sizeofprime <= 7; sizeofprime++)
            {
                for (int repeat = 0; repeat < 100; repeat++)
                {
                    generator(sizeofprime, bytes, false);
                    result = tests(bytes, false);
                    if ((result & (1 << 0)) != 0) wyniki[sizeofprime - 1][0]++;
                    if ((result & (1 << 1)) != 0) wyniki[sizeofprime - 1][1]++;
                    if ((result & (1 << 2)) != 0) wyniki[sizeofprime - 1][2]++;
                    if ((result & (1 << 3)) != 0) wyniki[sizeofprime - 1][3]++;
                    if (result == 15) wyniki[sizeofprime - 1][4]++;
                }
            }
            cout << "Success rate after 100 iterations" << endl << endl;
            cout << "Length\tTest 1\tTest 2\tTest 3\tTest 4\tAll tests" << endl;
            for (int i = 1; i <= 7; i++)
            {
                cout << i;
                for (int j = 0; j < 5; j++) cout << "\t" << wyniki[i - 1][j];
                cout << endl;
            }
            cout << endl;
        }
        else return 0;
    }
}
