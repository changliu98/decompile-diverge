void __cdecl combain_sorted_array(int *p, int *q, int *s)
{
  int *pa = p;
  int *qa = q;
  int *p_end = p + 5;
  int *q_end = q + 5;

  while (pa < p_end && qa < q_end)
  {
    if (*pa > *qa)
    {
      if (qa == q + 4)
      {
        *s++ = *qa;
        while (pa < p_end)
          *s++ = *pa++;
      }
      *s++ = *qa++;
    }
    else
    {
      if (pa == p + 4)
      {
        *s = *pa;
        int *sb = s + 1;
        while (qa < q_end)
          *sb++ = *qa++;
        return;
      }
      *s++ = *pa++;
    }
  }
}