int __cdecl stbhw__weighted(int num_options, int *weights)
{
  int choice;
  int total = 0;
  int k;

  // Calculate the sum of all weights
  for (k = 0; k < num_options; ++k)
    total += weights[k];

  // (rand() >> 4) improves randomness by dropping the least significant bits,
  // which are often weak in standard LCG random number generators.
  choice = (rand() >> 4) % total;

  // Find the chosen option based on the random value
  total = 0;
  for (k = 0; k < num_options; ++k)
  {
    total += weights[k];
    if (choice < total)
      break;
  }

  // Safety check to ensure we found a valid option
  assert(k < num_options);

  return k;
}