// Increments the integer value pointed to by n by 1
// Adds the constant value DAT_00102004 to the float value pointed to by a
// Increments the character value pointed to by c by 4 (0x04)
void changeValues(int *count,float *value,char *character)
{
  *count = *count + 1;
  *value = DAT_00102004 + *value;
  *character = *character + '\x04';
}