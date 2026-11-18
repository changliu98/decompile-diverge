void shift_array(char *array)

{
  int element;
  char *array_local;
  
  element = 0;
  while (array[element] != '\0') {
    array[element] = array[element] + '\x05';
    element = element + 1;
  }
  return;
}