int __cdecl arrayFind(int elem, int *list, int length)
{
  int i;
  int j;

  // Search for the element in the array
  for (i = 0; i < length; ++i)
  {
    if (list[i] == elem)
      break;
  }

  // If the element was not found, return -1
  if (i >= length)
    return -1;

  // Shift all elements before the found index to the right by 1
  for (j = 0; j < i; ++j)
    list[i - j] = list[i - j - 1];

  // Move the found element to the front of the array
  *list = elem;

  return 0;
}