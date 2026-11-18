static int walNextHash(int iHash) {
  iHash++;
  iHash &= (WAL_HASH_SIZE - 1);
  return iHash;
}