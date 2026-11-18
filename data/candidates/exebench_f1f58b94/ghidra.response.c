void sort4_sorting_network_simple_swap(short *d)

{
  short sVar1;
  short sVar2;
  short b_4;
  short a_4;
  short b_3;
  short a_3;
  short b_2;
  short a_2;
  short b_1;
  short a_1;
  short b;
  short a;
  short *d_local;
  
  if (*d < d[1]) {
    sVar1 = *d;
  }
  else {
    sVar1 = d[1];
  }
  if (*d < d[1]) {
    sVar2 = d[1];
  }
  else {
    sVar2 = *d;
  }
  *d = sVar1;
  d[1] = sVar2;
  if (d[2] < d[3]) {
    sVar1 = d[2];
  }
  else {
    sVar1 = d[3];
  }
  if (d[2] < d[3]) {
    sVar2 = d[3];
  }
  else {
    sVar2 = d[2];
  }
  d[2] = sVar1;
  d[3] = sVar2;
  if (*d < d[2]) {
    sVar1 = *d;
  }
  else {
    sVar1 = d[2];
  }
  if (*d < d[2]) {
    sVar2 = d[2];
  }
  else {
    sVar2 = *d;
  }
  *d = sVar1;
  d[2] = sVar2;
  if (d[1] < d[3]) {
    sVar1 = d[1];
  }
  else {
    sVar1 = d[3];
  }
  if (d[1] < d[3]) {
    sVar2 = d[3];
  }
  else {
    sVar2 = d[1];
  }
  d[1] = sVar1;
  d[3] = sVar2;
  if (d[1] < d[2]) {
    sVar1 = d[1];
  }
  else {
    sVar1 = d[2];
  }
  if (d[1] < d[2]) {
    sVar2 = d[2];
  }
  else {
    sVar2 = d[1];
  }
  d[1] = sVar1;
  d[2] = sVar2;
  return;
}