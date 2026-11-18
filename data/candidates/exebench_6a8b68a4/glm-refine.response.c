// Objective: Sets the value of the provided integer pointer to 30.
// Note: The original calling convention is __cdecl, meaning the caller cleans up the stack.
void __cdecl SetHealthToFull(int *ptr)
{
  // Dereference the pointer and assign the value 30.
  // In a reverse engineering context, '30' could represent max health, 
  // a boolean true state, or a specific game/engine state ID.
  *ptr = 30;
}