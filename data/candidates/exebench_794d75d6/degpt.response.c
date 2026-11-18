void AdjustSpan2(int *startIndex, int *endIndex, int *length, int maxLength)
{
  // If the start index is negative, adjust the length and end index
  // to account for the negative offset, and set start to 0
  if (*startIndex < 0) {
    *length += *startIndex;
    *endIndex -= *startIndex;
    *startIndex = 0;
  }
  // If the span extends beyond the maximum allowed value,
  // truncate the length so that the span ends at max
  if (maxLength < *startIndex + *length) {
    *length = maxLength - *startIndex;
  }
}