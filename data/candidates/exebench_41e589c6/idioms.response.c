void find_ibm(int char1, int char2, int *outchar1, int *outchar2)
{
  int char1a;
  int char2a;
  int char1b;
  int char2b;
  char1 = char1 - 161;
  char2 = char2 - 127;
  char1a = char1 * 157 + char2 - 63;
  char1a = (char1a < 0) ? 0 : (char1a > 126) ? 126 : char1a;
  char1b = char1a - (char1a / 188 * 188);
  char2 = char1a / 188 * 188 + 63;
  char2a = (char2 < 0) ? 0 : (char2 > 126) ? 126 : char2;
  char2 = char2a - (char2a / 188 * 188);
  char1a = char1a / 188 * 188 + 137;
  char1 = char1a - (char1a / 188 * 188);
  char1 = (char1 < 0) ? 0 : (char1 > 126) ? 126 : char1;
  char1a = (char1a / 188);
  char1 = (char1 + 128);
  char2 = (char2 + 128);
  *outchar1 = char1;
  *outchar2 = char2;
}