float __cdecl hpluck(float xin, float *q)
{
  int ip_0;
  float temp;
  float v2;
  float v3;

  // q[0] acts as a phase accumulator / read-write index
  q[0] += 1.0f;
  
  if (q[1] < q[0]) 
  {
    ip_0 = 20;
    q[0] = 20.0f;
  } 
  else 
  {
    ip_0 = (int)q[0];
  }

  // Lowpass filter / decay stage
  v2 = (1.0f - q[8]) * q[ip_0] + q[8] * q[7];
  q[7] = v2;

  // Pick-up position interpolation (Karplus-Strong "pluck position")
  temp = q[9] * (q[2] * q[ip_0] + q[3] * q[6]);
  
  // Shift delay line state
  q[6] = q[ip_0];
  
  // q[10] is a float whose sign bit is flipped to negate it (-q[10])
  float neg_q10 = -q[10];
  
  // Calculate next delay line sample
  q[ip_0] = neg_q10 * q[5] + q[10] * temp + q[4];
  
  // Inject excitation input
  v3 = xin + q[ip_0];
  q[ip_0] = v3;
  
  // Update filter history states
  q[5] = v3;
  q[4] = temp;
  
  return q[7];
}