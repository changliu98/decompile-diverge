void combain_sorted_array( int *p, int *q, int *s)
{
 int *p_end = p + 5;
 int *q_end = q + 5;

 while( p<p_end && q<q_end )
 {
  if( *p <= *q)
  {
   if( p == p_end - 1 )
   {
    *s = *p;


    s++;
    while(q<q_end)
    {
     *s = *q;
     q++;
     s++;
    }
    break;
   }
   *s = *p;
   p++;
   s++;
  }
  else

  {
   if (q == q_end -1)
   {
    *s = *q;
    s++;
    while(p<p_end)
    {
     *s = *p;
     p++;
     s++;
    }
   }
   *s = *q;
   q++;
   s++;
  }
 }
}