void bitrv208(struct fft_data *data)
{
  double tmpr; double tmpi;
  tmpr = data->data[0];
  tmpi = data->data[1];
  data->data[0] = data->data[8];
  data->data[1] = data->data[9];
  data->data[2] = data->data[10];
  data->data[3] = data->data[11];
  data->data[4] = data->data[12];
  data->data[5] = data->data[13];
  data->data[6] = data->data[14];
  data->data[7] = data->data[15];
  data->data[8] = tmpr;
  data->data[9] = tmpi;
  data->data[10] = data->data[2];
  data->data[11] = data->data[3];
  data->data[12] = data->data[4];
  data->data[13] = data->data[5];
  data->data[14] = data->data[6];
  data->data[15] = data->data[7];
}