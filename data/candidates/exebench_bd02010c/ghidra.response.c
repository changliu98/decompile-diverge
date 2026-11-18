void get_vector_modulo(int *v,int *m)

{
  int i;
  int *m_local;
  int *v_local;
  
  for (i = 0; i < 3; i = i + 1) {
    v[i] = v[i] % m[i];
    if (v[i] < 0) {
      v[i] = m[i] + v[i];
    }
  }
  return;
}