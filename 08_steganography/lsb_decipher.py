import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

def validate_arguments():
    if len(sys.argv) != 2:
        print("Use: python lsb_decipher.py \"name.png\" ")
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
    arg_width, arg_height = arg_image.size
    arg_image = [[[*arg_image.getpixel((x, y))] for x in range(arg_width)] for y in range(arg_height)]
    return [arg_name, arg_height, arg_width, arg_image]

if __name__ == "__main__":
    data = validate_arguments()
    name = data[0]
    height = data[1]
    width = data[2]
    image = data[3]
    text = []
    for i in range(0, width*height, 2):
        x1 = i % width
        y1 = i // width
        x2 = (i+1) % width
        y2 = (i+1) // width
        if y2 < height:
            bin = []
            for b in range(0, 4):
                bin.append(image[y1][x1][b]%2)
            for b in range(0, 4):
                bin.append(image[y2][x2][b]%2)
            bin_str = ''.join(str(bit) for bit in bin)
            cr = int(bin_str, 2)
            cr = chr(cr)
            text.append(cr)
    text = ''.join(text)
    print(text)