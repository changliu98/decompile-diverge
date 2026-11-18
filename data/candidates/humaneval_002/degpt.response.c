// Returns the fractional part of the input number.
// Casts the float to an int to truncate the decimal part,
// then subtracts the integer part from the original number.
float func0(float input_value)
{
  return input_value - (float)(int)input_value;
}