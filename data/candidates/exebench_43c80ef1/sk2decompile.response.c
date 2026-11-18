void IndexToData(int *data, int *index, int index_data) {
  *index = index_data & 3;
  *data = index_data >> 2;
  return;
}