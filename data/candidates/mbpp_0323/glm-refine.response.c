void __cdecl func0(int *arr, int n)
{
  int index;          // [rsp+Ch] [rbp-14h]  Current index iterating through the array
  int out_of_place;   // [rsp+10h] [rbp-10h] Index of the last known out-of-place element (-1 if none)

  out_of_place = -1;
  for ( index = 0; index < n; ++index )
  {
    // If we have a pending out-of-place element, check if the current element 
    // has the opposite sign, which means we can fix the sequence via rotation.
    if ( out_of_place >= 0 && 
         (arr[index] >= 0 && arr[out_of_place] < 0 || arr[index] < 0 && arr[out_of_place] >= 0) )
    {
      right_rotate(arr, n, out_of_place, index);
      
      // After rotation, determine if there are still out-of-place elements in the rotated subarray.
      if ( index - out_of_place <= 2 )
        out_of_place = -1; // Distance is small enough; no elements are out of place anymore.
      else
        out_of_place += 2; // Skip the newly placed pair and check the next element.
    }
    
    // If no element is currently marked as out-of-place, check if the current element violates 
    // the alternating sign condition (positive at even index, negative at odd index).
    if ( out_of_place == -1 && 
         (arr[index] >= 0 && !(index % 2) || arr[index] < 0 && index % 2 == 1) )
    {
      out_of_place = index;
    }
  }
}