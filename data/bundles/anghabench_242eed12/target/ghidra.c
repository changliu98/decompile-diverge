int wacom_intuos_id_mangle(int tool_id)

{
  int tool_id_local;
  
  return (tool_id & 0xfffff000U) << 4 | tool_id & 0xfffU;
}