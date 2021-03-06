/*********************************************************************
* Filename:   cmp.c
* Author:     Aiyu Xiao (xiao_ai_yu@live.cn)
*********************************************************************/
#include "../cmp.h"

#if defined(_M_X64)
#define _BitScanReverse_coeff _BitScanReverse64
#elif defined(_M_IX86)
#define _BitScanReverse_coeff _BitScanReverse
#else
#error "No matched architecture found."
#endif

int8_t math_uintx_cmp(const coeff_t src1[], size_t length1,
                      const coeff_t src2[], size_t length2) {

    const coeff_t* cur_src1 = src1 + length1 - 1;
    const coeff_t* cur_src2 = src2 + length2 - 1;
    const coeff_t* const rlast_src1 = src1 - 1;

    while (*cur_src1 == 0 && cur_src1 != src1) {
        --length1;
        --cur_src1;
    }
    while (*cur_src2 == 0 && cur_src2 != src2) {
        --length2;
        --cur_src2;
    }

    if (length1 == length2) {
        while (*cur_src1 == *cur_src2 && cur_src1 != src1) {
            --cur_src1;
            --cur_src2;
        }

        if (*cur_src1 > *cur_src2)
            return 1;
        else if (*cur_src1 < *cur_src2)
            return -1;
        else
            return 0;
    } else {
        return length1 > length2 ? 1 : -1;
    }
}

int8_t math_uintx_isZero(const coeff_t src[], size_t length) {
    for (size_t i = 0; i < length; ++i) 
        if (src[i] != 0) return 0;
    return 1;
}

size_t math_uintx_bit_length(const coeff_t src[], size_t length) {
    const coeff_t* cur_src = src + length - 1;
    while (cur_src != src && *cur_src == 0)
        --cur_src;

    unsigned long Index;
    if (_BitScanReverse_coeff(&Index, *cur_src)) 
        return (cur_src - src) * sizeof(coeff_t) * 8 + Index + 1;
    else 
        return 0;
}
