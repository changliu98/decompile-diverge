void cross5(float *vec_a, float *vec_b, float *vec_c, float *vec_d, float *result)
{
    // Calculate the 0-th component of the 5D cross product result
    // Sum of signed permutations of products of 4 elements from v0, v1, v2, v3
    // Coefficient DAT_00103004 likely represents a specific sign or scaling factor (e.g., -1 or 1)
    *result = vec_a[4] * vec_b[3] * vec_c[2] * vec_d[1] +
          SIGN_FACTOR * vec_a[4] * vec_b[3] * vec_c[1] * vec_d[2] +
          SIGN_FACTOR * vec_a[4] * vec_b[2] * vec_c[3] * vec_d[1] +
          vec_a[4] * vec_b[2] * vec_c[1] * vec_d[3] +
          vec_a[4] * vec_b[1] * vec_c[3] * vec_d[2] +
          SIGN_FACTOR * vec_a[4] * vec_b[1] * vec_c[2] * vec_d[3] +
          SIGN_FACTOR * vec_a[3] * vec_b[4] * vec_c[2] * vec_d[1] +
          vec_a[3] * vec_b[4] * vec_c[1] * vec_d[2] +
          vec_a[3] * vec_b[2] * vec_c[4] * vec_d[1] +
          SIGN_FACTOR * vec_a[3] * vec_b[2] * vec_c[1] * vec_d[4] +
          SIGN_FACTOR * vec_a[3] * vec_b[1] * vec_c[4] * vec_d[2] +
          vec_a[3] * vec_b[1] * vec_c[2] * vec_d[4] +
          vec_a[2] * vec_b[4] * vec_c[3] * vec_d[1] +
          SIGN_FACTOR * vec_a[2] * vec_b[4] * vec_c[1] * vec_d[3] +
          SIGN_FACTOR * vec_a[2] * vec_b[3] * vec_c[4] * vec_d[1] +
          vec_a[2] * vec_b[3] * vec_c[1] * vec_d[4] +
          vec_a[2] * vec_b[1] * vec_c[4] * vec_d[3] +
          SIGN_FACTOR * vec_a[2] * vec_b[1] * vec_c[3] * vec_d[4] +
          SIGN_FACTOR * vec_a[1] * vec_b[4] * vec_c[3] * vec_d[2] +
          vec_a[1] * vec_b[4] * vec_c[2] * vec_d[3] +
          vec_a[1] * vec_b[3] * vec_c[4] * vec_d[2] +
          SIGN_FACTOR * vec_a[1] * vec_b[3] * vec_c[2] * vec_d[4] +
          vec_a[1] * vec_b[2] * vec_c[3] * vec_d[4] + SIGN_FACTOR * vec_a[1] * vec_b[2] * vec_c[4] * vec_d[3];

    // Calculate the 1-st component of the 5D cross product result
    result[1] = SIGN_FACTOR * vec_a[4] * vec_b[3] * vec_c[2] * vec_d[0] +
            vec_a[4] * vec_b[3] * vec_c[0] * vec_d[2] +
            vec_a[4] * vec_b[2] * vec_c[3] * vec_d[0] +
            SIGN_FACTOR * vec_a[4] * vec_b[2] * vec_c[0] * vec_d[3] +
            SIGN_FACTOR * vec_a[4] * vec_b[0] * vec_c[3] * vec_d[2] +
            vec_a[4] * vec_b[0] * vec_c[2] * vec_d[3] +
            vec_a[3] * vec_b[4] * vec_c[2] * vec_d[0] +
            SIGN_FACTOR * vec_a[3] * vec_b[4] * vec_c[0] * vec_d[2] +
            SIGN_FACTOR * vec_a[3] * vec_b[2] * vec_c[4] * vec_d[0] +
            vec_a[3] * vec_b[2] * vec_c[0] * vec_d[4] +
            vec_a[3] * vec_b[0] * vec_c[4] * vec_d[2] +
            SIGN_FACTOR * vec_a[3] * vec_b[0] * vec_c[2] * vec_d[4] +
            SIGN_FACTOR * vec_a[2] * vec_b[4] * vec_c[3] * vec_d[0] +
            vec_a[2] * vec_b[4] * vec_c[0] * vec_d[3] +
            vec_a[2] * vec_b[3] * vec_c[4] * vec_d[0] +
            SIGN_FACTOR * vec_a[2] * vec_b[3] * vec_c[0] * vec_d[4] +
            SIGN_FACTOR * vec_a[2] * vec_b[0] * vec_c[4] * vec_d[3] +
            vec_a[2] * vec_b[0] * vec_c[3] * vec_d[4] +
            vec_a[0] * vec_b[4] * vec_c[3] * vec_d[2] +
            SIGN_FACTOR * vec_a[0] * vec_b[4] * vec_c[2] * vec_d[3] +
            SIGN_FACTOR * vec_a[0] * vec_b[3] * vec_c[4] * vec_d[2] +
            vec_a[0] * vec_b[3] * vec_c[2] * vec_d[4] +
            SIGN_FACTOR * vec_a[0] * vec_b[2] * vec_c[3] * vec_d[4] + vec_a[0] * vec_b[2] * vec_c[4] * vec_d[3];

    // Calculate the 2-nd component of the 5D cross product result
    result[2] = vec_a[4] * vec_b[3] * vec_c[1] * vec_d[0] +
            SIGN_FACTOR * vec_a[4] * vec_b[3] * vec_c[0] * vec_d[1] +
            SIGN_FACTOR * vec_a[4] * vec_b[1] * vec_c[3] * vec_d[0] +
            vec_a[4] * vec_b[1] * vec_c[0] * vec_d[3] +
            vec_a[4] * vec_b[0] * vec_c[3] * vec_d[1] +
            SIGN_FACTOR * vec_a[4] * vec_b[0] * vec_c[1] * vec_d[3] +
            SIGN_FACTOR * vec_a[3] * vec_b[4] * vec_c[1] * vec_d[0] +
            vec_a[3] * vec_b[4] * vec_c[0] * vec_d[1] +
            vec_a[3] * vec_b[1] * vec_c[4] * vec_d[0] +
            SIGN_FACTOR * vec_a[3] * vec_b[1] * vec_c[0] * vec_d[4] +
            SIGN_FACTOR * vec_a[3] * vec_b[0] * vec_c[4] * vec_d[1] +
            vec_a[3] * vec_b[0] * vec_c[1] * vec_d[4] +
            vec_a[1] * vec_b[4] * vec_c[3] * vec_d[0] +
            SIGN_FACTOR * vec_a[1] * vec_b[4] * vec_c[0] * vec_d[3] +
            SIGN_FACTOR * vec_a[1] * vec_b[3] * vec_c[4] * vec_d[0] +
            vec_a[1] * vec_b[3] * vec_c[0] * vec_d[4] +
            vec_a[1] * vec_b[0] * vec_c[4] * vec_d[3] +
            SIGN_FACTOR * vec_a[1] * vec_b[0] * vec_c[3] * vec_d[4] +
            SIGN_FACTOR * vec_a[0] * vec_b[4] * vec_c[3] * vec_d[1] +
            vec_a[0] * vec_b[4] * vec_c[1] * vec_d[3] +
            vec_a[0] * vec_b[3] * vec_c[4] * vec_d[1] +
            SIGN_FACTOR * vec_a[0] * vec_b[3] * vec_c[1] * vec_d[4] +
            vec_a[0] * vec_b[1] * vec_c[3] * vec_d[4] + SIGN_FACTOR * vec_a[0] * vec_b[1] * vec_c[4] * vec_d[3];

    // Calculate the 3-rd component of the 5D cross product result
    result[3] = SIGN_FACTOR * vec_a[4] * vec_b[2] * vec_c[1] * vec_d[0] +
            vec_a[4] * vec_b[2] * vec_c[0] * vec_d[1] +
            vec_a[4] * vec_b[1] * vec_c[2] * vec_d[0] +
            SIGN_FACTOR * vec_a[4] * vec_b[1] * vec_c[0] * vec_d[2] +
            SIGN_FACTOR * vec_a[4] * vec_b[0] * vec_c[2] * vec_d[1] +
            vec_a[4] * vec_b[0] * vec_c[1] * vec_d[2] +
            vec_a[2] * vec_b[4] * vec_c[1] * vec_d[0] +
            SIGN_FACTOR * vec_a[2] * vec_b[4] * vec_c[0] * vec_d[1] +
            SIGN_FACTOR * vec_a[2] * vec_b[1] * vec_c[4] * vec_d[0] +
            vec_a[2] * vec_b[1] * vec_c[0] * vec_d[4] +
            vec_a[2] * vec_b[0] * vec_c[4] * vec_d[1] +
            SIGN_FACTOR * vec_a[2] * vec_b[0] * vec_c[1] * vec_d[4] +
            SIGN_FACTOR * vec_a[1] * vec_b[4] * vec_c[2] * vec_d[0] +
            vec_a[1] * vec_b[4] * vec_c[0] * vec_d[2] +
            vec_a[1] * vec_b[2] * vec_c[4] * vec_d[0] +
            SIGN_FACTOR * vec_a[1] * vec_b[2] * vec_c[0] * vec_d[4] +
            SIGN_FACTOR * vec_a[1] * vec_b[0] * vec_c[4] * vec_d[2] +
            vec_a[1] * vec_b[0] * vec_c[2] * vec_d[4] +
            vec_a[0] * vec_b[4] * vec_c[2] * vec_d[1] +
            SIGN_FACTOR * vec_a[0] * vec_b[4] * vec_c[1] * vec_d[2] +
            SIGN_FACTOR * vec_a[0] * vec_b[2] * vec_c[4] * vec_d[1] +
            vec_a[0] * vec_b[2] * vec_c[1] * vec_d[4] +
            SIGN_FACTOR * vec_a[0] * vec_b[1] * vec_c[2] * vec_d[4] + vec_a[0] * vec_b[1] * vec_c[4] * vec_d[2];

    // Calculate the 4-th component of the 5D cross product result
    result[4] = vec_a[3] * vec_b[2] * vec_c[1] * vec_d[0] +
            SIGN_FACTOR * vec_a[3] * vec_b[2] * vec_c[0] * vec_d[1] +
            SIGN_FACTOR * vec_a[3] * vec_b[1] * vec_c[2] * vec_d[0] +
            vec_a[3] * vec_b[1] * vec_c[0] * vec_d[2] +
            vec_a[3] * vec_b[0] * vec_c[2] * vec_d[1] +
            SIGN_FACTOR * vec_a[3] * vec_b[0] * vec_c[1] * vec_d[2] +
            SIGN_FACTOR * vec_a[2] * vec_b[3] * vec_c[1] * vec_d[0] +
            vec_a[2] * vec_b[3] * vec_c[0] * vec_d[1] +
            vec_a[2] * vec_b[1] * vec_c[3] * vec_d[0] +
            SIGN_FACTOR * vec_a[2] * vec_b[1] * vec_c[0] * vec_d[3] +
            SIGN_FACTOR * vec_a[2] * vec_b[0] * vec_c[3] * vec_d[1] +
            vec_a[2] * vec_b[0] * vec_c[1] * vec_d[3] +
            vec_a[1] * vec_b[3] * vec_c[2] * vec_d[0] +
            SIGN_FACTOR * vec_a[1] * vec_b[3] * vec_c[0] * vec_d[2] +
            SIGN_FACTOR * vec_a[1] * vec_b[2] * vec_c[3] * vec_d[0] +
            vec_a[1] * vec_b[2] * vec_c[0] * vec_d[3] +
            vec_a[1] * vec_b[0] * vec_c[3] * vec_d[2] +
            SIGN_FACTOR * vec_a[1] * vec_b[0] * vec_c[2] * vec_d[3] +
            SIGN_FACTOR * vec_a[0] * vec_b[3] * vec_c[2] * vec_d[1] +
            vec_a[0] * vec_b[3] * vec_c[1] * vec_d[2] +
            vec_a[0] * vec_b[2] * vec_c[3] * vec_d[1] +
            SIGN_FACTOR * vec_a[0] * vec_b[2] * vec_c[1] * vec_d[3] +
            vec_a[0] * vec_b[1] * vec_c[2] * vec_d[3] + SIGN_FACTOR * vec_a[0] * vec_b[1] * vec_c[3] * vec_d[2];
}