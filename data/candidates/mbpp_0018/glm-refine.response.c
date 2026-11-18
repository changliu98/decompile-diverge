char *__cdecl func0(char *input_string, char *chars_to_remove)
{
  int *char_counts;    // Array tracking the presence of characters to remove
  char *mutable_str;   // Mutable copy of the input string
  int read_idx;        // Index for reading characters from the mutable string
  int write_idx;       // Index for writing kept characters back to the string
  char current_char;

  // Get the frequency/presence array for the characters to be removed
  char_counts = get_char_count_array(chars_to_remove);
  
  // Convert the input string to a mutable list (character array)
  mutable_str = str_to_list(input_string);

  // Iterate over the mutable string, filtering out specified characters
  for (read_idx = 0, write_idx = 0; mutable_str[read_idx]; ++read_idx)
  {
    current_char = mutable_str[read_idx];
    
    // If the character is not marked for removal, keep it
    if (!char_counts[current_char])
    {
      mutable_str[write_idx++] = current_char;
    }
  }

  // Convert the filtered list back into a string
  return lst_to_string(mutable_str, write_idx);
}