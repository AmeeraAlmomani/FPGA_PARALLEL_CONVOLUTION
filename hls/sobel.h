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


#ifndef SOBEL_H
#define SOBEL_H

#include <hls_stream.h>
#include <ap_int.h>
#include <cmath>


#define HEIGHT 512   // Image height 512
#define WIDTH 512    // Image width
#define N 1       // Number of kernels
#define LBH 1       //Output Local buffer height

typedef ap_uint<8> pixel_t;
typedef ap_uint<512> pixel_pack_t;
typedef ap_uint<8 * N> pixel_vec_t;

// Function prototype
void sobel_filter(pixel_t img_in[HEIGHT][WIDTH], pixel_pack_t img_out[HEIGHT][WIDTH / 64]); //pixel_t img_out[HEIGHT][WIDTH]

#endif  // SOBEL_H
