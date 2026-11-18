void scale_mat(struct Matrix *mat, int sx, int sy) {
    if (sx != 1024) {
        mat->m[0][0] = (mat->m[0][0] * sx) / 1024;
        mat->m[0][1] = (mat->m[0][1] * sx) / 1024;
        mat->m[0][2] = (mat->m[0][2] * sx) / 1024;
    }
    if (sy != 1024) {
        mat->m[1][0] = (mat->m[1][0] * sy) / 1024;
        mat->m[1][1] = (mat->m[1][1] * sy) / 1024;
        mat->m[1][2] = (mat->m[1][2] * sy) / 1024;
    }
}