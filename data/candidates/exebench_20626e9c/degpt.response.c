void unscale(double *probability, uint iteration_count)
{
  // Iterate 'times' number of iterations
  for (uint counter = 0; counter < iteration_count; counter++) {
    // Multiply the probability value by a constant scaling factor (DAT_00102010)
    *probability = scaling_factor * *probability;
  }
}