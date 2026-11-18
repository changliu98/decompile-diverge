char* func0(char* street) {
  int length = strlen(street);
  if (length > 4 && strcmp(&street[length - 4], "Road") == 0) {
    street[length - 4] = '\0';
    strcat(street, "Rd.");
  }
  return street;
}