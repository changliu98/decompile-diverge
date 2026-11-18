void __cdecl geom_matmat4d(const double *a, const double *b, double *c)
{
    // Column 0 of C
    MAT4(c, 0, 0) = MAT4(a, 0, 0) * MAT4(b, 0, 0) + MAT4(a, 1, 0) * MAT4(b, 0, 1) + MAT4(a, 2, 0) * MAT4(b, 0, 2) + MAT4(a, 3, 0) * MAT4(b, 0, 3);
    MAT4(c, 0, 1) = MAT4(a, 0, 1) * MAT4(b, 0, 0) + MAT4(a, 1, 1) * MAT4(b, 0, 1) + MAT4(a, 2, 1) * MAT4(b, 0, 2) + MAT4(a, 3, 1) * MAT4(b, 0, 3);
    MAT4(c, 0, 2) = MAT4(a, 0, 2) * MAT4(b, 0, 0) + MAT4(a, 1, 2) * MAT4(b, 0, 1) + MAT4(a, 2, 2) * MAT4(b, 0, 2) + MAT4(a, 3, 2) * MAT4(b, 0, 3);
    MAT4(c, 0, 3) = MAT4(a, 0, 3) * MAT4(b, 0, 0) + MAT4(a, 1, 3) * MAT4(b, 0, 1) + MAT4(a, 2, 3) * MAT4(b, 0, 2) + MAT4(a, 3, 3) * MAT4(b, 0, 3);

    // Column 1 of C
    MAT4(c, 1, 0) = MAT4(a, 0, 0) * MAT4(b, 1, 0) + MAT4(a, 1, 0) * MAT4(b, 1, 1) + MAT4(a, 2, 0) * MAT4(b, 1, 2) + MAT4(a, 3, 0) * MAT4(b, 1, 3);
    MAT4(c, 1, 1) = MAT4(a, 0, 1) * MAT4(b, 1, 0) + MAT4(a, 1, 1) * MAT4(b, 1, 1) + MAT4(a, 2, 1) * MAT4(b, 1, 2) + MAT4(a, 3, 1) * MAT4(b, 1, 3);
    MAT4(c, 1, 2) = MAT4(a, 0, 2) * MAT4(b, 1, 0) + MAT4(a, 1, 2) * MAT4(b, 1, 1) + MAT4(a, 2, 2) * MAT4(b, 1, 2) + MAT4(a, 3, 2) * MAT4(b, 1, 3);
    MAT4(c, 1, 3) = MAT4(a, 0, 3) * MAT4(b, 1, 0) + MAT4(a, 1, 3) * MAT4(b, 1, 1) + MAT4(a, 2, 3) * MAT4(b, 1, 2) + MAT4(a, 3, 3) * MAT4(b, 1, 3);

    // Column 2 of C
    MAT4(c, 2, 0) = MAT4(a, 0, 0) * MAT4(b, 2, 0) + MAT4(a, 1, 0) * MAT4(b, 2, 1) + MAT4(a, 2, 0) * MAT4(b, 2, 2) + MAT4(a, 3, 0) * MAT4(b, 2, 3);
    MAT4(c, 2, 1) = MAT4(a, 0, 1) * MAT4(b, 2, 0) + MAT4(a, 1, 1) * MAT4(b, 2, 1) + MAT4(a, 2, 1) * MAT4(b, 2, 2) + MAT4(a, 3, 1) * MAT4(b, 2, 3);
    MAT4(c, 2, 2) = MAT4(a, 0, 2) * MAT4(b, 2, 0) + MAT4(a, 1, 2) * MAT4(b, 2, 1) + MAT4(a, 2, 2) * MAT4(b, 2, 2) + MAT4(a, 3, 2) * MAT4(b, 2, 3);
    MAT4(c, 2, 3) = MAT4(a, 0, 3) * MAT4(b, 2, 0) + MAT4(a, 1, 3) * MAT4(b, 2, 1) + MAT4(a, 2, 3) * MAT4(b, 2, 2) + MAT4(a, 3, 3) * MAT4(b, 2, 3);

    // Column 3 of C
    MAT4(c, 3, 0) = MAT4(a, 0, 0) * MAT4(b, 3, 0) + MAT4(a, 1, 0) * MAT4(b, 3, 1) + MAT4(a, 2, 0) * MAT4(b, 3, 2) + MAT4(a, 3, 0) * MAT4(b, 3, 3);
    MAT4(c, 3, 1) = MAT4(a, 0, 1) * MAT4(b, 3, 0) + MAT4(a, 1, 1) * MAT4(b, 3, 1) + MAT4(a, 2, 1) * MAT4(b, 3, 2) + MAT4(a, 3, 1) * MAT4(b, 3, 3);
    MAT4(c, 3, 2) = MAT4(a, 0, 2) * MAT4(b, 3, 0) + MAT4(a, 1, 2) * MAT4(b, 3, 1) + MAT4(a, 2, 2) * MAT4(b, 3, 2) + MAT4(a, 3, 2) * MAT4(b, 3, 3);
    MAT4(c, 3, 3) = MAT4(a, 0, 3) * MAT4(b, 3, 0) + MAT4(a, 1, 3) * MAT4(b, 3, 1) + MAT4(a, 2, 3) * MAT4(b, 3, 2) + MAT4(a, 3, 3) * MAT4(b, 3, 3);
}