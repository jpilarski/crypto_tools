import hashlib
import time
import random

def hash(message):
    message_bytes = message.encode("utf-8")
    functions = ["md5", "sha1", "sha224", "sha256", "sha384", "sha512", "sha3_224", "sha3_256", "sha3_384", "sha3_512"]
    results = []
    for name in functions:
        start = time.time()
        hash_func = getattr(hashlib, name)()
        hash_func.update(message_bytes)
        hash_val = hash_func.hexdigest()
        run_time = time.time() - start
        results.append(hash_val)
        results.append(len(hash_val))
        results.append(run_time)
    return results

def B_print(B_display_names, B_sizes, B_times, B_lengths):
    print("Results")
    print()
    print("Time")
    print("\t", end="")
    for size in B_sizes:
        print(f"\t{size}", end="")
    print("\tbytes")
    print()
    for i in range(10):
        print(B_display_names[i], end="")
        for j in range(len(B_sizes)):
            print(f"\t{round(B_times[i][j], 3)}", end="")
        print()
    print()
    print("Length")
    print("\t", end="")
    for size in B_sizes:
        print(f"\t{size}", end="")
    print("\tbytes")
    print()
    for i in range(10):
        print(B_display_names[i], end="")
        for j in range(len(B_sizes)):
            print(f"\t{int(round(B_lengths[i][j], 0))}", end="")
        print()
    print()

if __name__ == "__main__":
    function_names = ["MD5", "SHA-1", "SHA-2-224", "SHA-2-256", "SHA-2-384", "SHA-2-512", "SHA-3-224", "SHA-3-256", "SHA-3-384", "SHA-3-512"]
    display_names = ["      MD5:", "    SHA-1:", "SHA-2-224:", "SHA-2-256:", "SHA-2-384:", "SHA-2-512:", "SHA-3-224:", "SHA-3-256:", "SHA-3-384:", "SHA-3-512:"]

    while True:
        print("Choose operating mode")
        print("A) Enter message")
        print("B) Test hash functions parameters")
        print("C) Test collision on 12, 20 and 50 bits")
        print("D) Test Strict Avalanche Criterion")
        dialog = input("Your choice: ")
        print()

        if dialog=="A":
            message = input("Enter message: ")
            results = hash(message)
            print()
            print(f"Hashes for message: {message}")
            print()
            for i in range(10):
                print(f"{display_names[i]} {results[i*3]}")
            print()

        elif dialog=="B":
            iter = 10
            sizes = [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000]
            lengths = [[0]*len(sizes) for _ in range(10)]
            times = [[0.0]*len(sizes) for _ in range(10)]
            for i in range(len(sizes)):
                size = sizes[i]
                for _ in range(iter):
                    message = ''.join(chr(random.randint(32, 125)) for _ in range(size))
                    results = hash(message)
                    for j in range(10):
                        lengths[j][i] += results[j*3+1]
                        times[j][i] += results[j*3+2]
            for i in range(len(sizes)):
                for j in range(10):
                    times[j][i] /= iter
                    lengths[j][i] /= iter
            B_print(display_names, sizes, times, lengths)

        elif dialog=="C":
            message = input("Enter message: ")
            print()
            results = hash(message)
            b_12 = [True] * 10
            b_20 = [True] * 10
            b_50 = [True] * 10
            original = []
            for i in range(10):
                binary = bytes.fromhex(results[i*3])
                original.append(''.join(f"{byte:08b}" for byte in binary))
            with open("words.txt", "r", encoding="utf-8") as file:
                for line in file:
                    current = []
                    results = hash(line.strip())
                    for i in range(10):
                        binary = bytes.fromhex(results[i*3])
                        current.append(''.join(f"{byte:08b}" for byte in binary))
                    for i in range(10):
                        if b_12[i] and original[i][:12] == current[i][:12]:
                            print(f"For message {message} word {line.strip()} was found, with which there is a collision in the first 12 bits in function {function_names[i]}")
                            b_12[i] = False
                        if b_20[i] and original[i][:20] == current[i][:20]:
                            print(f"For message {message} word {line.strip()} was found, with which there is a collision in the first 20 bits in function {function_names[i]}")
                            b_20[i] = False
                        if b_50[i] and original[i][:50] == current[i][:50]:
                            print(f"For message {message} word {line.strip()} was found, with which there is a collision in the first 50 bits in function {function_names[i]}")
                            b_50[i] = False
            print()


        elif dialog=="D":
            message = input("Enter message: ")
            print()
            index = random.randint(0, len(message)-1)
            char_code = ord(message[index])
            while True:
                bit_index = random.randint(0, 7)
                flipped_char_code = char_code ^ (1 << bit_index)
                if flipped_char_code > 32 and flipped_char_code < 127:
                    break
            new_message = message[:index]+chr(flipped_char_code)+message[index+1:]
            results = hash(message)
            new_results = hash(new_message)
            print(f"Original message: {message}")
            print(f" Changed message: {new_message}")
            print()
            for i in range(10):
                original = ''.join(f"{byte:08b}" for byte in bytes.fromhex(results[i*3]))
                changed = ''.join(f"{byte:08b}" for byte in bytes.fromhex(new_results[i*3]))
                counter = 0
                for a, b in zip(original, changed):
                    if a != b:
                        counter += 1
                print(f"Original {function_names[i]} hash: {results[i*3]}")
                print(f" Changed {function_names[i]} hash: {new_results[i*3]}")
                print(f"Changed {counter} out of {len(original)} bits ({round(counter*100/len(original), 0)}%)")
                print()
                
        else:
            exit()