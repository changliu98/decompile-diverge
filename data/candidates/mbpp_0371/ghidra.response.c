int func0(int *A,int left_element,int right_element)

{
  int iVar1;
  int mid;
  int right_element_local;
  int left_element_local;
  int *A_local;
  int local_c;
  
  local_c = left_element;
  if (left_element <= right_element) {
    iVar1 = left_element + (right_element - left_element) / 2;
    if (A[iVar1] == iVar1) {
      local_c = func0(A,iVar1 + 1,right_element);
    }
    else {
      local_c = func0(A,left_element,iVar1 + -1);
    }
  }
  return local_c;
}