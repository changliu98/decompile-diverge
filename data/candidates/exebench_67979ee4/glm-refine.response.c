void __cdecl quaternionComposition(
        float q01, float q02, float q03, float q04,
        float q11, float q12, float q13, float q14,
        float *q21, float *q22, float *q23, float *q24)
{
    // Hamilton product (quaternion composition) of q1 and q2
    *q21 = (q01 * q11) - (q02 * q12) - (q03 * q13) - (q04 * q14);
    *q22 = (q01 * q12) + (q02 * q11) + (q03 * q14) - (q04 * q13);
    *q23 = (q01 * q13) - (q02 * q14) + (q03 * q11) + (q04 * q12);
    *q24 = (q01 * q14) + (q02 * q13) - (q03 * q12) + (q04 * q11);
}