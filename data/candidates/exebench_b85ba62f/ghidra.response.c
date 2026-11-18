unsigned_long
rational_best_approximation
          (unsigned_long given_numerator,unsigned_long given_denominator,unsigned_long max_numerator
          ,unsigned_long max_denominator,unsigned_long *best_numerator,
          unsigned_long *best_denominator)

{
  unsigned_long uVar1;
  ulong uVar2;
  unsigned_long uVar3;
  ulong uVar4;
  unsigned_long a;
  unsigned_long t;
  unsigned_long d1;
  unsigned_long n1;
  unsigned_long d0;
  unsigned_long n0;
  unsigned_long d;
  unsigned_long n;
  unsigned_long *best_denominator_local;
  unsigned_long *best_numerator_local;
  unsigned_long max_denominator_local;
  unsigned_long max_numerator_local;
  unsigned_long given_denominator_local;
  unsigned_long given_numerator_local;
  
  n0 = 0;
  d0 = 1;
  n1 = 1;
  d1 = 0;
  d = given_denominator;
  n = given_numerator;
  while ((n1 <= max_numerator && (d1 <= max_denominator))) {
    if (d == 0) goto LAB_001012da;
    uVar2 = n / d;
    uVar4 = n % d;
    n = d;
    uVar3 = n0 + uVar2 * n1;
    n0 = n1;
    uVar1 = d1;
    d1 = d0 + uVar2 * d1;
    n1 = uVar3;
    d0 = uVar1;
    d = uVar4;
  }
  n1 = n0;
  d1 = d0;
LAB_001012da:
  *best_numerator = n1;
  *best_denominator = d1;
  return 0;
}