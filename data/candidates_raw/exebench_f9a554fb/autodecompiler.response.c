void add_llr(short int *llr, unsigned int length, short int *llr_sum)
{
    unsigned int i;
    for(i=0;i<length;i++)
        llr_sum[i] += llr[i];
}