double compute_average(int number_values, int sum)
{
 double average = (double)sum / (double)number_values;

 return round(average * 100) / 100;
}