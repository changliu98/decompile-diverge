int binary_search(int *item_list, int size, int item)
{
  int first = 0;
  int last = size - 1;
  int found = 0;
  int mid;
  int direction;
  while (1) {
    direction = 0;
    if (first <= last) {
      direction = (found == 0) ? 1 : -1;
    }
    if (direction == 0) {
      break;
    }
    mid = (first + last) / 2;
    if (item_list[mid] == item) {
      found = 1;
    } else if (item < item_list[mid]) {
      last = mid - 1;
    } else {
      first = mid + 1;
    }
  }
  return found;
}