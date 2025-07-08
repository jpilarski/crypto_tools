# 🧩 Secret sharing

## ℹ️ O programie

#### [🇬🇧 English version](#ℹ️-about-the-program)

### ❔ Czym jest podział sekretu

Sekretem są dowolne poufne dane, na przykład hasło czy klucz prywatny. Podział sekretu polega na podzieleniu danych. Pojedynczy udział w sekrecie nie pozwala odszyfrować danych, a do ich odtworzenia potrzebnych jest, w zależności od protokołu wszystkie `n` udziałów, lub tylko `t` z `n` udziałów.

#### Metoda trywialna:

1. Niech `k` oznacza rozmiar przestrzeni liczbowej, a `s` sekret, będący liczbą całkowitą z przedziału od `0` do `k-1`.
2. Wyznacz losowo `n-1` wartości, należących do przedziału od `<0, k-1>`. Są to kolejne udziały.
3. Wyznacz ostatni udział ze wzoru <code>s<sub>n</sub> = (s-s<sub>1</sub>-s<sub>2</sub>-...-s<sub>n-1</sub>) mod k</code>.
4. Aby odtworzyć sekret, zsumuj wszystkie `n` udziałów, a na sumie wykonaj operację `mod k`.

#### Metoda Shamira (`t` z `n` udziałów)

1. Niech `s` oznacza sekret. Wybierz liczbę pierwszą `p` większą zarówno od `s` jak i od `k`.
2. Wybierz losowo `t-1` liczb <code>a<sub>1</sub>, a<sub>2</sub>... a<sub>t-1</sub></code>. 
3. Dla każdego `i = 1, 2, ..., n` wyznacz <code>s<sub>i</sub> = (s + a<sub>1</sub>i + a<sub>2</sub>i<sup>2</sup> + ... + a<sub>t-1</sub>i<sup>t-1</sup>) mod p</code>.
4. Udziałami są pary liczb <code>(i, s<sub>i</sub>)</code>.
5. Aby odtworzyć sekret, po zebraniu `t` udziałów, należy rozwiązać układ równań lub wykorzystać wielomian interpolacyjny Langrage'a.

### 💻 Uruchomienie i działanie programu

Kompilacja programu:

|         | Metoda trywialna                                      | Metoda Shamira                                     |
| ------- | ----------------------------------------------------- | -------------------------------------------------- |
| Windows | `> g++ trivial.cpp -o trivial.exe`<br>`> trivial.exe` | `> g++ shamir.cpp -o shamir.exe`<br>`> shamir.exe` |
| Linux   | `> g++ trivial.cpp -o trivial`<br>`> ./trivial`       | `> g++ shamir.cpp -o shamir`<br>`> ./shamir`       |

Program z metodą trywialną wymaga podania `n`, `k` i `s`. Następnie wyznacza wszystkie udziały oraz oblicza na nowo sekret i sprawdza jego poprawność.

Program z metodą Shamira wymaga podania `n` w odpowiednim zakresie, następnie `t`, oraz `s`. Wypisuje wszystkie `n` udziałów, wybiera losowo `t` z nich i oblicza na ich podstawie sekret oraz sprawdza jego poprawność.

Oba programy są wyposażone w interfejs tekstowy.

## ℹ️ About the program

#### [🇵🇱 Wersja polska](#ℹ️-o-programie)

### ❔ What is secret sharing

A secret is any confidential data — like a password or a private key. Secret sharing is the process of splitting this data into multiple pieces. A single share does not reveal the secret; depending on the scheme, either all `n` shares or only `t` out of `n` are required to reconstruct it.

#### Trivial method:

1. Let `k` be the size of the number space, and `s` the secret, a number from `0` to `k-1`.
2. Randomly generate `n-1` numbers from the range `<0, k-1>`. These are the first `n-1` shares.
3. Compute the last share using: <code>s<sub>n</sub> = (s − s<sub>1</sub> − s<sub>2</sub> − ... − s<sub>n−1</sub>) mod k</code>
4. To recover the secret, sum all `n` shares and apply `mod k`.

#### Shamir's method (`t` of `n` shares)

1. Let `s` be the secret. Choose a prime `p` such that `p > s` and `p > n`.
2. Randomly choose <code>t−1</code> numbers <code>a<sub>1</sub>, a<sub>2</sub>, ..., a<sub>t−1</sub></code>
3. For each `i = 1, 2, ..., n`, compute: <code>s<sub>i</sub> = (s + a<sub>1</sub>i + a<sub>2</sub>i<sup>2</sup> + ... + a<sub>t−1</sub>i<sup>t−1</sup>) mod p</code>
4. Each share is a pair: <code>(i, s<sub>i</sub>)</code>
5. To recover the secret, use any `t` shares and perform Lagrange interpolation.

### 💻 Running the program

To compile the program:

|         | Trivial method                                        | Shamir's method                                    |
| ------- | ----------------------------------------------------- | -------------------------------------------------- |
| Windows | `> g++ trivial.cpp -o trivial.exe`<br>`> trivial.exe` | `> g++ shamir.cpp -o shamir.exe`<br>`> shamir.exe` |
| Linux   | `> g++ trivial.cpp -o trivial`<br>`> ./trivial`       | `> g++ shamir.cpp -o shamir`<br>`> ./shamir`       |

Trivial method: the program takes `n`, `k`, and `s` as input, generates all shares, then recomputes the secret and verifies it.

Shamir's method: the program asks for `n`, then `t`, and finally `s`. It prints all `n` shares, randomly selects `t` of them, reconstructs the secret, and verifies correctness.

Both have text interface.