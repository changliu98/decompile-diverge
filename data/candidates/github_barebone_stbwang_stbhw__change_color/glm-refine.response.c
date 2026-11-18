int __cdecl stbhw__change_color(int old_color, int num_options, int *weights)
{
  int choice;
  int total_weight;
  int k;

  // If no weights are provided, pick a uniformly random color 
  // that is different from old_color.
  if (!weights)
    return ((rand() >> 4) % (num_options - 1) + 1 + old_color) % num_options;

  // Calculate the total weight of all available options (excluding the current color)
  total_weight = 0;
  for (k = 0; k < num_options; ++k)
  {
    if (k != old_color)
      total_weight += weights[k];
  }

  // Pick a random threshold within the total weight
  choice = (rand() >> 4) % total_weight;

  // Find the color that corresponds to the chosen threshold
  total_weight = 0;
  for (k = 0; k < num_options; ++k)
  {
    if (k != old_color)
    {
      total_weight += weights[k];
      if (choice < total_weight)
        break;
    }
  }

  // Safety check to ensure we successfully found a valid color
  assert(k < num_options);
  
  return k;
}