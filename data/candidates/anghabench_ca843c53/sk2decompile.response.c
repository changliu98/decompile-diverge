static int maya_pb_route_shift(int i) {
  static int shift[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  return shift[i % 10];
}