char * func0(char *street)
{
  // Calculate the length of the input street string
  size_t streetLength = strlen(street);
  // Check if the string length is greater than 4 and ends with "Road"
  if (4 < streetLength && strcmp(street + streetLength - 4, "Road") == 0) {
    // Null-terminate the string at the position before "Road"
    street[streetLength - 4] = '\0';
    // Append "Rd." to the truncated string
    strcat(street, "Rd.");
  }
  // Return the modified street string
  return street;
}