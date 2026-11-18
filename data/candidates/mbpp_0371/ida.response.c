int __cdecl func0(int *A, int left_element, int right_element)
{
  int mid; // [rsp+4h] [rbp-1Ch]

  if ( left_element > right_element )
    return left_element;
  mid = (right_element - left_element) / 2 + left_element;
  if ( A[mid] == mid )
    return func0(A, mid + 1, right_element);
  else
    return func0(A, left_element, mid - 1);
}