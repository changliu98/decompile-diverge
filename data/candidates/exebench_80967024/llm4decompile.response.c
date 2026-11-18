void upcoef_len_cal(int sigInLength,
                     int filterLen,
                     int stride,
                     int *sigOutLength,
                     int *sigOutLengthDefault)
{

    int count = 0;

    *sigOutLength = sigInLength;
    *sigOutLengthDefault = sigInLength;
    for (count = 0; count < stride; count++) {
        *sigOutLengthDefault = (*sigOutLengthDefault * 2) + filterLen - 1;
        *sigOutLength = (*sigOutLength * 2) + filterLen - 2;
    }
}