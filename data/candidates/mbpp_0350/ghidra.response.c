int func0(char *s)

{
  size_t sVar1;
  int i_1;
  int i;
  int arr [26];
  int n;
  int maxOcc;
  char *s_local;
  
  maxOcc = 0;
  sVar1 = strlen(s);
  memset(arr,0,0x68);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    arr[s[i] + -0x61] = arr[s[i] + -0x61] + 1;
  }
  for (i_1 = 0; i_1 < 0x1a; i_1 = i_1 + 1) {
    if (maxOcc < arr[i_1]) {
      maxOcc = arr[i_1];
    }
  }
  return (int)sVar1 - maxOcc;
}