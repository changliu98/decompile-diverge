void R16SRFFT(float *input, float *output)
{
    float f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15;
    float t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

    f0 = input[0];
    f1 = input[1];
    f2 = input[2];
    f3 = input[3];
    f4 = input[4];
    f5 = input[5];
    f6 = input[6];
    f7 = input[7];
    f8 = input[8];
    f9 = input[9];
    f10 = input[10];
    f11 = input[11];
    f12 = input[12];
    f13 = input[13];
    f14 = input[14];
    f15 = input[15];

    t0 = f0 + f8;
    t1 = f1 + f9;
    t2 = f2 + f10;
    t3 = f3 + f11;
    t4 = f4 + f12;
    t5 = f5 + f13;
    t6 = f6 + f14;
    t7 = f7 + f15;

    t8 = f0 - f8;
    t9 = f1 - f9;
    t10 = f2 - f10;
    t11 = f3 - f11;
    t12 = f4 - f12;
    t13 = f5 - f13;
    t14 = f6 - f14;
    t15 = f7 - f15;

    f0 = t0 + t4;
    f1 = t1 + t5;
    f2 = t2 + t6;
    f3 = t3 + t7;
    f4 = t8 - t12;
    f5 = t9 - t13;
    f6 = t10 - t14;
    f7 = t11 - t15;

    t0 = t0 - t4;
    t1 = t1 - t5;
    t2 = t2 - t6;
    t3 = t3 - t7;
    t4 = t8 + t12;
    t5 = t9 + t13;
    t6 = t10 + t14;
    t7 = t11 + t15;

    t8 = t9 - t1;
    t9 = t11 - t3;
    t10 = t13 - t5;
    t11 = t15 - t7;

    t12 = t10 + t8;
    t13 = t12 + t12;
    t14 = t10 - t8;
    t15 = t14 - t14;

    t8 = t11 + t9;
    t9 = t11 - t9;
    t10 = t13 - t8;
    t11 = t15 - t9;

    output[0] = f0 + f2;
    output[8] = f0 - f2;
    output[4] = f4 + f6;
    output[12] = f4 - f6;
    output[2] = f0 + f6;
    output[10] = f0 - f6;
    output[6] = f4 - f2;
    output[14] = f4 + f2;

    output[1] = f1 + t4;
    output[15] = f1 - t4;
    output[9] = f5 + t8;
    output[7] = f5 - t8;
    output[3] = f1 + t8;
    output[11] = f1 - t8;
    output[5] = f5 - t4;
    output[13] = f5 + t4;
}