void __cdecl bn_mul_comba8(uint64_t *r, uint64_t *a, uint64_t *b)
{
    uint64_t c1 = 0;
    uint64_t c2 = 0;
    uint64_t c3 = 0;

    // r[0] = a[0] * b[0]
    MUL_ADD_CARRY(a[0], b[0], c1, c2, c3);
    r[0] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[1] = a[0]*b[1] + a[1]*b[0]
    MUL_ADD_CARRY(a[0], b[1], c1, c2, c3);
    MUL_ADD_CARRY(a[1], b[0], c1, c2, c3);
    r[1] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[2] = a[0]*b[2] + a[1]*b[1] + a[2]*b[0]
    MUL_ADD_CARRY(a[0], b[2], c1, c2, c3);
    MUL_ADD_CARRY(a[1], b[1], c1, c2, c3);
    MUL_ADD_CARRY(a[2], b[0], c1, c2, c3);
    r[2] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[3] = a[0]*b[3] + a[1]*b[2] + a[2]*b[1] + a[3]*b[0]
    MUL_ADD_CARRY(a[0], b[3], c1, c2, c3);
    MUL_ADD_CARRY(a[1], b[2], c1, c2, c3);
    MUL_ADD_CARRY(a[2], b[1], c1, c2, c3);
    MUL_ADD_CARRY(a[3], b[0], c1, c2, c3);
    r[3] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[4] = a[0]*b[4] + a[1]*b[3] + a[2]*b[2] + a[3]*b[1] + a[4]*b[0]
    MUL_ADD_CARRY(a[0], b[4], c1, c2, c3);
    MUL_ADD_CARRY(a[1], b[3], c1, c2, c3);
    MUL_ADD_CARRY(a[2], b[2], c1, c2, c3);
    MUL_ADD_CARRY(a[3], b[1], c1, c2, c3);
    MUL_ADD_CARRY(a[4], b[0], c1, c2, c3);
    r[4] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[5] = a[0]*b[5] + a[1]*b[4] + a[2]*b[3] + a[3]*b[2] + a[4]*b[1] + a[5]*b[0]
    MUL_ADD_CARRY(a[0], b[5], c1, c2, c3);
    MUL_ADD_CARRY(a[1], b[4], c1, c2, c3);
    MUL_ADD_CARRY(a[2], b[3], c1, c2, c3);
    MUL_ADD_CARRY(a[3], b[2], c1, c2, c3);
    MUL_ADD_CARRY(a[4], b[1], c1, c2, c3);
    MUL_ADD_CARRY(a[5], b[0], c1, c2, c3);
    r[5] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[6] = a[0]*b[6] + a[1]*b[5] + a[2]*b[4] + a[3]*b[3] + a[4]*b[2] + a[5]*b[1] + a[6]*b[0]
    MUL_ADD_CARRY(a[0], b[6], c1, c2, c3);
    MUL_ADD_CARRY(a[1], b[5], c1, c2, c3);
    MUL_ADD_CARRY(a[2], b[4], c1, c2, c3);
    MUL_ADD_CARRY(a[3], b[3], c1, c2, c3);
    MUL_ADD_CARRY(a[4], b[2], c1, c2, c3);
    MUL_ADD_CARRY(a[5], b[1], c1, c2, c3);
    MUL_ADD_CARRY(a[6], b[0], c1, c2, c3);
    r[6] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[7] = a[0]*b[7] + a[1]*b[6] + a[2]*b[5] + a[3]*b[4] + a[4]*b[3] + a[5]*b[2] + a[6]*b[1] + a[7]*b[0]
    MUL_ADD_CARRY(a[0], b[7], c1, c2, c3);
    MUL_ADD_CARRY(a[1], b[6], c1, c2, c3);
    MUL_ADD_CARRY(a[2], b[5], c1, c2, c3);
    MUL_ADD_CARRY(a[3], b[4], c1, c2, c3);
    MUL_ADD_CARRY(a[4], b[3], c1, c2, c3);
    MUL_ADD_CARRY(a[5], b[2], c1, c2, c3);
    MUL_ADD_CARRY(a[6], b[1], c1, c2, c3);
    MUL_ADD_CARRY(a[7], b[0], c1, c2, c3);
    r[7] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[8] = a[1]*b[7] + a[2]*b[6] + a[3]*b[5] + a[4]*b[4] + a[5]*b[3] + a[6]*b[2] + a[7]*b[1]
    MUL_ADD_CARRY(a[1], b[7], c1, c2, c3);
    MUL_ADD_CARRY(a[2], b[6], c1, c2, c3);
    MUL_ADD_CARRY(a[3], b[5], c1, c2, c3);
    MUL_ADD_CARRY(a[4], b[4], c1, c2, c3);
    MUL_ADD_CARRY(a[5], b[3], c1, c2, c3);
    MUL_ADD_CARRY(a[6], b[2], c1, c2, c3);
    MUL_ADD_CARRY(a[7], b[1], c1, c2, c3);
    r[8] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[9] = a[2]*b[7] + a[3]*b[6] + a[4]*b[5] + a[5]*b[4] + a[6]*b[3] + a[7]*b[2]
    MUL_ADD_CARRY(a[2], b[7], c1, c2, c3);
    MUL_ADD_CARRY(a[3], b[6], c1, c2, c3);
    MUL_ADD_CARRY(a[4], b[5], c1, c2, c3);
    MUL_ADD_CARRY(a[5], b[4], c1, c2, c3);
    MUL_ADD_CARRY(a[6], b[3], c1, c2, c3);
    MUL_ADD_CARRY(a[7], b[2], c1, c2, c3);
    r[9] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[10] = a[3]*b[7] + a[4]*b[6] + a[5]*b[5] + a[6]*b[4] + a[7]*b[3]
    MUL_ADD_CARRY(a[3], b[7], c1, c2, c3);
    MUL_ADD_CARRY(a[4], b[6], c1, c2, c3);
    MUL_ADD_CARRY(a[5], b[5], c1, c2, c3);
    MUL_ADD_CARRY(a[6], b[4], c1, c2, c3);
    MUL_ADD_CARRY(a[7], b[3], c1, c2, c3);
    r[10] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[11] = a[4]*b[7] + a[5]*b[6] + a[6]*b[5] + a[7]*b[4]
    MUL_ADD_CARRY(a[4], b[7], c1, c2, c3);
    MUL_ADD_CARRY(a[5], b[6], c1, c2, c3);
    MUL_ADD_CARRY(a[6], b[5], c1, c2, c3);
    MUL_ADD_CARRY(a[7], b[4], c1, c2, c3);
    r[11] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[12] = a[5]*b[7] + a[6]*b[6] + a[7]*b[5]
    MUL_ADD_CARRY(a[5], b[7], c1, c2, c3);
    MUL_ADD_CARRY(a[6], b[6], c1, c2, c3);
    MUL_ADD_CARRY(a[7], b[5], c1, c2, c3);
    r[12] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[13] = a[6]*b[7] + a[7]*b[6]
    MUL_ADD_CARRY(a[6], b[7], c1, c2, c3);
    MUL_ADD_CARRY(a[7], b[6], c1, c2, c3);
    r[13] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[14] = a[7]*b[7]
    MUL_ADD_CARRY(a[7], b[7], c1, c2, c3);
    r[14] = c2;
    c2 = c3;
    c3 = c1;
    c1 = 0;

    // r[15] = final carry
    r[15] = c2;
}