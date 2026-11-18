void bitrv208(float *a) {
    float temp1 = a[2];
    float temp2 = a[3];
    float temp3 = a[6];
    float temp4 = a[7];
    float temp5 = a[8];
    float temp6 = a[9];
    float temp7 = a[12];
    float temp8 = a[13];

    a[2] = temp5;
    a[3] = temp6;
    a[6] = temp7;
    a[7] = temp8;
    a[8] = temp1;
    a[9] = temp2;
    a[12] = temp3;
    a[13] = temp4;
}