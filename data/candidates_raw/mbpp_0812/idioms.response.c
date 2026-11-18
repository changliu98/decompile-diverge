char *format_street(char *street)
{
  int len = strlen(street);
  if (len > 4 && !strcmp(street + len - 4, "Road")) {
    street[len - 4] = '\0';
    strcat(street, "Rd.");
  }
  return street;
}