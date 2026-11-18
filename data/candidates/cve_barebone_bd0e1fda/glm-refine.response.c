njs_jump_off_t __cdecl njs_vmcode_array(njs_vm_t *vm, u_char *pc)
{
  njs_array_t *array;
  uint32_t length;

  // Allocate an array. 
  // *((_QWORD *)pc + 2) extracts the 64-bit operand from the bytecode instruction (pc + 16).
  array = njs_array_alloc(vm, 0LL, *((_QWORD *)pc + 2), 8u);
  if ( !array )
    return -1LL;

  // pc[24] checks a boolean flag in the bytecode instruction to determine if the array should be initialized.
  if ( pc[24] )
  {
    njs_value_t *value = array->start;
    length = array->length;
    
    // Initialize each element. 
    // *(_BYTE *)&value->data = 7 sets the type tag of the njs_value_t to 7 (likely NJS_UNDEFINED or similar).
    do
    {
      *(_BYTE *)&value->data = 7;
      ++value;
      --length;
    }
    while ( length );
  }
  else
  {
    // If the flag is false, override the allocated length to 0.
    array->length = 0;
  }

  // Store the newly created array as the return value of the VM.
  njs_set_array(&vm->retval, array);
  
  // Return the size of the instruction to advance the program counter.
  return 32LL;
}