char *make_string(int p, int q, int r, int s)
{
 char *str;
 int i, j, k, l, m = 0;
 if(p > 0) m += p;
 if(q > 0) m += q;
 if(r > 0) m += r;
 if(s > 0) m += s;

 str = (char *)malloc((m + 1) * sizeof(char));
 if(str == NULL)
 {
  perror("Failed to allocate memory");
  exit(1);
 }

 for(i = 0; i < p; i++) { str[m++] = 'p'; }
 for(j = 0; j < q; j++) { str[m++] = 'q'; }
 for(k = 0; k < r; k++) { str[m++] = 'r'; }
 for(l = 0; l < s; l++) { str[m++] = 's'; }
 str[m] = '\0';
 return str;
}