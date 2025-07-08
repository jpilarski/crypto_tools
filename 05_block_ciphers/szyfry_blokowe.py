import os
import time
import random
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

def xor(a, b):
    return bytes(x ^ y for x, y in zip(a, b))

if __name__ == "__main__":
    print(f"Algorithms working time:")
    sizes = [1024*1024, 10*1024*1024, 50*1024*1024]
    cypher_modes = ["ECB", "CBC", "CTR"]
    for mode in cypher_modes:
        print(f"\tMode {mode}:")
        for size in sizes:
            print(f"\t\tSize in bytes = {size}:")
            iterations = 1
            encryptions = 0.0
            decryptions = 0.0
            for _ in range(iterations):
                key = os.urandom(32)
                iv_nonce = os.urandom(16)
                data = os.urandom(size)
                if mode == "ECB":
                    cipher = Cipher(algorithms.AES(key), modes.ECB())
                elif mode == "CBC":
                    cipher = Cipher(algorithms.AES(key), modes.CBC(iv_nonce))
                elif mode == "CTR":
                    cipher = Cipher(algorithms.AES(key), modes.CTR(iv_nonce))
                encryptor = cipher.encryptor()
                start = time.time()
                encrypted = encryptor.update(data) + encryptor.finalize()
                stop = time.time()
                encryptions = encryptions + stop - start
                decryptor = cipher.decryptor()
                start = time.time()
                decrypted = decryptor.update(encrypted) + decryptor.finalize()
                stop = time.time()
                decryptions = decryptions + stop - start
            print(f"\t\t\tEncryption = {round(encryptions/100, 5)}s")
            print(f"\t\t\tDecryption = {round(decryptions/100, 5)}s")
    print()
    print(f"Error propagation:")
    message = input("Enter message to encrypt: ")
    message = message * 16
    byte_message = message.encode("utf-8")
    for mode in cypher_modes:
        print(f"\tMode {mode}:")
        print(f"\t\tMessage:           {message}")
        key = os.urandom(32)
        iv_nonce = os.urandom(16)
        if mode == "ECB":
            cipher = Cipher(algorithms.AES(key), modes.ECB())
        elif mode == "CBC":
            cipher = Cipher(algorithms.AES(key), modes.CBC(iv_nonce))
        elif mode == "CTR":
            cipher = Cipher(algorithms.AES(key), modes.CTR(iv_nonce))
        encryptor = cipher.encryptor()
        encrypted = encryptor.update(byte_message) + encryptor.finalize()
        print(f"\t\tChanging 1 bit in encrypted message")
        encrypted = bytearray(encrypted)
        encrypted[random.randint(0, len(encrypted)-1)] ^= 1 << random.randint(0,7)
        encrypted = bytes(encrypted)
        decryptor = cipher.decryptor()
        decrypted = decryptor.update(encrypted) + decryptor.finalize()
        decoded = decrypted.decode("utf-8", errors="replace")
        print(f"\t\tDecrypted message: {decoded}")
    print()
    print(f"CBC implementation:")
    message = input("Enter message to encrypt: ")
    message = message * 16
    byte_message = message.encode("utf-8")
    key = os.urandom(32)
    iv = os.urandom(16)
    cipher = Cipher(algorithms.AES(key), modes.ECB())
    encryptor = cipher.encryptor()
    decryptor = cipher.decryptor()
    blocks = [byte_message[i:i+16] for i in range(0, len(byte_message), 16)]
    cbc = []
    prev = iv
    for block in blocks:
        xored = xor(block, prev)
        encrypted = encryptor.update(xored)
        cbc.append(encrypted)
        prev = encrypted
    ciphered = b''.join(cbc)
    blocks = [ciphered[i:i+16] for i in range(0, len(ciphered), 16)]
    cbc = []
    prev = iv
    for block in blocks:
        decrypted = decryptor.update(block)
        xored = xor(decrypted, prev)
        cbc.append(xored)
        prev = block
    decoded_message = b''.join(cbc)
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv))
    encryptor = cipher.encryptor()
    encrypted = encryptor.update(byte_message) + encryptor.finalize()
    print(f"\tOriginal message:  {message}")
    print(f"\tEncrypted message:               {ciphered.hex()}")
    print(f"\tEncryption by build-in function: {encrypted.hex()}")
    print(f"\tDecrypted message: {decoded_message.decode("utf-8", errors="replace")}")
