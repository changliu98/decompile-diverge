void rifft2pt(float *data, float scale) {
    float a = data[0];
    float b = data[1];
    float c = data[2] * 0.5f;
    float d = data[3] * 0.5f;

    float t1 = a + b;
    float t2 = a - b;

    data[0] = (t1 + c) * scale;
    data[1] = (t2 - d) * scale;
    data[2] = (t1 - c) * scale;
    data[3] = (t2 + d) * scale;
}