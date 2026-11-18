// Encodes a single character value into its Base64 representation.
// If the input value is less than '@' (ASCII 64), it returns the corresponding
// Base64 character from the encoding table. Otherwise, it returns '=' as a
// placeholder or padding character.
char base64_encode_value(char input_value)
{
  // Check if the value is within the valid Base64 encoding range (0-63)
  // '@' is ASCII 64, so values < 64 are valid indices into the encoding table
  return input_value < '@' ? base64_encode_value::encoding[(int)input_value] : '=';
}