njs_jump_off_t njs_vmcode_typeof(njs_vm_t *virtual_machine, njs_value_t *input_value, njs_value_t *invalid_value)
{
  njs_value_t *type_string_ptr;
  
  // Retrieve the type string value corresponding to the input value's type from the predefined types array
  type_string_ptr = njs_vmcode_typeof::types[input_value->data.type];
  // Copy the main part of the type value to the VM's return value
  *(undefined8 *)&virtual_machine->retval = *(undefined8 *)type_string_ptr;
  // Copy the union member 'u' from the type value's internal structure to the VM's return value
  virtual_machine->retval.data.u = ((anon_union_8_16_5fa0025e_for_u *)((long)type_string_ptr + 8))->u;
  // Return the jump offset to proceed to the next instruction
  return 0x18;
}