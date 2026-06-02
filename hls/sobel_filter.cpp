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

void sobel_filter(pixel_t img_in[HEIGHT][WIDTH], pixel_pack_t img_out[HEIGHT][WIDTH / 64]) {
    #pragma HLS INTERFACE axis port=img_in depth=1
    #pragma HLS INTERFACE axis port=img_out depth=1
    #pragma HLS INTERFACE ap_ctrl_none port=return

    // Small LBH-row circular output buffer
    pixel_t local_buf[LBH][WIDTH];
    #pragma HLS ARRAY_PARTITION variable=local_buf cyclic factor=N dim=2


    // Line buffer for input rows
    pixel_t linebuf[3][WIDTH];
    #pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1

    // Sliding 3x3 window
    pixel_t window[N][3][3];
    #pragma HLS ARRAY_PARTITION variable=window complete dim=0

    // Sobel kernels
    const int sobel_x[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    const int sobel_y[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
 

    Row_Loop: for (int i = 0; i < HEIGHT; i++) {
        Col_Loop: for (int j = 0; j < WIDTH; j++) {
            #pragma HLS PIPELINE II=1

            // Update line buffer
            linebuf[0][j] = linebuf[1][j];
            linebuf[1][j] = linebuf[2][j];
            linebuf[2][j] = img_in[i][j];
        }

        if (i > 2 ) {

       Loop1: for (int col_idx = 2; col_idx <= WIDTH-N; col_idx += N) {
           
                // Extract 3x3 window
               
                int Gx[N] = {0};
                int Gy[N] = {0};
            Kernel_Loop: for (int k = 0; k < N; k++) {
                    #pragma HLS UNROLL
                
               Kernel_Loop2: for (int wi = 0; wi < 3; wi++) {
                    for (int wj = 0; wj < 3; wj++) {
                        #pragma HLS UNROLL
                        window[k][wi][wj] = linebuf[wi][col_idx - 2 + k + wj];
                    }
                }

                         
                    int sumx = 0, sumy = 0;

                   Loop2: for (int m = 0; m < 3; m++) {
                        #pragma HLS UNROLL
                     Loop3:   for (int n = 0; n < 3; n++) {
                            #pragma HLS UNROLL
                            sumx += window[k][m][n] * sobel_x[m][n];
                            sumy += window[k][m][n] * sobel_y[m][n];
                        }
                    }

                    Gx[k] = sumx;
                    Gy[k] = sumy;
               
                      int G = std::abs(Gx[k]) + std::abs(Gy[k]);
                    if (G > 255) G = 255;

                    int row_idx = (i - 1) % LBH;
                    local_buf[row_idx][col_idx - 1+ k] = (pixel_t)G;

                }
            }
        }

        // Pack and write output row after processing full window
        if (i > 2) {
            int row_idx = (i - 1) % LBH;
           Loop4: for (int j = 0; j < WIDTH; j += 64) {
                #pragma HLS PIPELINE II=1
                pixel_pack_t pack;

               Loop5: for (int k = 0; k < 64; k++) {
                    #pragma HLS UNROLL
                    int col = j + k;

                    // Check border condition
                    bool is_border = ((i - 1) == 0 || (i - 1) == HEIGHT - 1 || col == 0 || col == WIDTH - 1);
                    pixel_t val = is_border ? (pixel_t)0 : local_buf[row_idx][col];

                    pack.range((k + 1) * 8 - 1, k * 8) = val;
                }

                img_out[i - 1][j / 64] = pack;
            }
        }
    }
}
