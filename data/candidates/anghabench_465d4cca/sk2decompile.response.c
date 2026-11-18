static int minor_to_index(int minor) {
  int index;
  index = minor >> MINORBITS;
  return index;
}