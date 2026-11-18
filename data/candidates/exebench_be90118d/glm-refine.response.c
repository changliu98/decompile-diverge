void __cdecl pointerExample2(int *ptr1)
{
  // Dereference the pointer and assign the integer value 2 to the memory address it points to.
  // Semantics: Modifies the caller's variable in-place.
  *ptr1 = 2;
}