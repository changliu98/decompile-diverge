int dp(int n) {
 int v[n+1];
 v[0] = 0; v[1] = 1;
 for (int i = 2; ; i++) {
  if (i > n) break;
  v[i] = v[i/2] + v[i/3] + v[i/4];
  if (v[i] < i) v[i] = i;
 }
 return v[n];
}