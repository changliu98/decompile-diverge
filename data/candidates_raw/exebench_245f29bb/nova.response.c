float func0(float *number) {
    float32 number32 = *number;
    number32 = number32;
    return *((float *)&number32);
}