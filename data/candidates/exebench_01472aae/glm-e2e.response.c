void mlMatrixLoadPositionTransposedRotation(Matrix4x4 *out, const Vector3 *pos, const Matrix4x4 *rot) {
    // Row 0
    out->m[0][0] = rot->m[0][0];
    out->m[0][1] = rot->m[1][0];
    out->m[0][2] = rot->m[2][0];
    out->m[0][3] = 0.0f;

    // Row 1
    out->m[1][0] = rot->m[0][1];
    out->m[1][1] = rot->m[1][1];
    out->m[1][2] = rot->m[2][1];
    out->m[1][3] = 0.0f;

    // Row 2
    out->m[2][0] = rot->m[0][2];
    out->m[2][1] = rot->m[1][2];
    out->m[2][2] = rot->m[2][2];
    out->m[2][3] = 0.0f;

    // Row 3 (Translation)
    out->m[3][0] = pos->v[0];
    out->m[3][1] = pos->v[1];
    out->m[3][2] = pos->v[2];
    out->m[3][3] = 1.0f;
}