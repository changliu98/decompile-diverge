char *__cdecl func0(char *street)
{
  size_t length = strlen(street);

  if (length > 4 && !strcmp(&street[length - 4], "Road"))
  {
    street[length - 4] = '\0';
    strcat(street, "Rd.");
  }

  return street;
}