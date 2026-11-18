void swi_coortrf2(struct Vec3 *in, struct Vec3 *out, double a, double b) {
    double in_x = in->x;
    double in_y = in->y;
    double in_z = in->z;

    // out->y = in->y * b + in->z * a
    double out_y = in_y * b + in_z * a;

    // out->z = -in->y * a + in->z * b
    // The bitwise XOR with 0x8000000000000000 flips the sign bit of the double.
    double neg_in_y;
    *((uint64_t*)&neg_in_y) = *((uint64_t*)&in_y) ^ 0x8000000000000000;
    
    double out_z = neg_in_y * a + in_z * b;

    out->x = in_x;
    out->y = out_y;
    out->z = out_z;
}