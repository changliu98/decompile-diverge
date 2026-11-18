njs_jump_off_t __cdecl njs_vmcode_typeof(njs_vm_t *vm, njs_value_t *value, njs_value_t *invld)
{
  vm->retval.data = *(struct {__int32 type : 8;uint8_t truth;uint16_t magic16;uint32_t magic32;union {double number;njs_object_t *object;njs_array_t *array;njs_array_buffer_t *array_buffer;njs_typed_array_t *typed_array;njs_data_view_t *data_view;njs_object_value_t *object_value;njs_function_t *function;njs_function_lambda_t *lambda;njs_regexp_t *regexp;njs_date_t *date;njs_promise_t *promise;njs_prop_handler_t prop_handler;njs_value_t *value;njs_property_next_t *next;void *data;} u;} *)*(&njs_vmcode_typeof_types + *(_BYTE *)&value->data);
  return 24LL;
}