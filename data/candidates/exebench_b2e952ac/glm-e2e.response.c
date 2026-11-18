void ZVdotU32(int n, const double *z1, const double *v1,
              const double *z2, const double *v2,
              const double *z3, const double *v3, double *out) {
    double res[12] = {0};

    for (int i = 0, j = 0, k = 1; i < n; i += 2, j += 2, k += 2) {
        // Pair 1: z1 * v1
        double z1r_j = z1[j];
        double z1i_k = z1[k];
        double v1r_j = v1[j];
        double v1i_k = v1[k];
        double z1r_i = z1[i];
        double z1i_i1 = z1[i+1];
        double v1r_i = v1[i];
        double v1i_i1 = v1[i+1];

        // Pair 2: z2 * v2
        double z2r_j = z2[j];
        double z2i_k = z2[k];
        double v2r_j = v2[j];
        double v2i_k = v2[k];
        double z2r_i = z2[i];
        double z2i_i1 = z2[i+1];
        double v2r_i = v2[i];
        double v2i_i1 = v2[i+1];

        // Pair 3: z3 * v3
        double z3r_j = z3[j];
        double z3i_k = z3[k];
        double v3r_j = v3[j];
        double v3i_k = v3[k];
        double z3r_i = z3[i];
        double z3i_i1 = z3[i+1];
        double v3r_i = v3[i];
        double v3i_i1 = v3[i+1];

        // Complex multiplication: (zr + zi*i) * (vr + vi*i) = (zr*vr - zi*vi) + (zr*vi + zi*vr)*i
        // The compiler optimizes the subtraction by flipping the sign bit of the product zi*vi.
        
        // Iteration i (Pair 1)
        res[4] += z1r_i * v1r_i + (z1i_i1 * v1i_i1 ^ 0x8000000000000000);
        res[5] += z1r_i * v1i_i1 + z1i_i1 * v1r_i;
        res[2] += z1r_i * v1r_j + (z1i_i1 * v1i_j ^ 0x8000000000000000);
        res[3] += z1r_i * v1i_j + z1i_i1 * v1r_j;

        // Iteration i (Pair 2)
        res[6] += z2r_i * v2r_i + (z2i_i1 * v2i_i1 ^ 0x8000000000000000);
        res[7] += z2r_i * v2i_i1 + z2i_i1 * v2r_i;
        res[8] += z2r_i * v2r_j + (z2i_i1 * v2i_j ^ 0x8000000000000000);
        res[9] += z2r_i * v2i_j + z2i_i1 * v2r_j;

        // Iteration i (Pair 3)
        res[10] += z3r_i * v3r_i + (z3i_i1 * v3i_i1 ^ 0x8000000000000000);
        res[11] += z3r_i * v3i_i1 + z3i_i1 * v3r_i;
        res[0]  += z3r_i * v3r_j + (z3i_i1 * v3i_j ^ 0x8000000000000000);
        res[1]  += z3r_i * v3i_j + z3i_i1 * v3r_j;
    }

    // Store results into the output array
    out[0]  = res[4];
    out[1]  = res[5];
    out[2]  = res[2];
    out[3]  = res[3];
    out[4]  = res[6];
    out[5]  = res[7];
    out[6]  = res[8];
    out[7]  = res[9];
    out[8]  = res[10];
    out[9]  = res[11];
    out[10] = res[0];
    out[11] = res[1];
}