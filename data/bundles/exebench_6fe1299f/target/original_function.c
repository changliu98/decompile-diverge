void quant_u(float *p_data, int *p_index, float qmin, float qmax, int nlev)

{
register int i, j;
register float step, qbnd, *p_in;

 p_in = p_data;


 step = (qmax - qmin) / (nlev - 1);


 qbnd = qmin + (0.5 * step);
 j = nlev - 1;
 for (i = 0; i < j; i ++ ) {
  if (*p_in < qbnd)
   break;
  else
   qbnd += step;
 }


 *p_in = qmin + (i * step);
 *p_index = i;

}