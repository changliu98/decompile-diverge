int func0(char **strings, int count, char *prefix, char ***out)
{
 int i;
 int prefix_length;
 int out_count;

 prefix_length = strlen(prefix);
 *out = malloc((size_t)count * sizeof(char *));
 out_count = 0;
 for (i = 0; i < count; i++) {
  if (!strncmp(strings[i], prefix, (size_t)prefix_length)) {
   (*out)[out_count] = strings[i];
   out_count++;
  }
 }
 return out_count;
}