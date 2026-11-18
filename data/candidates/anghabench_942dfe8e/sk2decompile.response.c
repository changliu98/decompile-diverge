int prot2perm(int prot) {
  int perm = 0;
  if (prot & 1) perm |= 4;
  if (prot & 2) perm |= 2;
  if (prot & 4) perm |= 1;
  return perm;
}