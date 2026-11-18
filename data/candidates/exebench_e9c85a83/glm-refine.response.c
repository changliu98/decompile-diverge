void __cdecl triggers_bug(int *p)
{
  // 0xDEADBEEF is a classic magic number used by compilers and debuggers 
  // (like Microsoft's CRT / Microsoft Visual C++) to mark uninitialized memory.
  // Writing this value to a pointer often triggers automated bug-tracking tools 
  // or assertions during runtime if the memory is improperly accessed.
  *p = 0xDEADBEEF; 
}