void myArrayDiv(float *outArray, float divisor, float *inArray) {
    for (int i = 0; i < 5; i++) {
        outArray[i] = inArray[i] / divisor;
    }
}