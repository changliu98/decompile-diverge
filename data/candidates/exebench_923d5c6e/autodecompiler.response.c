void ne_pre_filter16_double(double *new_state, double *old_state, int *r)
{
    double temp[16];

    temp[15] = old_state[0] - old_state[15];
    temp[14] = old_state[1] - old_state[14];
    temp[13] = old_state[2] - old_state[13];
    temp[12] = old_state[3] - old_state[12];
    temp[11] = old_state[4] - old_state[11];
    temp[10] = old_state[5] - old_state[10];
    temp[9] = old_state[6] - old_state[9];
    temp[8] = old_state[7] - old_state[8];
    temp[7] = old_state[7] - temp[8]/2;
    temp[6] = old_state[6] - temp[9]/2;
    temp[5] = old_state[5] - temp[10]/2;
    temp[4] = old_state[4] - temp[11]/2;
    temp[3] = old_state[3] - temp[12]/2;
    temp[2] = old_state[2] - temp[13]/2;
    temp[1] = old_state[1] - temp[14]/2;
    temp[0] = old_state[0] - temp[15]/2;

    temp[8] = temp[8]*r[0]/16;
    temp[9] = temp[9]*r[1]/16;
    temp[10] = temp[10]*r[2]/16;
    temp[11] = temp[11]*r[3]/16;
    temp[12] = temp[12]*r[4]/16;
    temp[13] = temp[13]*r[5]/16;
    temp[14] = temp[14]*r[6]/16;
    temp[15] = temp[15]*r[7]/16;

    temp[0] += temp[14]*r[14]/16;
    temp[1] += temp[0]*r[21]/16;
    temp[1] += temp[13]*r[13]/16;
    temp[2] += temp[1]*r[20]/16;
    temp[3] += temp[12]*r[12]/16;
    temp[4] += temp[2]*r[19]/16;
    temp[5] += temp[11]*r[11]/16;
    temp[6] += temp[3]*r[18]/16;
    temp[7] += temp[10]*r[10]/16;
    temp[8] += temp[4]*r[17]/16;
    temp[9] += temp[5]*r[16]/16;
    temp[10] += temp[6]*r[15]/16;
    temp[11] += temp[7]*r[8]/16;
    temp[12] += temp[8]*r[9]/16;
    temp[13] += temp[9]*r[14]/16;
    temp[14] += temp[15]*r[7]/16;
    temp[15] += temp[14]*r[0]/16;

    temp[0] += temp[15]/2;
    new_state[0] = temp[0];
    temp[1] += temp[14]/2;
    new_state[1] = temp[1];
    temp[2] += temp[13]/2;
    new_state[2] = temp[2];
    temp[3] += temp[12]/2;
    new_state[3] = temp[3];
    temp[4] += temp[11]/2;
    new_state[4] = temp[4];
    temp[5] += temp[10]/2;
    new_state[5] = temp[5];
    temp[6] += temp[9]/2;
    new_state[6] = temp[6];
    temp[7] += temp[8]/2;
    new_state[7] = temp[7];

    new_state[8] = temp[7] - temp[8];
    new_state[9] = temp[6] - temp[9];
    new_state[10] = temp[5] - temp[10];
    new_state[11] = temp[4] - temp[11];
    new_state[12] = temp[3] - temp[12];
    new_state[13] = temp[2] - temp[13];
    new_state[14] = temp[1] - temp[14];
    new_state[15] = temp[0] - temp[15];
}