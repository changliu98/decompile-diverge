int __cdecl nogr_prompt_dir(const char *prompt, int *px, int *py)
{
  if (px) *px = 1; // Defensive check (semantically safe as px is guaranteed non-null by caller in most cases)
  if (py) *py = 0; // Defensive check
  return 0;        // 0 typically indicates success in standard C conventions
}