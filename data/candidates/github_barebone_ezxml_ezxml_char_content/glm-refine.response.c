void __cdecl ezxml_char_content(ezxml_root_t root, char *s, size_t len, char t)
{
  ezxml_t xml;
  char *decoded_str;
  size_t decoded_len;
  size_t current_len;
  char *new_txt;

  xml = root->cur;
  
  // Bail out if there's no active XML element, no name, or no content to process
  if (!xml || !xml->name || !len)
    return;

  // Ensure the string is null-terminated and decode the entities
  s[len] = '\0';
  decoded_str = ezxml_decode(s, root->ent, t);
  decoded_len = strlen(decoded_str) + 1; // +1 for the null terminator

  if (*xml->txt) 
  {
    // The XML node already has text, so we need to append to it
    current_len = strlen(xml->txt);
    
    if ((xml->flags & 0x40) != 0) 
    {
      // If the 0x40 flag is set, the memory is dynamically allocated and safe to realloc
      new_txt = (char *)realloc(xml->txt, decoded_len + current_len);
    }
    else 
    {
      // Otherwise, allocate new memory and copy the existing text over
      new_txt = (char *)malloc(decoded_len + current_len);
      strcpy(new_txt, xml->txt);
    }
    
    xml->txt = new_txt;
    strcpy(&xml->txt[current_len], decoded_str);
    
    // If ezxml_decode allocated a new string, free it to prevent memory leaks
    if (decoded_str != s)
      free(decoded_str);
  }
  else 
  {
    // The XML node has no existing text, so just assign the decoded string directly
    xml->txt = decoded_str;
  }

  // If the text pointer is no longer the original string `s`, mark the 0x40 flag
  // This indicates that xml->txt is now independently allocated and owned by the node
  if (xml->txt != s)
    ezxml_set_flag(xml, 0x40);
}