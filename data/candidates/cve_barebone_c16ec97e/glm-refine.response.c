njs_int_t __cdecl njs_array_convert_to_slow_array(njs_vm_t *vm, njs_array_t *array)
{
  njs_value_t *val;
  njs_object_prop_t *prop;
  njs_value_t value;
  njs_value_t index;
  uint32_t length;
  uint32_t i;

  // Initialize a value descriptor pointing to the array object
  njs_set_array(&value, array);

  // Clear the lowest bit of the object's flags (likely marking it as a "slow" array)
  *(_BYTE *)&array->object &= ~1u;

  length = array->length;
  
  // Iterate over all elements in the fast array
  for ( i = 0; i < length; ++i )
  {
    // Check if the element is valid (data type != 7 typically implies NJS_UNDEFINED or similar invalid/empty slot)
    if ( array->start[i].data != 7 )
    {
      // Convert the integer index to a string (for property lookup)
      njs_uint32_to_string(&index, i);
      
      // Add the property to the object
      prop = njs_object_property_add(vm, &value, &index, 0);
      if ( !prop )
        return -1; // Return NJS_ERROR on allocation/insertion failure
        
      // Copy the value from the fast array slot into the newly created property
      val = &array->start[i];
      *(_QWORD *)&prop->value.data = val->data;
      prop->value.data.u.object = val->data.u.object;
    }
  }
  
  // Free the contiguous C-array memory used by the fast array
  njs_mp_free(vm->mem_pool, array->start);
  array->start = NULL;
  
  return 0; // Return NJS_OK
}