float xCorrCoef(
    float *target,
    float *regressor,
    int subl
){
    int i;
    float ftmp1, ftmp2;

    ftmp1 = 0.0;
    ftmp2 = 0.0;


    for (i=0; i<subl; i++) {
        ftmp1 += target[i]*regressor[i];
        ftmp2 += regressor[i]*regressor[i];
    }

    if (ftmp1 > 0.0) {
        return (float)(ftmp1*ftmp1/ftmp2);
    }
    else {
        return (float)0.0;
    }
}