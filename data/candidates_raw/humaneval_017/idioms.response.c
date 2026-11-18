int *get_note_list(char *music, int *count)
{
  int *out = ((void *)0);
  int size = 0;
  int capacity = 0;
  char current[3] = {0};
  int music_string_length = strlen(music) + 1;
  char *temp_music_string = (char *)malloc(music_string_length * sizeof(char));
  strcpy(temp_music_string, music);
  strcat(temp_music_string, " ");
  int i = 0;
  for (i = 0; i < music_string_length; i++)
  {
    if (temp_music_string[i] == ' ')
    {
      if (strcmp(current, "o") == 0)
      {
        if (size == capacity)
        {
          int new_capacity = (capacity == 0) ? 4 : capacity * 2;
          capacity = new_capacity;
          out = (int *)realloc(out, capacity * sizeof(int));
        }
        out[size++] = 4;
      }
      if (strcmp(current, "o|") == 0)
      {
        if (size == capacity)
        {
          int new_capacity = (capacity == 0) ? 4 : capacity * 2;
          capacity = new_capacity;
          out = (int *)realloc(out, capacity * sizeof(int));
        }
        out[size++] = 2;
      }
      if (strcmp(current, ".|") == 0)
      {
        if (size == capacity)
        {
          int new_capacity = (capacity == 0) ? 4 : capacity * 2;
          capacity = new_capacity;
          out = (int *)realloc(out, capacity * sizeof(int));
        }
        out[size++] = 1;
      }
      strcpy(current, "");
    }
    else
    {
      int current_length = strlen(current);
      if (current_length < 2)
      {
        current[current_length] = temp_music_string[i];
        current[current_length + 1] = '\0';
      }
    }
  }
  free(temp_music_string);
  *count = size;
  return out;
}