





char bppm_symbol(float *x)
{
  if( x[0] > 0.667 ) return '.';
  if( x[1] > 0.667 ) return '(';
  if( x[2] > 0.667 ) return ')';
  if( (x[1]+x[2]) > x[0] ) {
    if( (x[1]/(x[1]+x[2])) > 0.667) return '{';
    if( (x[2]/(x[1]+x[2])) > 0.667) return '}';
    else return '|';
  }
  if( x[0] > (x[1]+x[2]) ) return ',';
  return ':';
}
