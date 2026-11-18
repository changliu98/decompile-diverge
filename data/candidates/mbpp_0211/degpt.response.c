int func0(int input_value)
{
  // Base case: if n is 1, return 1
  if (input_value == 1) {
    return 1;
  }
  else {
    // For n > 1, compute pow(_DAT_00102008, n - 2) and cast to int
    return (int)pow(base_constant,(double)(input_value - 2));
  }
}