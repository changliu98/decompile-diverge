void rifft2pt(float *data, float scale) {
    // The constant loaded from memory at 0x2004 is 0.5f
    float c = 0.5f; 

    float a = data[0];
    float b = data[1];
    float c_val = data[2] * 0.5f;
    float d_val = data[3] * 0.5f;

    float e = a + b;
    float f = a - b;

    a = e + c_val;
    b = f - d_val;
    c_val = e - c_val;
    d_val = f + d_val;

    data[0] = scale * a;
    data[1] = scale * b;
    data[2] = scale * c_val;
    data[3] = scale * d_val;
}