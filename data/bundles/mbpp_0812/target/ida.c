char *__cdecl func0(char *street)
{
  int length; // [rsp+4h] [rbp-Ch]

  length = strlen(street);
  if ( length > 4 && !strcmp(&street[length - 4], "Road") )
  {
    street[length - 4] = 0;
    strcat(street, "Rd.");
  }
  return street;
}