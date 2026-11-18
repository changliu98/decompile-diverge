void __cdecl func0(const char *text, char *out)
{
  size_t i;

  for (i = 0; text[i] != '\0'; ++i)
  {
    // Shift each lowercase letter by 4 positions (Caesar cipher)
    out[i] = ((text[i] - 'a') + 4) % 26 + 'a';
  }
  
  out[i] = '\0';
}