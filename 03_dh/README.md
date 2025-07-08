# 🤝🔑 Diffie–Hellman algorithm

## ℹ️ O programie

#### [🇬🇧 English version](#ℹ️-about-the-program)

### ❔ Jak działa algorytm DH

Algorytm Diffiego-Hellmana służy nie do szyfrowania, a do dystrybucji kluczy. Można go zaimplementować dla większej niż 2 liczby osób. Kroki algorytmu:

1. Uczestników należy ustawić w pierścieniu.
2. Wybierz 2 jawne liczby: liczbę pierwszą `n` oraz liczbę `g`, która jest pierwiastkiem pierwotnym modulo `n`.
3. Każdy z uczestników wybiera własną tajną liczbę `x`.
4. Każdy oblicza swoje <code>X = g<sup>x</sup> mod n</code>.
5. Każdy przesyła obliczone `X` następnej osobie w pierścieniu.
6. Każdy oblicza nowe <code>X = X<sub>otrzymane</sub><sup>x</sup> mod n</code>.
7. Kroki 5-6 powtarza się tyle razy, ile jest uczestników - 1.
8. Ostatnia obliczona wartość jest kluczem sesji, identycznym dla wszystkich uczestników.

### 💻 Uruchomienie i działanie programu

Kompilacja programu:

Windows:

* `> g++ DH.cpp -o DH.exe`
* `> DH.exe`

Linux:

* `> g++ DH.cpp -o DH`
* `> ./DH`

Program jest wyposażony w interfejs tekstowy. Po uruchomieniu podaje się liczbę osób. Program wypisuje wartości `n` oraz `g`, a następnie dla każdego uczestnika, podaje jego własne `x` oraz obliczony klucz sesji. Na końcu sprawdza, czy wszystkie klucze są identyczne.

## ℹ️ About the program

#### [🇵🇱 Wersja polska](#ℹ️-o-programie)

### ❔ How the DH algorithm Works

The Diffie-Hellman algorithm is not used for encryption, but for key distribution. It can be implemented for more than two participants. The steps of the algorithm:

1. Arrange the participants in a ring.
2. Choose two public numbers: a prime number `n` and a number `g`, which is a primitive root modulo n.
3. Each participant chooses their own secret number `x`.
4. Each computes <code>X = g<sup>x</sup> mod n</code>.
5. Each sends their computed `X` to the next person in the ring.
6. Each computes a new <code>X = X<sub>received</sub><sup>x</sup> mod n</code>.
7. Repeat steps 5–6 a total of number of participants - 1 times.
8. The final computed value is the session key, identical for all participants.

### 💻 Running the program

To compile the program:

Windows:

* `> g++ DH.cpp -o DH.exe`
* `> DH.exe`

Linux:

* `> g++ DH.cpp -o DH`
* `> ./DH`

The program uses a text-based interface. After starting, you enter the number of participants. The program then displays the values of `n` and `g`, and for each participant, it shows their secret number x and the computed session key. Finally, it checks whether all session keys are identical.
