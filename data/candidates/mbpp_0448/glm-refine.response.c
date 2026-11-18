int __cdecl func0(int n)
{
  int next_val; // [rsp+0h] [rbp-1Ch]
  int sum;      // [rsp+4h] [rbp-18h]
  int v3;       // [rsp+8h] [rbp-14h]  (formerly c)
  int v2;       // [rsp+Ch] [rbp-10h]  (formerly b)
  int v1;       // [rsp+10h] [rbp-Ch]  (formerly a)
  int i;        // [rsp+14h] [rbp-8h]  (formerly na)

  // Base cases for n = 0, 1, 2
  switch ( n )
  {
    case 0:
      return 3;
    case 1:
      return 3;
    case 2:
      return 5;
  }

  // Initial sequence values corresponding to n=1, n=2, and n=3
  i = n;
  v1 = 3;  // a
  v2 = 0;  // b
  v3 = 2;  // c
  sum = 5; // sum for n=2

  while ( i > 2 )
  {
    // Calculate the next value in the sequence
    next_val = v2 + v1;
    
    // Add the newly generated value to the running total
    sum += next_val;
    
    // Shift the window for the next iteration
    v1 = v2;
    v2 = v3;
    v3 = next_val;
    
    --i;
  }
  
  return sum;
}