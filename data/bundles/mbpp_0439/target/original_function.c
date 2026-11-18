int func0(int* L, int size) {
  char temp[256] = {0};
  char numStr[20];
  for (int i = 0; i < size; i++) {
    sprintf(numStr, "%d", L[i]);
    strcat(temp, numStr);
  }
  return atoi(temp);
}