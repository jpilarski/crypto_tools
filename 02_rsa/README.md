# 🔐 RSA asymmetric cipher

## ℹ️ O programie

#### [🇬🇧 English version](#ℹ️-about-the-program)

### ❔ Jak działa RSA

RSA jest szyfrem asymetrycznym. Jego działanie opiera się na istnieniu klucza publicznego i prywatnego. Klucz publiczny jest jawny i każdy może nim zaszyfrować wiadomość, natomiast tylko właściciel klucza prywatnego może ją odszyfrować. RSA można też wykorzystać do podpisów cyfrowych: właściciel klucza prywatnego szyfruje nim dokument, a każdy posiadający klucz publiczny jest w stanie zweryfikować jego tożsamość. Algorytm RSA działa następująco:

1. Wybierz 2 duże liczby pierwsze `p` i `q`.
2. Wyznacz liczbę `N` jako iloczyn liczb `p` i `q`.
3. Wyznacz liczbę `φ = (p-1)*(q-1)`.
4. Wybierz losową liczbę pierwszą `e` względnie pierwszą z `φ`.
5. Wyznacz losową liczbę `d`, która spełnia założenie `e*d ≡ 1 mod φ`.

Kluczem prywatnym jest para `d` i `n`, a kluczem publicznym para `e` i `n`.

Algorytm szyfrowania:

1. Podziel tekst wiadomości na bloki liczbowe, których wartość jest mniejsza od `n`.
2. Kolejne elementy szyfrogramu wyznacz ze wzoru <code>cᵢ = mᵢ<sup>e</sup> mod n</code>.

Algorytm deszyfrowania:

1. Kolejne elementy tekstu jawnego wyznacz ze wzoru <code>mᵢ = cᵢ<sup>d</sup> mod n</code>.
2. Zamień obliczone wartości na tekst.

### 💻 Uruchomienie i działanie programu

Kompilacja programu:

Windows:

* `> g++ RSA.cpp -o RSA.exe`
* `> RSA.exe`

Linux:

* `> g++ RSA.cpp -o RSA`
* `> ./RSA`

Program po uruchomieniu pozwala wpisać własną wiadomość lub sam generuje ciąg znaków. Następnie podaje obliczony klub publiczny, kolejno obliczone wartości `cᵢ`, klucz prywatny, odszyfrowaną wiadomość oraz informację, czy odszyfrowany tekst pokrywa się z początkowym.

## ℹ️ About the program

#### [🇵🇱 Wersja polska](#ℹ️-o-programie)

### ❔ How RSA works

RSA is an asymmetric cipher. Its operation is based on the existence of a public key and a private key. Anyone can use public key to encrypt a message, while only the owner of the private key can decrypt it. RSA can also be used for digital signatures: the owner of the private key encrypts the document with it, and anyone with the public key can verify its authenticity. The RSA algorithm works as follows:

1. Choose two large prime numbers `p` and `q`.
2. Calculate `N` as the product of `p` and `q`.
3. Calculate `φ = (p-1)*(q-1)`.
4. Choose a random prime number `e` that is relatively prime with `φ`.
5. Calculate a number `d` such that `e*d ≡ 1 mod φ`.

The private key is the pair `d` and `n`, and the public key is the pair `e` and `n`.

Encryption algorithm:

1. Split the plaintext into numeric blocks smaller than `n`.
2. Calculate each ciphertext element using the formula <code>cᵢ = mᵢ<sup>e</sup> mod n</code>.

Decryption algorithm:

1. Calculate each plaintext element using the formula <code>mᵢ = cᵢ<sup>d</sup> mod n</code>.
2. Convert the computed values back to text.

### 💻 Running the program

To compile the program:

Windows:

* `> g++ RSA.cpp -o RSA.exe`
* `> RSA.exe`

Linux:

* `> g++ RSA.cpp -o RSA`
* `> ./RSA`

After running, the program allows you to enter your own message or generates a random string. Then it outputs the calculated public key, the ciphertext values `cᵢ`, the private key, the decrypted message, and whether the decrypted text matches the original.
