char *__cdecl func0(const char *s)
{
  int len;            // Length of the input string
  int write_pos;      // Current write offset in the global buffer
  int i;              // Loop counter

  len = strlen(s);
  write_pos = 0;

  // Ascending loop: Appends numbers from 1 to len
  for ( i = 1; i <= len; ++i )
    write_pos += sprintf(&g_func0_res[write_pos], "%d", (unsigned int)i);

  // Descending loop: Appends numbers from len-1 down to 1
  for ( i = len - 1; i > 0; --i )
    write_pos += sprintf(&g_func0_res[write_pos], "%d", (unsigned int)i);

  // Null-terminate the final string
  g_func0_res[write_pos] = 0;

  return g_func0_res;
}