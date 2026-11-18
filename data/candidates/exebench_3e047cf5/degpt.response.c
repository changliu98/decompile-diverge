// Converts a DNA sequence to RNA by replacing all 'T'/'t' characters with 'U'/'u'
void ToRNA(char *dnaSequence)
{
  // Iterate through the string until the null terminator is reached
  for (; *dnaSequence; dnaSequence++) {
    // Replace uppercase 'T' with 'U'
    if (*dnaSequence == 'T') *dnaSequence = 'U';
    // Replace lowercase 't' with 'u'
    else if (*dnaSequence == 't') *dnaSequence = 'u';
  }
}