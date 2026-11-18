void split(long long int *a, long long int *b, long long int s, long long int n, long long int m) {
 if(n < 17) {
  long long int i, j, k, l;
  for(i = s; i < s + n; i++) {
   k = 1;
   long long int min = b[a[i] + m];
   for(j = i + 1; j < s + n; j++) {
    if(min > b[a[j] + m]) {
     min = b[a[j] + m];
     k = 0;
    }
    if(b[a[j] + m] == min) {
     long long int temp = a[i + k];
     a[i + k] = a[j];
     a[j] = temp;
     k++;
    }
   }
   for(j = 0; j < k; j++) {
    b[a[i + j]] = s + k - 1;
   }
   if(k == 1)
    a[i] = -1;
   i = i + k - 1;
  }
  return;
 }
 long long int p, q, r, t, u, v, x, c, l, i, j;
 p = 0;
 q = 0;
 t = b[a[s + n / 2] + m];
 u = 0;
 v = 0;
 for(i = s; i < s + n; i++) {
  if(b[a[i] + m] < t)
   p++;
  if(b[a[i] + m] == t)
   q++;
 }
 p = p + s;
 q = p + q;
 v = s;
 r = 0;
 for(i = s; i < p; i++) {
  if(b[a[i] + m] < t) {
   continue;
  } else if(b[a[i] + m] == t) {
   long long int temp = a[i];
   a[i] = a[p + r];
   a[p + r] = temp;
   r++;
  } else {
   long long int temp = a[i];
   a[i] = a[v + u];
   a[v + u] = temp;
   u++;
  }
 }
 while(p + r < q) {
  if(b[a[p + r] + m] == t) {
   r++;
  } else {
   long long int temp = a[p + r];
   a[p + r] = a[v + u];
   a[v + u] = temp;
   u++;
  }
 }
 if(s < p)
  split(a, b, s, p - s, m);
 for(i = 0; i < q - p; i++) {
  b[a[p + i]] = q - 1;
 }
 if(p == q - 1)
  a[p] = -1;
 if(q < s + n)
  split(a, b, q, s + n - q, m);
}