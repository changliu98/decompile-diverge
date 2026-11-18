// Sets the minimum and maximum cost bounds based on the index i
void cost_bounds(double *min_cost, double *max_cost, int index)
{
  // If the index i is greater than 0, set the cost bounds to predefined values
  if (0 < index) {
    *min_cost = DAT_00102010; // Assign the minimum cost bound
    *max_cost = DAT_00102008; // Assign the maximum cost bound
  }
}