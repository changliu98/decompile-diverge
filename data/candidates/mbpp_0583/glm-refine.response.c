int __cdecl func0(int num)
{
  int left_subtree_count;
  int i;
  int total_count;

  // Base case: A tree with 0 or 1 nodes has exactly 1 structural configuration.
  if ( num <= 1 )
    return 1;
    
  total_count = 0;
  
  // Iterate through all possible root positions in the sequence
  for ( i = 0; i < num; ++i )
  {
    // Recursively calculate the number of configurations for the left subtree
    left_subtree_count = func0(i);
    
    // Multiply by the configurations of the right subtree and accumulate
    total_count += func0(num - i - 1) * left_subtree_count;
  }
  
  return total_count;
}