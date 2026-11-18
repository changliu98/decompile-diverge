void separateString(char *input, char *upperOutput, char *lowerOutput, char *numOutput, char *specialOutput) {
 int i;
 int length = strlen(input);
 int upperCount = 0, lowerCount = 0, numCount = 0, specialCount = 0;

 for (i = 0; i < length; i++) {
  if (isupper(input[i])) {
   upperOutput[upperCount++] = input[i];
  } else if (islower(input[i])) {
   lowerOutput[lowerCount++] = input[i];
  } else if (isdigit(input[i])) {
   numOutput[numCount++] = input[i];
  } else if (input[i] == ',' || input[i] == '.' || input[i] == '!' || input[i] == '?') {
   specialOutput[specialCount++] = input[i];
  }
 }

 upperOutput[upperCount] = '\0';
 lowerOutput[lowerCount] = '\0';
 numOutput[numCount] = '\0';
 specialOutput[specialCount] = '\0';
}