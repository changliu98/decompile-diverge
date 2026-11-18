void transposeMatrix(float *m1, float *m2)
{
    float temp;

    m1[0] = m2[0];
    m1[5] = m2[5];
    m1[10] = m2[10];
    m1[15] = m2[15];

    temp = m2[4];
    m1[4] = m2[1];
    m1[1] = temp;

    temp = m2[8];
    m1[8] = m2[2];
    m1[2] = temp;

    temp = m2[12];
    m1[12] = m2[3];
    m1[3] = temp;

    temp = m2[9];
    m1[9] = m2[6];
    m1[6] = temp;

    temp = m2[13];
    m1[13] = m2[7];
    m1[7] = temp;

    temp = m2[14];
    m1[14] = m2[11];
    m1[11] = temp;
}