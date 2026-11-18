void __cdecl Mat4_RotateQuaternion(float *mat, float *q)
{
    // Helper function to process a 4-element vector (column or row) of the matrix.
    // This preserves the exact semantics of the original repeated blocks.
    auto process = [&](float m0, float m1, float m2, float m3) {
        float q0 = q[0];
        float q1 = q[1];
        float q2 = q[2];
        float q3 = q[3];

        float v0 = (-q2 * m1) + (q1 * m2) + (q3 * m0) + (q0 * m3);
        float v1 = (-q0 * m2) + (q2 * m0) + (q3 * m1) + (q1 * m3);
        float v2 = (-q1 * m0) + (q0 * m1) + (q3 * m2) + (q2 * m3);
        float v3 = (-q2 * m2) + (-q1 * m1) + (q3 * m3) + (-q0 * m0);

        float r0 = (-v2 * q1) + (v1 * q2) + (v3 * q0) + (v0 * q3);
        float r1 = (-v0 * q2) + (v2 * q0) + (v3 * q1) + (v1 * q3);
        float r2 = (-v1 * q0) + (v0 * q1) + (v3 * q2) + (v2 * q3);
        // r3 is computed but immediately discarded in the original code
        // float r3 = (-v2 * q2) + (-v1 * q1) + (v3 * q3) + (-v0 * q0);

        return std::tuple<float, float, float>(r0, r1, r2);
    };

    // Process the first three elements of the matrix vectors
    auto [m0, m1, m2] = process(mat[0], mat[1], mat[2], mat[3]);
    mat[0] = m0;
    mat[1] = m1;
    mat[2] = m2;
    mat[3] = 0.0f;

    auto [m4, m5, m6] = process(mat[4], mat[5], mat[6], mat[7]);
    mat[4] = m4;
    mat[5] = m5;
    mat[6] = m6;
    mat[7] = 0.0f;

    auto [m8, m9, m10] = process(mat[8], mat[9], mat[10], mat[11]);
    mat[8] = m8;
    mat[9] = m9;
    mat[10] = m10;
    mat[11] = 0.0f;
}