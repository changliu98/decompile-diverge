char *func0(int p, int q, int r, int s)
{
 int i, j, k, l;
 int total = 0;
 char *str;

 if (p > 0)
  total += p;
 if (q > 0)
  total += q;
 if (r > 0)
  total += r;
 if (s > 0)
  total += s;

 str = malloc((size_t)(total + 1));
 if (!str) {
  perror("Failed to allocate memory");
  exit(1);
 }

 j = 0;
 for (i = 0; i < p; i++)
  str[j++] = 'p';
 for (i = 0; i < q; i++)
  str[j++] = 'q';
 for (i = 0; i < r; i++)
  str[j++] = 'r';
 for (i = 0; i < s; i++)
  str[j++] = 's';
 str[j] = '\0';

 return str;
}