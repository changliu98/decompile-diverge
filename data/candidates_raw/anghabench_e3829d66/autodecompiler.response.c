double biquad(double xin, double *coef, double *delay)
{
    double yout;
    double mem1, mem2, mem3, mem4, mem5, mem6, mem7;

    coef[0] = 0.06250470379874744 + 0.05468750000000000*xin;
    coef[1] = 0.06249999999999999 + 0.07421875000000000*xin;
    coef[2] = 0.06250470379874744 + 0.15625000000000000*xin;
    coef[3] = 0.06249999999999999 + 0.30859375000000000*xin;
    coef[4] = 0.06250470379874744 + 0.54687500000000000*xin;
    coef[5] = 0.06250470379874744 + 0.76562500000000000*xin;
    mem1 = coef[0] + coef[1] + coef[2] + coef[3] + coef[4] + coef[5] + coef[6] + 0.53515625000000000*xin;
    coef[6] = 0.11718750000000000*xin;
    yout = coef[7] * mem1;
    mem2 = coef[1] + coef[2] + coef[3] + coef[4] + coef[5] + coef[6] + coef[7];
    coef[7] = 0.11718750000000000*xin;
    yout += coef[8] * mem2;
    mem3 = coef[2] + coef[3] + coef[4] + coef[5] + coef[6] + coef[7] + coef[8];
    coef[8] = 0.11718750000000000*xin;
    yout += coef[9] * mem3;
    mem4 = coef[3] + coef[4] + coef[5] + coef[6] + coef[7] + coef[8] + coef[9];
    coef[9] = 0.11718750000000000*xin;
    yout += coef[10] * mem4;
    mem5 = coef[4] + coef[5] + coef[6] + coef[7] + coef[8] + coef[9] + coef[10];
    coef[10] = 0.11718750000000000*xin;
    yout += coef[11] * mem5;
    mem6 = coef[5] + coef[6] + coef[7] + coef[8] + coef[9] + coef[10] + coef[11];
    coef[11] = 0.11718750000000000*xin;
    yout += coef[12] * mem6;
    mem7 = coef[6] + coef[7] + coef[8] + coef[9] + coef[10] + coef[11] + coef[12];
    coef[12] = 0.11718750000000000*xin;
    yout += coef[13] * mem7;
    return yout;
}