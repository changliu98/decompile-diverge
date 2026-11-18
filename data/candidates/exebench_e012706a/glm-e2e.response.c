void cmatrix_to_frame(double *cmatrix, double *frame_r, double *frame_g, double *frame_b) {
    for (int i = 0; i < 3; i++) {
        frame_r[i] = cmatrix[i * 3 + 0];
        frame_g[i] = cmatrix[i * 3 + 1];
        frame_b[i] = cmatrix[i * 3 + 2];
    }
}