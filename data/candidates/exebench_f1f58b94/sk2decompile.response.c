void sort4_sorting_network_simple_swap(short *data) {
  short tmp0, tmp1;
  tmp0 = (data[0] < data[1]) ? data[0] : data[1];
  tmp1 = (data[0] < data[1]) ? data[1] : data[0];
  data[0] = tmp0;
  data[1] = tmp1;
  tmp0 = (data[2] < data[3]) ? data[2] : data[3];
  tmp1 = (data[2] < data[3]) ? data[3] : data[2];
  data[2] = tmp0;
  data[3] = tmp1;
  tmp0 = (data[0] < data[2]) ? data[0] : data[2];
  tmp1 = (data[0] < data[2]) ? data[2] : data[0];
  data[0] = tmp0;
  data[2] = tmp1;
  tmp0 = (data[1] < data[3]) ? data[1] : data[3];
  tmp1 = (data[1] < data[3]) ? data[3] : data[1];
  data[1] = tmp0;
  data[3] = tmp1;
  tmp0 = (data[1] < data[2]) ? data[1] : data[2];
  tmp1 = (data[1] < data[2]) ? data[2] : data[1];
  data[1] = tmp0;
  data[2] = tmp1;
}