char* func0(char in[256]) {
 char * vowels = "AEIOUaeiou";
 char * result;
 int i;
 size_t len = strlen(in);
 for (i = len - 2; i > 1; i--) {
  if (strchr(vowels, in[i]) && !strchr(vowels, in[i + 1]) && !strchr(vowels, in[i - 1])) {
   func0_out[0] = in[i];
   result = func0_out;
   goto end;
  }
 }
 func0_out[0] = '\0';
 result = func0_out;
end:
 return result;
}