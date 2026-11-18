int matCalcCross(const double v1[3], const double v2[3], double vr[3])
{

    vr[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    vr[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    vr[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    return 0;
}