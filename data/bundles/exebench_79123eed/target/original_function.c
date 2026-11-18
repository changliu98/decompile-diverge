void quant_u_dec(int index, float *p_data,float qmin, float qmax, int nlev)

{
register float step;


 step = (qmax - qmin) / (nlev - 1);


 *p_data = qmin + (index * step);

}