void quaternionComposition(float q01, float q02, float q03, float q04, float q11, float q12, float q13, float q14, float *q21, float *q22, float *q23, float *q24)
{
    *q21 = -q04 * q14 - q03 * q13 + q01 * q11 - q02 * q12;
    *q22 = -q04 * q13 + q03 * q14 + q01 * q12 + q02 * q11;
    *q23 = q04 * q12 + q03 * q11 + q01 * q13 - q02 * q14;
    *q24 = q04 * q11 - q03 * q12 + q01 * q14 + q02 * q13;
}