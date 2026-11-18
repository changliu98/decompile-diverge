void pick(int *pageCounter, int *rowCounter)
{
  // Increment the row counter
  *rowCounter = *rowCounter + 1;
  // If the row counter exceeds 767 (0x2ff), reset it to 0 and increment the page counter
  if (0x2ff < *rowCounter) {
    *pageCounter = *pageCounter + 1;
    *rowCounter = 0;
  }
  // If the page counter exceeds 179 (0xb3), reset it to 0
  if (0xb3 < *pageCounter) {
    *pageCounter = 0;
  }
}