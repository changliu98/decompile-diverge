// Extracts the lower 6 bits of y (masking with 0x5f) and stores the result in *x.
// Returns the original value of y.
uint and_peep2_qi(uint input_value, uint *output_buffer)
{
  *output_buffer = input_value & 0x5f; // Store the masked value (lower 6 bits) in *x
  return input_value;      // Return the original unmodified value of y
}