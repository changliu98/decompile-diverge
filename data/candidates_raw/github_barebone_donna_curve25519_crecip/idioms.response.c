void ipowm100(unsigned long *r, unsigned long *a)
{
  unsigned long t[10]; unsigned long t1[10]; unsigned long t2[10]; unsigned long t3[10]; unsigned long t4[10]; unsigned long t5[10]; unsigned long t6[10]; unsigned long t7[10];
  unsigned long *ra = r;
  unsigned long *aa = a;
  unsigned int i;
  mul(t, aa, a);
  mul(t1, t, a);
  mul(t2, t1, a);
  mul(t3, t2, t);
  mul(t, t3, t);
  mul(t1, t, t3);
  mul(t, t1, t);
  mul(t1, t, t);
  mul(t2, t1, t);
  mul(t, t2, t);
  mul(t1, t, t);
  for (i = 2; i < 10; i += 2)
  {
    mul(t, t1, t);
    mul(t1, t, t);
  }
  mul(t2, t1, t);
  mul(t, t2, t);
  mul(t1, t, t);
  for (i = 2; i < 20; i += 2)
  {
    mul(t, t1, t);
    mul(t1, t, t);
  }
  mul(t2, t1, t);
  mul(t, t2, t);
  mul(t1, t, t);
  for (i = 2; i < 10; i += 2)
  {
    mul(t, t1, t);
    mul(t1, t, t);
  }
  mul(t2, t1, t);
  mul(t, t2, t);
  mul(t1, t, t);
  for (i = 2; i < 50; i += 2)
  {
    mul(t, t1, t);
    mul(t1, t, t);
  }
  mul(t2, t1, t);
  mul(t, t2, t);
  mul(t1, t, t);
  for (i = 2; i < 100; i += 2)
  {
    mul(t, t1, t);
    mul(t1, t, t);
  }
  mul(t2, t1, t);
  mul(t, t2, t);
  mul(t1, t, t);
  for (i = 2; i < 50; i += 2)
  {
    mul(t, t1, t);
    mul(t1, t, t);
  }
  mul(t2, t1, t);
  mul(t, t2, t);
  mul(t1, t, t);
  mul(t2, t1, t);
  mul(t, t2, t);
  mul(t1, t, t);
  mul(ra, t1, t3);
}