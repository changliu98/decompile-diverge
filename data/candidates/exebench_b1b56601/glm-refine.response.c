void __cdecl nexper(int n, int *a, int *mtc, int *even)
{
  int i, j, l, m, s, d, i1, ib, iaa, m_val, j1, j2;

  if ( !*mtc ) 
  {
    // Initialization: Generate the first permutation (1, 2, ..., n)
    for ( i = 1; i <= n; ++i )
      a[i] = i;
    *mtc = 1;
    *even = 1;
    return;
  }

  if ( *even == 1 ) 
  {
    // If the previous permutation was even, swap the first two elements
    iaa = a[1];
    a[1] = a[2];
    a[2] = iaa;
    *even = 0;

    // Check for termination condition
    if ( a[n] == 1 && a[1] == n % 2 + 2 ) 
    {
      if ( n > 3 ) 
      {
        for ( i = 1; i <= n - 3; ++i ) 
        {
          if ( a[i + 1] != a[i] + 1 )
            return;
        }
      }
      *mtc = 0;
    }
    return;
  }

  // If the previous permutation was odd, find the next permutation
  s = 0;
  i1 = 2;
  while ( 1 ) 
  {
    if ( i1 > n ) 
    {
      *mtc = 0;
      return;
    }
    
    iaa = a[i1];
    ib = i1 - 1;
    d = 0;
    
    for ( j = 1; j <= ib; ++j ) 
    {
      if ( a[j] > iaa )
        ++d;
    }
    
    s += d;
    if ( d != (s % 2) * ib )
      break;
      
    ++i1;
  }

  m_val = (n + 1) * ((s + 1) % 2);
  l = 0; // Safe initialization
  
  for ( j = 1; j <= ib; ++j ) 
  {
    j1 = a[j] - iaa;
    j2 = a[j] - m_val;
    // Equivalent to: (j1 >= 0) XOR (j2 >= 0)
    if ( (j1 >= 0 && j2 < 0) || (j1 < 0 && j2 >= 0) ) 
    {
      m_val = a[j];
      l = j;
    }
  }

  a[l] = iaa;
  a[i1] = m_val;
  *even = 1;
}