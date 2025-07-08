import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

def validate_arguments():
    if len(sys.argv) != 3:
        print("Use: python lsb_cipher.py \"name.png\" \"text.txt\"")
        exit(1)
    arg_image = sys.argv[1]
    if not os.path.exists(arg_image):
        print(f"File {arg_image} does not exist")
        exit(1)
    if not arg_image.lower().endswith('.png'):
        print("File must have a .png extension")
        exit(1)
    arg_name = arg_image.split('.')[0]
    try:
        arg_image = Image.open(arg_image).convert('RGBA')
    except:
        print("Error loading png file")
        exit(1)
    arg_text = sys.argv[2]
    try:
        with open(arg_text, "r", encoding="utf-8") as file:
            arg_text = file.read()
    except:
        print(f"Problems with file {arg_text}")
        exit(1)
    arg_width, arg_height = arg_image.size
    arg_image = [[[*arg_image.getpixel((x, y))] for x in range(arg_width)] for y in range(arg_height)]
    return [arg_name, arg_height, arg_width, arg_image, arg_text]

if __name__ == "__main__":
    data = validate_arguments()
    name = data[0]
    height = data[1]
    width = data[2]
    image = data[3]
    text = data[4]
    iter = 0
    for i in range(0, width*height, 2):
        x1 = i % width
        y1 = i // width
        x2 = (i+1) % width
        y2 = (i+1) // width
        if y2 < height:
            cr = ord(text[iter])
            bin = [int(bit) for bit in format(cr, '08b')]
            for b in range(0, 4):
                if image[y1][x1][b] % 2 == 0 and bin[b] == 1:
                    image[y1][x1][b] += 1
                if image[y1][x1][b] % 2 == 1 and bin[b] == 0:
                    image[y1][x1][b] -= 1
                if image[y2][x2][b] % 2 == 0 and bin[b+4] == 1:
                    image[y2][x2][b] += 1
                if image[y2][x2][b] % 2 == 1 and bin[b+4] == 0:
                    image[y2][x2][b] -= 1
        iter += 1
        if iter >= len(text):
            break
    plt.imsave(f"{name}_ciphered.png", np.array(image, dtype=np.uint8))
