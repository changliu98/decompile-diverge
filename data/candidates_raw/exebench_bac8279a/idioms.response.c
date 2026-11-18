char get_char(float *vec)
{
  if (vec[0] > 0.667)
    return '.';
  if (vec[1] > 0.667)
    return '(';
  if (vec[2] > 0.667)
    return ')';
  if (vec[0] < vec[1]+vec[2])
  {
    if (vec[1]/vec[1]+vec[2] > 0.667)
      return '{';
    if (vec[2]/vec[1]+vec[2] > 0.667)
      return '}';
    return '|';
  }
  if (vec[1]+vec[2] < vec[0])
    return ',';
  if (vec[0] < vec[1]+vec[2])
    return ':';
  return '.';
}