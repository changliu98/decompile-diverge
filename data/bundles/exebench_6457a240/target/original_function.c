static void peneira (int m, int v[]) {

   int p = 1, f = 2, t = v[1];

   while (f <= m) {
      if (f < m && v[f] < v[f+1]) ++f;
      if (t >= v[f]) break;
      v[p] = v[f];
      p = f, f = 2*p;
   }
   v[p] = t;
}