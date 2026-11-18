void caesar(char *string, int encode) {
 int key = (encode) ? 5 : 21;
 size_t len = strlen(string);
 size_t i;
 for (i = 0; i < len; i++) {
  int new_letter = ((string[i] - 'a' + key) % 26) + 'a';
  string[i] = (char)new_letter;
 }
}