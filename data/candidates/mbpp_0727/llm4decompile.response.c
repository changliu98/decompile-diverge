char *func0(char *S) {
 int i,j;
 for (i = 0, j = 0; i < strlen(S); i++) {
  if (S[i] & 0x8)
   func0::result[j++] = S[i];
 }
 func0::result[j] = '\0';
 return func0::result;
}