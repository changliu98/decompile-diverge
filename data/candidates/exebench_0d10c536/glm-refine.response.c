void __cdecl bitrv216(double *a)
{
    // Cast to uint64_t* to cleanly handle the 64-bit memory slots 
    // without type-punning confusion between double and __int64.
    uint64_t *v = (uint64_t *)a;

    // Read the values that will be overwritten
    uint64_t x1r  = v[2];
    uint64_t x1i  = v[3];
    uint64_t x2r  = v[4];
    uint64_t x2i  = v[5];
    uint64_t x3r  = v[6];
    uint64_t x3i  = v[7];
    uint64_t x4r  = v[8];
    uint64_t x4i  = v[9];
    uint64_t x5r  = v[10];
    uint64_t x5i  = v[11];
    uint64_t x7r  = v[14];
    uint64_t x7i  = v[15];
    uint64_t x8i  = v[17];
    uint64_t x10r = v[20];
    uint64_t x10i = v[21];
    uint64_t x11r = v[22];
    uint64_t x11i = v[23];
    uint64_t x12r = v[24];
    uint64_t x12i = v[25];
    uint64_t x13r = v[26];
    uint64_t x13i = v[27];
    uint64_t x14r = v[28];
    uint64_t x14i = v[29];

    // Perform the bit-reversal permutation swaps
    v[2]  = v[16]; // Index 1  <-> 8
    v[3]  = x8i;
    v[4]  = x4r;   // Index 2  <-> 4
    v[5]  = x4i;
    v[6]  = x12r;  // Index 3  <-> 12
    v[7]  = x12i;
    v[8]  = x2r;   // Index 4  <-> 2
    v[9]  = x2i;
    v[10] = x10r;  // Index 5  <-> 10
    v[11] = x10i;
    v[14] = x14r;  // Index 7  <-> 14
    v[15] = x14i;
    v[16] = x1r;   // Index 8  <-> 1
    v[17] = x1i;
    v[20] = x5r;   // Index 10 <-> 5
    v[21] = x5i;
    v[22] = x13r;  // Index 11 <-> 13
    v[23] = x13i;
    v[24] = x3r;   // Index 12 <-> 3
    v[25] = x3i;
    v[26] = x11r;  // Index 13 <-> 11
    v[27] = x11i;
    v[28] = x7r;   // Index 14 <-> 7
    v[29] = x7i;
}