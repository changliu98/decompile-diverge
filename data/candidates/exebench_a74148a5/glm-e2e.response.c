float getUniform(int a, int b, int c, float *d) {
    float temp = ((float)a * *d) + (float)b;
    int temp_i = (int)(temp / (float)c);
    temp = temp - (float)(temp_i * c);
    *d = temp / (float)c;
    return *d;
}