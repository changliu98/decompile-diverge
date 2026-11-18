void iw_restrict_to_range(int min, int max, int *val)
{
 if(*val<min) *val=min;
 else if(*val>max) *val=max;
}