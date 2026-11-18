void __cdecl trataCoordenadas(char *linha, int *horizontal, int *vertical)
{
  // Convert the file (letter 'a'-'h') to a 0-based vertical index.
  // 'a' (ASCII 97) becomes 0, 'b' becomes 1, etc.
  *vertical = linha[0] - 'a';

  // Check if a second digit exists for the rank (e.g., "12" in "e12").
  // linha[3] checks for the second character of a two-digit number.
  // The `!= 10` checks that it isn't a newline character ('\n').
  if (linha[3] && linha[3] != '\n')
  {
    // Parse a two-digit rank: (linha[2] - '0') is the tens place, 
    // (linha[3] - '0') is the ones place. Subtract 1 to make it 0-indexed.
    *horizontal = (linha[2] - '0') * 10 + (linha[3] - '0') - 1;
  }
  else
  {
    // Parse a single-digit rank: (linha[2] - '0') - 1.
    // '1' (ASCII 49) becomes 0, '2' becomes 1, etc.
    *horizontal = linha[2] - '1';
  }
}