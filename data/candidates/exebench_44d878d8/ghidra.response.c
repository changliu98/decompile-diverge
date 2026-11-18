void qr_getSize(uint m,uint n,uint *Q_size,uint *R_size,uint *permSize)

{
  uint *permSize_local;
  uint *R_size_local;
  uint *Q_size_local;
  uint n_local;
  uint m_local;
  
  Q_size[1] = m;
  *Q_size = m;
  *permSize = n;
  *R_size = m;
  R_size[1] = n;
  return;
}