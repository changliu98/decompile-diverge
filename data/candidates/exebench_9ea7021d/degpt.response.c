void AdjustSpan(int *startIndex, int *length, int maxLength)
{
  // If the start index is negative, adjust the length and reset start to 0
  if (*startIndex < 0) {
    *length += *startIndex;
    *startIndex = 0;
  }
  // If the span exceeds the maximum allowed value, truncate the length
  if (maxLength < *startIndex + *length) {
    *length = maxLength - *startIndex;
  }
}