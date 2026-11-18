void __cdecl mtxMultiply(float *ret, const float *lhs, const float *rhs)
{
    // Row 0
    ret[0]  = M(lhs, 0, 0) * M(rhs, 0, 0) + M(lhs, 0, 1) * M(rhs, 1, 0) + M(lhs, 0, 2) * M(rhs, 2, 0) + M(lhs, 0, 3) * M(rhs, 3, 0);
    ret[1]  = M(lhs, 0, 0) * M(rhs, 0, 1) + M(lhs, 0, 1) * M(rhs, 1, 1) + M(lhs, 0, 2) * M(rhs, 2, 1) + M(lhs, 0, 3) * M(rhs, 3, 1);
    ret[2]  = M(lhs, 0, 0) * M(rhs, 0, 2) + M(lhs, 0, 1) * M(rhs, 1, 2) + M(lhs, 0, 2) * M(rhs, 2, 2) + M(lhs, 0, 3) * M(rhs, 3, 2);
    ret[3]  = M(lhs, 0, 0) * M(rhs, 0, 3) + M(lhs, 0, 1) * M(rhs, 1, 3) + M(lhs, 0, 2) * M(rhs, 2, 3) + M(lhs, 0, 3) * M(rhs, 3, 3);

    // Row 1
    ret[4]  = M(lhs, 1, 0) * M(rhs, 0, 0) + M(lhs, 1, 1) * M(rhs, 1, 0) + M(lhs, 1, 2) * M(rhs, 2, 0) + M(lhs, 1, 3) * M(rhs, 3, 0);
    ret[5]  = M(lhs, 1, 0) * M(rhs, 0, 1) + M(lhs, 1, 1) * M(rhs, 1, 1) + M(lhs, 1, 2) * M(rhs, 2, 1) + M(lhs, 1, 3) * M(rhs, 3, 1);
    ret[6]  = M(lhs, 1, 0) * M(rhs, 0, 2) + M(lhs, 1, 1) * M(rhs, 1, 2) + M(lhs, 1, 2) * M(rhs, 2, 2) + M(lhs, 1, 3) * M(rhs, 3, 2);
    ret[7]  = M(lhs, 1, 0) * M(rhs, 0, 3) + M(lhs, 1, 1) * M(rhs, 1, 3) + M(lhs, 1, 2) * M(rhs, 2, 3) + M(lhs, 1, 3) * M(rhs, 3, 3);

    // Row 2
    ret[8]  = M(lhs, 2, 0) * M(rhs, 0, 0) + M(lhs, 2, 1) * M(rhs, 1, 0) + M(lhs, 2, 2) * M(rhs, 2, 0) + M(lhs, 2, 3) * M(rhs, 3, 0);
    ret[9]  = M(lhs, 2, 0) * M(rhs, 0, 1) + M(lhs, 2, 1) * M(rhs, 1, 1) + M(lhs, 2, 2) * M(rhs, 2, 1) + M(lhs, 2, 3) * M(rhs, 3, 1);
    ret[10] = M(lhs, 2, 0) * M(rhs, 0, 2) + M(lhs, 2, 1) * M(rhs, 1, 2) + M(lhs, 2, 2) * M(rhs, 2, 2) + M(lhs, 2, 3) * M(rhs, 3, 2);
    ret[11] = M(lhs, 2, 0) * M(rhs, 0, 3) + M(lhs, 2, 1) * M(rhs, 1, 3) + M(lhs, 2, 2) * M(rhs, 2, 3) + M(lhs, 2, 3) * M(rhs, 3, 3);

    // Row 3
    ret[12] = M(lhs, 3, 0) * M(rhs, 0, 0) + M(lhs, 3, 1) * M(rhs, 1, 0) + M(lhs, 3, 2) * M(rhs, 2, 0) + M(lhs, 3, 3) * M(rhs, 3, 0);
    ret[13] = M(lhs, 3, 0) * M(rhs, 0, 1) + M(lhs, 3, 1) * M(rhs, 1, 1) + M(lhs, 3, 2) * M(rhs, 2, 1) + M(lhs, 3, 3) * M(rhs, 3, 1);
    ret[14] = M(lhs, 3, 0) * M(rhs, 0, 2) + M(lhs, 3, 1) * M(rhs, 1, 2) + M(lhs, 3, 2) * M(rhs, 2, 2) + M(lhs, 3, 3) * M(rhs, 3, 2);
    ret[15] = M(lhs, 3, 0) * M(rhs, 0, 3) + M(lhs, 3, 1) * M(rhs, 1, 3) + M(lhs, 3, 2) * M(rhs, 2, 3) + M(lhs, 3, 3) * M(rhs, 3, 3);
}