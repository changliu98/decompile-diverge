bool _hasDuplicates(int* array, int size) {
  bool hasDuplicates = false;
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (array[i] == array[j]) {
        hasDuplicates = true;
        break;
      }
    }
    if (hasDuplicates & 1) {
      break;
    }
  }
  return hasDuplicates;
}