// Function to calculate the proportion of positive, negative, and zero values in an integer array
void summary(int *numbers, int size, double *positive_ratio, double *negative_ratio, double *zero_ratio)
{
  int index;
  int zero_counter = 0; // Counter for zero values
  int negative_counter = 0;  // Counter for negative values
  int positive_counter = 0;  // Counter for positive values
  
  // Iterate through the array to count positive, negative, and zero values
  for (index = 0; index < size; index = index + 1) {
    if (numbers[index] < 0) {
      negative_counter = negative_counter + 1; // Increment negative count
    }
    else if (numbers[index] == 0) {
      zero_counter = zero_counter + 1; // Increment zero count
    }
    else {
      positive_counter = positive_counter + 1; // Increment positive count
    }
  }
  // Calculate and store the proportion of positive values
  *positive_ratio = (double)positive_counter / (double)size;
  // Calculate and store the proportion of negative values
  *negative_ratio = (double)negative_counter / (double)size;
  // Calculate and store the proportion of zero values
  *zero_ratio = (double)zero_counter / (double)size;
}