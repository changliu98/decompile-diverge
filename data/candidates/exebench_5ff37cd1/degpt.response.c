// Decrements the latitude by 1 and increments the longitude by 1
void go_south_east(int *latitude, int *longitude)
{
  // Move one unit south (decrease latitude)
  *latitude = *latitude - 1;
  // Move one unit east (increase longitude)
  *longitude = *longitude + 1;
}