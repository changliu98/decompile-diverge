void convertscreenvertex(float *vertex, int width, int height) {
    vertex[0] = (vertex[0] - (width >> 1)) / (float)(width >> 1);
    vertex[1] = ((height >> 1) - vertex[1]) / (float)(width >> 1);
    vertex[2] = 1.0f;
}