int path_source_set(int *path, int source) {
  *path &= ~0x0e;
  *path |= (source & 0x0e);
  return *path;
}