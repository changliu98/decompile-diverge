int* func0(char* music_string, int* count)
{
 int i;
 int* output;
 int output_size;
 int output_capacity;
 char current[3];
 char* music_string_local;
 int music_string_length;

 output = NULL;
 output_size = 0;
 output_capacity = 0;
 memset(current, 0, 3);

 music_string_length = strlen(music_string);
 music_string_local = malloc((size_t)(music_string_length + 2));
 strcpy(music_string_local, music_string);
 strcat(music_string_local, " ");

 for (i = 0; i < music_string_length + 1; i++)
 {
  if (music_string_local[i] == ' ')
  {
   if (!strcmp(current, "o"))
   {
    if (output_size == output_capacity)
    {
     output_capacity = (output_capacity > 0 ? output_capacity * 2 : 4);
     output = realloc(output, (size_t)(output_capacity * sizeof(int)));
    }

    output[output_size++] = 4;
   }

   if (!strcmp(current, "o|"))
   {
    if (output_size == output_capacity)
    {
     output_capacity = (output_capacity > 0 ? output_capacity * 2 : 4);
     output = realloc(output, (size_t)(output_capacity * sizeof(int)));
    }

    output[output_size++] = 2;
   }

   if (!strcmp(current, ".|"))
   {
    if (output_size == output_capacity)
    {
     output_capacity = (output_capacity > 0 ? output_capacity * 2 : 4);
     output = realloc(output, (size_t)(output_capacity * sizeof(int)));
    }

    output[output_size++] = 1;
   }

   strcpy(current, "");
  }
  else
  {
   size_t current_length = strlen(current);

   if (current_length < 3 - 1)
   {
    current[current_length] = music_string_local[i];
    current[current_length + 1] = '\0';
   }
  }
 }

 free(music_string_local);

 *count = output_size;
 return output;
}