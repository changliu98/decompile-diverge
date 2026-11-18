char bppm_symbol(float *values)
{
  // Check if the first element exceeds the threshold
  if ((double)*values > DAT_00102008) return '.';
  // Check if the second element exceeds the threshold
  if ((double)values[1] > DAT_00102008) return '(';
  // Check if the third element exceeds the threshold
  if ((double)values[2] > DAT_00102008) return ')';
  // Check if the sum of the second and third elements is less than or equal to the first element
  if (values[1] + values[2] < *values || values[1] + values[2] == *values) {
    // If the first element is less than or equal to the sum, return ':'
    if (*values <= values[1] + values[2]) return ':';
    // Otherwise, return ','
    return ',';
  }
  // Check if the ratio of the second element to the sum of the second and third elements is less than or equal to the threshold
  if ((double)(values[1] / (values[1] + values[2])) <= DAT_00102008) {
    // Check if the ratio of the third element to the sum of the second and third elements is less than or equal to the threshold
    if ((double)(values[2] / (values[1] + values[2])) <= DAT_00102008) return '|';
    // Otherwise, return '}'
    return '}';
  }
  // Default return value
  return '{';
}