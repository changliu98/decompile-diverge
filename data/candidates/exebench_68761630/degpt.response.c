// Atomically performs a bitwise OR operation on the integer pointed to by p with value v.
// Uses LOCK/UNLOCK to ensure thread safety during the read-modify-write operation.
void a_or(int *target_value, int value_to_or)
{
  LOCK();
  *target_value |= value_to_or;
  UNLOCK();
}