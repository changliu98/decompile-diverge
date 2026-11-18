int __cdecl wacom_intuos_id_mangle(int tool_id)
{
  return tool_id & 0xFFF | (16 * (tool_id & 0xFFFFF000));
}