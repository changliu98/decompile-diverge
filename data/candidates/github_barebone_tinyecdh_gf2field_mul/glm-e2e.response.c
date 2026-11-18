void gf2field_mul(gf2field_elem *out, const gf2field_elem *a, const gf2field_elem *b) {
    gf2field_elem tmp;

    // Assert that out and b do not point to the same memory location
    if (out == b) {
        __assert_fail("out != b", "file.c", 450, "gf2field_mul");
    }

    // tmp = a
    gf2field_copy(&tmp, a);

    // if (b == 0) out = 0; else out = a;
    if (gf2field_is_zero(b)) {
        gf2field_is_zero(out); // Likely optimized to a zeroing function like gf2field_set_zero(out)
    } else {
        gf2field_copy(out, a);
    }

    // Binary expansion (square-and-multiply) loop
    // 0xa3 is 163 in decimal, typical for GF(2^163)
    for (int i = 1; i < 163; i++) {
        // tmp = tmp << 1 (Square in GF(2) representation)
        gf2field_lshift(&tmp, &tmp, 1);
        
        // Reduce tmp modulo the irreducible polynomial if it overflowed
        if (gf2field_is_one(&tmp)) {
            gf2field_reduce(&tmp, &tmp);
        }
        
        // If the i-th bit of b is set, add tmp to out
        if (bitvec_get_bit(b, i)) {
            gf2field_add(out, out, &tmp);
        }
    }
}