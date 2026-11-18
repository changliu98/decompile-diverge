void update_size(int *size1, int *size2)
{
  if (*size1 > *size2) {
    *size1 = *size1 / 2;
    *size2 = *size2 * 2;
  } else {
    *size1 = *size1 * 2;
    *size2 = *size2 / 2;
  }
}