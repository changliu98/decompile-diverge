int bppm_symbol(struct shape *s)
{
 char c;

 if(s->a > 0.666) c = '.';
 else if(s->b > 0.666) c = '(';
 else if(s->c > 0.666) c = ')';
 else if(s->b + s->c < s->a) {
  if(s->b / (s->b + s->c) > 0.666) c = '{';
  else if(s->c / (s->b + s->c) > 0.666) c = '}';
  else c = '|';
 } else if(s->a > s->b + s->c) c = ',';
 else c = ':';

 return c;
}