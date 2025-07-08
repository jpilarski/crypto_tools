# 🧱 Block ciphers

## ℹ️ O programie

#### [🇬🇧 English version](#ℹ️-about-the-program)

### ❔ Czym są szyfry blokowe

Szyfry blokowe to algorytmy szyfrujące dane w blokach o stałej długości (np. 128 bitów), przekształcając je za pomocą klucza. Stosowane są m.in. w szyfrowaniu plików, komunikacji sieciowej czy protokołach TLS.

### ➡️ Przykłady szyfrów oraz trybów pracy

Szyfry:

* **AES** (najpopularniejszy)
* **DES** (przestarzały)

Tryby pracy:

* **ECB** – każdy blok jest szyfrowany osobno (niebezpieczny)
* **CBC** – każdy blok zależy od poprzedniego
* **CFB**/**OFB** – tryby strumieniowe
* **CTR** – można używać równolegle

### 💻 Uruchomienie i działanie programu

Windows:

* `> python block_ciphers.py`

Linux:

* `> python3 block_ciphers.py`

Program po uruchomieniu wykonuje w kolejności następujące zadania:

1. Porównuje czasy szyfrowania i deszyfrowania dla szyfru AES w trybach ECB, CBC i CTR dla trzech rozmiarów wiadomości
2. Bada, jak zmienia się propagacja błędów w zależności od trybu
3. Szyfruje metodą CBC zaimplementowaną ręcznie na bazie ECB i sprawdza poprawność szyfrowania

### ❗ Propagacja błędów

* W trybie ECB uszkodzony zostaje cały blok, w którym doszło do zamianu bitu
* W trybie CBC, tak jak w ECB uszkodzony jest blok w całości, ponadto zmieniony jest jeden bit w kolejnym bloku, odpowiadający pozycji pierwotnie uszkodzonego bitu
* W trybie CTR uszkodzony zostaje tylko zmieniony bit

## ℹ️ About the program

#### [🇵🇱 Wersja polska](#ℹ️-o-programie)

### ❔ What are block ciphers

Block ciphers are algorithms that encrypt data in fixed-size blocks (e.g., 128 bits) using a key. They are used in file encryption, network communication, and protocols like TLS.

### ➡️ Examples of ciphers and modes of operation

Ciphers:

* **AES** (mst popular)
* **DES** (obsolete)

Modes of operation:

* **ECB** – each block is encrypted separately (insecure)
* **CBC** – each block depends on the previous one
* **CFB**/**OFB** – stream-like modes
* **CTR** – supports parallel encryption

### 💻 Running the program

Windows:

* `> python block_ciphers.py`

Linux:

* `> python3 block_ciphers.py`

After launch, the program performs the following tasks in order:

1. Compares encryption and decryption times for AES in ECB, CBC, and CTR modes for three message sizes
2. Analyses how error propagation varies by mode
3. Encrypts using CBC mode manually implemented on top of ECB and verifies correctness

### ❗ Error propagation

* In ECB mode, the whole block with the flipped bit gets corrupted
* In CBC mode, the corrupted block is fully damaged, and one bit in the next block (same position) is also affected
* In CTR mode, only the flipped bit is corrupted
