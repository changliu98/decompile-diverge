void mm_us(float *m1, float *m2, float *mout)
{
    int i, j, k;
    float su;
    for(i=0;i<4;++i)
        for(j=0;j<4;++j) {
            su=.0;
            for(k=0;k<4;++k)
                su += m1[i*4 +k] * m2[k*4 +j];
            mout[i*4 +j]=su;
        }
}