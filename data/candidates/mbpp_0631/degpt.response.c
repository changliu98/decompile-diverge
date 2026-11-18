void func0(char *inputString)
{
  // Iterate through the string until the null terminator is reached
  for (int currentIndex = 0; inputString[currentIndex] != '\0'; currentIndex++) {
    // Check if the current character is a space
    if (inputString[currentIndex] == ' ') {
      // Replace the space with an underscore
      inputString[currentIndex] = '_';
    }
  }
}