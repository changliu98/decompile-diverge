// Copies the contents of the dice array to the copy array
void copy_dice(int *source_array, int *destination_array)
{
  // Iterate through each element of the 6-element arrays
  for (int index = 0; index < 6; index++) {
    // Assign the value from dice to the corresponding position in copy
    destination_array[index] = source_array[index];
  }
}