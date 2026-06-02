// ============================================================================
// Copyright (c) 2026 Ameera Almomani, Doa’a Aloqoul
// 
// This software is licensed under the BSD 3-Clause License (https://opensource.org/license/bsd-3-clause)
//
// This source code is provided for academic and research purposes only.
// 
// Conditions of use:
// 1. You may use, modify, and distribute this code for *non-commercial* 
//    research and educational purposes, provided that proper credit is given.
// 2. Commercial use of this code is *not permitted* without prior written consent.
// 3. Any publication or work that uses this code (in whole or in part) must 
//    cite the following paper: https://doi.org/10.1088/2631-8695/ae655e
// ============================================================================

#include "sobel.h"
#include <iostream>
#include <cassert>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



// Helper to print image
void print_image(pixel_t img[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << (int)img[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool read_png_to_array(const std::string& filename, pixel_t image[HEIGHT][WIDTH]) {
    int width, height, channels;

    // Load image as 1 channel (grayscale)
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 1);
    if (!data) {
        std::cerr << "Error: Could not load image " << filename << std::endl;
        return false;
    }

    // Resize or crop if needed
    for (int i = 0; i < HEIGHT && i < height; ++i) {
        for (int j = 0; j < WIDTH && j < width; ++j) {
            image[i][j] = data[i * width + j];
        }
    }

    stbi_image_free(data);
    return true;
}


// Write a 2D array to a grayscale PNG
void write_array_to_png(const std::string& filename, pixel_t image[HEIGHT][WIDTH]) {
    unsigned char* data = new unsigned char[HEIGHT * WIDTH];

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            data[i * WIDTH + j] = image[i][j];
        }
    }

    // Save as grayscale (1 channel)
    stbi_write_png(filename.c_str(), WIDTH, HEIGHT, 1, data, WIDTH);
    delete[] data;
}


int main() {
    pixel_t img_in[HEIGHT][WIDTH];
    pixel_pack_t img_out[HEIGHT][WIDTH / 64];

    pixel_t img_out_unpacked[HEIGHT][WIDTH];

    // input image
    std::string input_file = "D:\\Research\\CNN-FPGA\\Code_512\\imgs\\Lenna_gray.jpg";
	read_png_to_array(input_file,img_in);

    // Apply Sobel filter (hardware version)
    sobel_filter(img_in, img_out);

	// output image
    std::string output_file = "D:\\Research\\CNN-FPGA\\Code_512\\imgs\\Lena_Out__15_K.png";

    for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH / 64; j++) {
			pixel_pack_t pack = img_out[i][j];
			for (int k = 0; k < 64; k++) {
				img_out_unpacked[i][j * 64 + k] = pack.range((k + 1) * 8 - 1, k * 8);
			}
		}
	}

    // Write the output image to file
    write_array_to_png(output_file, img_out_unpacked);


    return 0;
}
