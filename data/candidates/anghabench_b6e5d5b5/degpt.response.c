void packInt32(uint8_t *output_buffer, uint32_t input_value)
{
  // Store the least significant byte at the first position
  *output_buffer = (uint8_t)input_value;
  // Store the second least significant byte at the second position
  output_buffer[1] = (uint8_t)(input_value >> 8);
  // Store the third least significant byte at the third position
  output_buffer[2] = (uint8_t)(input_value >> 0x10);
  // Store the most significant byte at the fourth position
  output_buffer[3] = (uint8_t)(input_value >> 0x18);
}