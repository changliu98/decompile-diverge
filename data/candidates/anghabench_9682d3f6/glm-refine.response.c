void __cdecl bn_reverse(unsigned char *s, int len)
{
  int left = 0;
  int right = len - 1;

  while (left < right)
  {
    unsigned char temp = s[left];
    s[left] = s[right];
    s[right] = temp;
    
    left++;
    right--;
  }
}