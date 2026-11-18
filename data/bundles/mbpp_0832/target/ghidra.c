int func0(char *input)

{
  int iVar1;
  int number_1;
  int number;
  int i;
  int index;
  char temp [256];
  int max;
  char *input_local;
  
  max = 0;
  index = 0;
  for (i = 0; input[i] != '\0'; i = i + 1) {
    if ((input[i] < '0') || ('9' < input[i])) {
      if (index != 0) {
        temp[index] = '\0';
        iVar1 = atoi(temp);
        if (max < iVar1) {
          max = iVar1;
        }
        index = 0;
      }
    }
    else {
      temp[index] = input[i];
      index = index + 1;
    }
  }
  if (index != 0) {
    temp[index] = '\0';
    iVar1 = atoi(temp);
    if (max < iVar1) {
      max = iVar1;
    }
  }
  return max;
}