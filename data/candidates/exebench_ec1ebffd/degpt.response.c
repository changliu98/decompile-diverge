/*
 * slevmar_box_check - Check if lower bounds are strictly less than upper bounds
 *
 * @lb: Pointer to the array of lower bounds
 * @ub: Pointer to the array of upper bounds
 * @m:  Number of elements in the bounds arrays
 *
 * Returns 1 if all lower bounds are strictly less than corresponding upper bounds,
 *         0 otherwise (including if lb or ub is NULL or if any ub[i] <= lb[i])
 */
int slevmar_box_check(float *lower_bounds, float *upper_bounds, int num_bounds)
{
  int index;
  /* Check if both bound arrays are provided */
  if (lower_bounds && upper_bounds) {
    /* Iterate through each bound pair */
    for (index = 0; index < num_bounds; index++) {
      /* If any upper bound is not strictly greater than the lower bound, return invalid */
      if (upper_bounds[index] <= lower_bounds[index]) {
        return 0;
      }
    }
  }
  /* Bounds are valid (or arrays were NULL) */
  return 1;
}