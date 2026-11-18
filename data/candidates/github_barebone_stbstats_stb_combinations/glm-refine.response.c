int __cdecl stb_combinations(int n, int t, int ***combinations)
{
  int *c;
  int **comb;
  int nCr;
  int current = 0;
  int j, x, jb;

  // Allocate combination index array with 3 extra padding elements 
  // (used as boundary conditions in the algorithm)
  c = (int *)calloc(t + 3, 4uLL);
  
  // Calculate nCr = n! / (t! * (n - t)!)
  double fact_n = stb_factorial(n);
  double fact_t = stb_factorial(t);
  nCr = (int)(fact_n / (fact_t * stb_factorial(n - t)));
  
  // Allocate a matrix of size nCr x t to store the combinations
  comb = (int **)stb_allocmat(nCr, t, 4uLL);

  // Initialize the combination array
  // c[1..t] stores the current combination (0-indexed values)
  for (j = 1; j <= t; ++j)
    c[j] = j - 1;
  c[t + 1] = n; // Upper boundary
  c[t + 2] = 0; // Lower boundary

  // Generate combinations using a modified lexicographic algorithm
  for (j = t; ; j = jb - 1)
  {
    // Visit the current combination
    stb_visit(c, t, &comb, current++);

    // Decrement elements down to 0 and visit each state
    while (j > 0)
    {
      c[j] = j;
      --j;
      stb_visit(c, t, &comb, current++);
    }

    // Increment the first element until it reaches the second element
    while (c[1] + 1 < c[2])
    {
      ++c[1];
      stb_visit(c, t, &comb, current++);
    }

    // Find the next element to increment
    jb = 2;
    c[1] = 0;
    for (x = c[2] + 1; x == c[jb + 1]; x = c[jb] + 1)
    {
      ++jb;
      c[jb - 1] = jb - 2;
    }

    // Termination condition: if we've pushed the increment past 't', we are done
    if (jb > t)
      break;

    c[jb] = x;
  }

  // Output the generated combinations array
  *combinations = comb;
  
  free(c);
  return nCr;
}