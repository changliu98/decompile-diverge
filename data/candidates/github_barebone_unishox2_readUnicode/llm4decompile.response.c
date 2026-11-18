int32_t readUnicode(const unsigned char *buf, int *bit_no_p, int len)
{
    int sign, idx, num, adder, step_code_idx;
    int step_code_len[5] = {6, 12, 14, 16, 21};

    step_code_idx = getStepCodeIdx(buf, len, bit_no_p, 5);
    if (step_code_idx == 99) {
        return -151;
    } else if (step_code_idx == 5) {
        return getStepCodeIdx(buf, len, bit_no_p, 4) + 0x7fff0000;
    } else if (step_code_idx < 0) {
        return 0;
    }

    if (*bit_no_p < len) {
        sign = readBit(buf, *bit_no_p);
    } else {
        sign = 0;
    }
    *bit_no_p += 1;

    if (*bit_no_p + step_code_len[step_code_idx] - 1 >= len) {
        return -151;
    }

    num = getNumFromBits(buf, len, *bit_no_p, step_code_len[step_code_idx]);
    adder = uni_adder[step_code_idx];
    num += adder;
    *bit_no_p += step_code_len[step_code_idx];

    if (sign) {
        return -num;
    } else {
        return num;
    }
}