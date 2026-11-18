void __cdecl sort4_sorting_network_simple_swap(short *d)
{
  // Stage 1: Compare-Swap d[0] and d[1]
  short min01 = (*d < d[1]) ? *d : d[1];
  short max01 = (*d < d[1]) ? d[1] : *d;
  *d = min01;
  d[1] = max01;

  // Stage 2: Compare-Swap d[2] and d[3]
  short min23 = (d[2] < d[3]) ? d[2] : d[3];
  short max23 = (d[2] < d[3]) ? d[3] : d[2];
  d[2] = min23;
  d[3] = max23;

  // Stage 3: Compare-Swap d[0] and d[2]
  short min02 = (*d < d[2]) ? *d : d[2];
  short max02 = (*d < d[2]) ? d[2] : *d;
  *d = min02;
  d[2] = max02;

  // Stage 4: Compare-Swap d[1] and d[3]
  short min13 = (d[1] < d[3]) ? d[1] : d[3];
  short max13 = (d[1] < d[3]) ? d[3] : d[1];
  d[1] = min13;
  d[3] = max13;

  // Stage 5: Compare-Swap d[1] and d[2]
  short min12 = (d[1] < d[2]) ? d[1] : d[2];
  short max12 = (d[1] < d[2]) ? d[2] : d[1];
  d[1] = min12;
  d[2] = max12;
}