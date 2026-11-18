int func0(char *input1, char *input2) {
 int i;
 int count = 0;
 int inputLength = strlen(input1);

 for (i = 0; i < inputLength; i++) {
  if (input1[i] != input2[i]) {
   count++;
  }
 }

 int result;

 if (count % 2 == 0) {
  result = count / 2;
 } else {
  result = -1;
 }

 return result;
}