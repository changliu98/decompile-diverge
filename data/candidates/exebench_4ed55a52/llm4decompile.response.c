void shift_array(char array[])
{
 int index = 0;
 while (array[index] != '\0')
 {
  array[index] = array[index] + 5;
  index++;
 }
}