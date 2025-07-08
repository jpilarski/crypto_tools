import os
import sys
import random
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

shares_matrix = [[0,0,1,1, 1,1,0,0], [0,1,0,1, 1,0,1,0], [0,1,1,0, 1,0,0,1], [1,0,0,1, 0,1,1,0], [1,0,1,0, 0,1,0,1], [1,1,0,0, 0,0,1,1]]

def validate_arguments():
    if len(sys.argv) != 2:
        print("Use: python vis_crypto.py \"name.png\"")
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
        arg_image = Image.open(arg_image).convert('1')
    except:
        print("Error loading png file")
        exit(1)
    arg_width, arg_height = arg_image.size
    arg_image = [[0 if arg_image.getpixel((x, y)) == 0 else 1 for x in range(arg_width)] for y in range(arg_height)]
    return [arg_name, arg_height, arg_width, arg_image]

if __name__ == "__main__":
    data = validate_arguments()
    name = data[0]
    height = data[1]
    width = data[2]
    original_matrix = data[3]
    matrix_1 = [[0] * width*2 for _ in range(height*2)]
    matrix_2 = [[0] * width*2 for _ in range(height*2)]
    final_matrix = [[0] * width*2 for _ in range(height*2)]
    for y in range(height):
        for x in range(width):
            prob = random.randint(0, 5)
            current_share = shares_matrix[prob]
            matrix_1[2*y][2*x] = current_share[0]
            matrix_1[2*y][2*x+1] = current_share[1]
            matrix_1[2*y+1][2*x] = current_share[2]
            matrix_1[2*y+1][2*x+1] = current_share[3]
            if original_matrix[y][x] == 1:
                matrix_2[2*y][2*x] = current_share[0]
                matrix_2[2*y][2*x+1] = current_share[1]
                matrix_2[2*y+1][2*x] = current_share[2]
                matrix_2[2*y+1][2*x+1] = current_share[3]
            else:
                matrix_2[2*y][2*x] = current_share[4]
                matrix_2[2*y][2*x+1] = current_share[5]
                matrix_2[2*y+1][2*x] = current_share[6]
                matrix_2[2*y+1][2*x+1] = current_share[7]
            final_matrix[2*y][2*x] = matrix_1[2*y][2*x]
            final_matrix[2*y][2*x+1] = matrix_1[2*y][2*x+1]
            final_matrix[2*y+1][2*x] = matrix_1[2*y+1][2*x]
            final_matrix[2*y+1][2*x+1] = matrix_1[2*y+1][2*x+1]
            if matrix_2[2*y][2*x] == 0:
                final_matrix[2*y][2*x] = 0
            if matrix_2[2*y][2*x+1] == 0:
                final_matrix[2*y][2*x+1] = 0
            if matrix_2[2*y+1][2*x] == 0:
                final_matrix[2*y+1][2*x] = 0
            if matrix_2[2*y+1][2*x+1] == 0:
                final_matrix[2*y+1][2*x+1] = 0
    plt.imsave(f"{name}_share1.png", np.array(matrix_1) * 255, cmap="gray", vmin=0, vmax=255)
    plt.imsave(f"{name}_share2.png", np.array(matrix_2) * 255, cmap="gray", vmin=0, vmax=255)
    plt.imsave(f"{name}_merged.png", np.array(final_matrix) * 255, cmap="gray", vmin=0, vmax=255)
