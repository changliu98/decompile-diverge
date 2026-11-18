int func0(char *value)
{
 double f = atof(value);
 double d;

 if (f >= 0.0) {
  d = floor(f + 0.5);
 } else {
  d = ceil(f - 0.5);
 }

 return (int)d;
}