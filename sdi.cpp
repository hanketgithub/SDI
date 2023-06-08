//
//  sdi.c
//  sdi
//
//  Created by Hank Lee on 5/31/23.
//  Copyright (c) 2023 Hank Lee. All rights reserved.
//


#include <stdint.h>
#include <iostream>

#include "sdi.h"


using namespace std;


uint32_t get_stride
(
    uint32_t width
)
{
    return (EAV_CYCLE * 2 + BLANK_LEN_1080 * 2 + SAV_CYCLE * 2 + width * 2) * 2; 
}


int convert_yuv420_1080_to_SDI
(
        uint8_t *dst,
  const uint8_t *src
)
{
    uint8_t (*py)[SRC_WIDTH_1080];
    uint8_t (*pu)[SRC_WIDTH_1080 / 2];
    uint8_t (*pv)[SRC_WIDTH_1080 / 2];
    int wxh = SRC_WIDTH_1080 * SRC_HEIGHT_1080;

    py = ( uint8_t (*)[SRC_WIDTH_1080] ) src;
    pu = ( uint8_t (*)[SRC_WIDTH_1080 / 2] ) (src + wxh);
    pv = ( uint8_t (*)[SRC_WIDTH_1080 / 2] ) (src + wxh + wxh / 4);    

    uint16_t *p = (uint16_t *) dst;

    for (int r = 0; r < SRC_HEIGHT_1080; r++)
    {
        // skip EAV, Blank and SAV
        //p += (EAV_CYCLE + BLANK_LEN_1080 + SAV_CYCLE) * 2;

        // Write EAV
        // Write 'E'
        *p = 0xFF03;
        p++;
        *p = 0xFF03;
        p++;
        // Write 'A'
        *p = 0x0000;
        p++;
        *p = 0x0000;
        p++;
        // Write 'V'
        *p = 0x0000;
        p++;
        *p = 0x0000;
        p++;
        // Write '.'
        *p = 0x7402;
        p++;
        *p = 0x7402;
        p++;

        // Skip blanking
        p += BLANK_LEN_1080 * 2;

        // Write SAV
        // Write 'S'
        *p = 0xFF03;
        p++;
        *p = 0xFF03;
        p++;
        // Write 'A'
        *p = 0x0000;
        p++;
        *p = 0x0000;
        p++;
        // Write 'V'
        *p = 0x0000;
        p++;
        *p = 0x0000;
        p++;
        // Write '.'
        *p = 0x0002;
        p++;
        *p = 0x0002;
        p++;

        for (int c = 0; c < SRC_WIDTH_1080; c += 2)
        {
            // output U
            *p = pu[r / 2][c / 2] << 8;
            p++;

            // output Y
            *p = py[r][c] << 8;
            p++;

            // output V
            *p = pv[r / 2][c / 2] << 8;
            p++;

            // output Y
            *p = py[r][c + 1] << 8;
            p++;
        }
    }

    return 0;
}