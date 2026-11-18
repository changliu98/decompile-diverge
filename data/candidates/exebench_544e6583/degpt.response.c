// Swaps the values of two integers using XOR bitwise operations
void SWAP(int *first_value, int *second_value)
{
  // Step 1: a now holds the XOR of original a and b
  *first_value = *first_value ^ *second_value;
  
  // Step 2: b now holds the original value of a (since b ^ (a ^ b) = a)
  *second_value = *first_value ^ *second_value;
  
  // Step 3: a now holds the original value of b (since (a ^ b) ^ a = b)
  *first_value = *first_value ^ *second_value;
}