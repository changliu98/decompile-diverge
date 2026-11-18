float __cdecl pluck(float sig, float *q)
{
  // q acts as a struct representing a Karplus-Strong style delay line:
  // q[0] (idx):       Current write index (float)
  // q[1] (len):       Length of the delay line (float)
  // q[2] (weight1):   Feedback weight 1
  // q[3] (weight2):   Feedback weight 2
  // q[4] (buffer[0]): Start of the delay buffer
  
  float idx = q[0] + 1.0f;
  int ip_0;
  float temp;
  float v2;
  float v3;

  if ( idx > q[1] )
  {
    // Wrap the index if it exceeds the length of the delay line
    ip_0 = 4;
    idx = 4.0f;
    temp = q[4];
    v2 = q[2] * temp + sig;
    v3 = q[(int)q[1] - 1];
  }
  else
  {
    ip_0 = (int)idx;
    temp = q[ip_0];
    v2 = q[2] * temp + sig;
    v3 = q[ip_0 - 1];
  }

  q[0] = idx;
  q[ip_0] = q[3] * v3 + v2;
  
  return temp;
}