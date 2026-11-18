void shift_array(char array[]) {
 int element = 0;
 while (array[element] != '\0')
  array[element++] += 5;
}