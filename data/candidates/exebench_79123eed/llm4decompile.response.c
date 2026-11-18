void quant_u_dec(int index, float *p_data, float qmin, float qmax, int nlev)
{
    *p_data = qmin + (qmax - qmin)/(nlev - 1)*index;
}