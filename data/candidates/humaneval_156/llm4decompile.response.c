void func0(int number, char *result)
{
 int i = 0;
 int num[13];
 char *rep[13];

 memcpy(rep, "\000M\000CM\000D\000CD\000C\000XC\000L\000XL\000X\000IX\000V\000IV\000I\000", sizeof(char *) * 13);
 memcpy(num, "\0001000\000900\000500\000400\000100\00090\00050\00040\00010\0009\0005\0004\0001", sizeof(int) * 13);

 *result = 0;

 while (number > 0) {
  while (number / num[i] > 0) {
   strcat(result, rep[i]);
   number -= num[i];
  }
  if (number > 0)
   i++;
 }
}