# 🔍 Steganography

## ℹ️ O programie

#### [🇬🇧 English version](#ℹ️-about-the-program)

### ❔ Czym jest steganografia

Steganografia polega na osadzeniu jednej informacji w innej. Znakiem wodnym jest osadzenie w na przykład pliku graficznym wiadomości tekstowej. Można to zrobić za pomocą algorytmu najmniej znaczącego bitu. Każdy bajt kodowanej informacji można zakodować na dwóch pikselach obrazka, mającego przestrzeń kolorów RGBA.

### 💻 Uruchomienie i działanie programu

|         | Program szyfrujący                              | Program deszyfrujący                   |
| ------- | ----------------------------------------------- | -------------------------------------- |
| Windows | `> python lsb_cipher.py "name.png" "text.txt"`  | `> python lsb_decipher.py "name.png"`  |
| Linux   | `> python3 lsb_cipher.py "name.png" "text.txt"` | `> python3 lsb_decipher.py "name.png"` |

`name.png` jest obrazkiem, w którym osadzamy lub z którego odczytujemy znak wodny, a `text.txt` jest tekstem, który osadzamy w obrazku.

Program szyfrujący odczytuje oba pliki i zamienia najmniej znaczące bity w czterech bajtach kodujących każdy piksel. Robi to do czasu wyczerpania tekstu lub miejsca na obrazku.

Program deszyfrujący odczytuje parami po dwa piksele i wypisuje na konsolę znak ASCII odpowiadający kombinacji najmniej znaczących bitów.

### [📷 Przykład działania](#example)

## ℹ️ About the program

#### [🇵🇱 Wersja polska](#ℹ️-o-programie)

### ❔ What is steganography

Steganography involves embedding one piece of information within another. A watermark, for example, embeds a text message into an image file. This can be done using the Least Significant Bit (LSB) algorithm. Each byte of the message can be encoded using two pixels in an image with RGBA color space.

### 💻 Running the program

|         | Encryption Program                              | Decryption Program                     |
| ------- | ----------------------------------------------- | -------------------------------------- |
| Windows | `> python lsb_cipher.py "name.png" "text.txt"`  | `> python lsb_decipher.py "name.png"`  |
| Linux   | `> python3 lsb_cipher.py "name.png" "text.txt"` | `> python3 lsb_decipher.py "name.png"` |

`name.png` is the image used to embed or extract the watermark, and `text.txt` is the file containing the text to embed.

The encryption program reads both files and modifies the least significant bits in four bytes representing each pixel. This continues until the text is fully embedded or the image space runs out.

The decryption program reads the pixels in pairs and prints the ASCII characters based on the combination of least significant bits.

<a id="example"></a>

### 📷 Example output

<table align="center" style="border-collapse: separate; border-spacing: 20px 10px; margin: auto;">
  <tr>
    <td><img src="picture.png" alt="p1" style="display: block; margin: auto; width: 300px;"/></td>
    <td><img src="picture_ciphered.png" alt="p2" style="display: block; margin: auto; width: 300px;"/></td>
  </tr>
</table>