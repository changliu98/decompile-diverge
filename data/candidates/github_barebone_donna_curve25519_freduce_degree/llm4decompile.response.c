void freduce_degree(limb *output)
{
    limb carry;

    output[8] += output[18] * 16;
    output[8] += output[18] * 2;
    output[8] += output[18];

    output[7] += output[17] * 16;
    output[7] += output[17] * 2;
    output[7] += output[17];

    output[6] += output[16] * 16;
    output[6] += output[16] * 2;
    output[6] += output[16];

    output[5] += output[15] * 16;
    output[5] += output[15] * 2;
    output[5] += output[15];

    output[4] += output[14] * 16;
    output[4] += output[14] * 2;
    output[4] += output[14];

    output[3] += output[13] * 16;
    output[3] += output[13] * 2;
    output[3] += output[13];

    output[2] += output[12] * 16;
    output[2] += output[12] * 2;
    output[2] += output[12];

    output[1] += output[11] * 16;
    output[1] += output[11] * 2;
    output[1] += output[11];

    output[0] += output[10] * 16;
    output[0] += output[10] * 2;
    output[0] += output[10];

    carry = output[0] >> 51;
    output[0] &= 0x7ffffffffffff;

    output[1] += carry * 16;
    output[1] += carry * 2;
    output[1] += carry;

    carry = output[1] >> 51;
    output[1] &= 0x7ffffffffffff;

    output[2] += carry * 16;
    output[2] += carry * 2;
    output[2] += carry;

    carry = output[2] >> 51;
    output[2] &= 0x7ffffffffffff;

    output[3] += carry * 16;
    output[3] += carry * 2;
    output[3] += carry;

    carry = output[3] >> 51;
    output[3] &= 0x7ffffffffffff;

    output[4] += carry * 16;
    output[4] += carry * 2;
    output[4] += carry;

    carry = output[4] >> 51;
    output[4] &= 0x7ffffffffffff;

    output[5] += carry * 16;
    output[5] += carry * 2;
    output[5] += carry;

    carry = output[5] >> 51;
    output[5] &= 0x7ffffffffffff;

    output[6] += carry * 16;
    output[6] += carry * 2;
    output[6] += carry;

    carry = output[6] >> 51;
    output[6] &= 0x7ffffffffffff;

    output[7] += carry * 16;
    output[7] += carry * 2;
    output[7] += carry;

    carry = output[7] >> 51;
    output[7] &= 0x7ffffffffffff;

    output[8] += carry * 16;
    output[8] += carry * 2;
    output[8] += carry;

    carry = output[8] >> 51;
    output[8] &= 0x7ffffffffffff;
}