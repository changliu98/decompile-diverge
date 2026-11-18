void lin_solve_3(Vec3 *x, const Mat3 *A, const Vec3 *b) {
    // Intermediate cross products of the matrix columns/rows
    double t0 = A->m[4] * A->m[8] - A->m[5] * A->m[7];
    double t1 = A->m[5] * A->m[6] - A->m[3] * A->m[8];
    double t2 = A->m[3] * A->m[7] - A->m[4] * A->m[6];
    
    // Determinant of A
    double det = A->m[0] * t0 + A->m[1] * t1 + A->m[2] * t2;
    double inv_det = 1.0 / det;
    
    // Cofactors for the first column of the adjugate matrix
    double c0 = t0;
    double c1 = A->m[2] * A->m[7] - A->m[1] * A->m[8];
    double c2 = A->m[1] * A->m[5] - A->m[2] * A->m[4];
    
    // Cofactors for the second column of the adjugate matrix
    double c3 = A->m[5] * A->m[6] - A->m[3] * A->m[8];
    double c4 = t2;
    double c5 = A->m[0] * A->m[8] - A->m[2] * A->m[6];
    
    // Cofactors for the third column of the adjugate matrix
    double c6 = A->m[1] * A->m[6] - A->m[0] * A->m[7];
    double c7 = A->m[0] * A->m[5] - A->m[1] * A->m[4];
    double c8 = t1;
    
    // Compute x = (1 / det) * (Adjugate(A) * b)
    x->v[0] = inv_det * (c0 * b->v[0] + c1 * b->v[1] + c2 * b->v[2]);
    x->v[1] = inv_det * (c3 * b->v[0] + c4 * b->v[1] + c5 * b->v[2]);
    x->v[2] = inv_det * (c6 * b->v[0] + c7 * b->v[1] + c8 * b->v[2]);
}