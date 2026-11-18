njs_int_t
njs_promise_perform_then(njs_vm_t *vm, njs_value_t *value,
    njs_value_t *fulfilled, njs_value_t *rejected,
    njs_promise_capability_t *capability)
{
 njs_promise_t *promise;
 njs_promise_data_t *data;
 njs_promise_reaction_t *reaction[2];
 njs_value_t arguments[2];
 njs_function_t *function;
 njs_int_t ret;

 if (fulfilled->type != NJS_DATA_TYPE_FUNCTION)
  fulfilled = &njs_value_undefined;
 if (rejected->type != NJS_DATA_TYPE_FUNCTION)
  rejected = &njs_value_undefined;

 promise = (njs_promise_t *) value->data.ptr;
 data = (njs_promise_data_t *) promise->data;

 reaction[0] = njs_mp_alloc(vm->mem_pool, sizeof(njs_promise_reaction_t));
 if (reaction[0] == NULL) {
  njs_memory_error(vm);
  return -1;
 }

 reaction[0]->capability = capability;
 reaction[0]->handler = *fulfilled;
 reaction[0]->type = 1;

 reaction[1] = njs_mp_alloc(vm->mem_pool, sizeof(njs_promise_reaction_t));
 if (reaction[1] == NULL) {
  njs_memory_error(vm);
  return -1;
 }

 reaction[1]->capability = capability;
 reaction[1]->handler = *rejected;
 reaction[1]->type = 2;

 if (!data->is_handled) {
  reaction[0]->next = data->fulfilled_reactions.next;
  reaction[0]->next->prev = &reaction[0]->next;
  reaction[0]->prev = &data->fulfilled_reactions;
  data->fulfilled_reactions.next = &reaction[0]->next;

  reaction[1]->next = data->rejected_reactions.next;
  reaction[1]->next->prev = &reaction[1]->next;
  reaction[1]->prev = &data->rejected_reactions;
  data->rejected_reactions.next = &reaction[1]->next;
 } else {
  function = njs_promise_create_function(vm, 80);
  function->u.lambda = njs_promise_reaction_job;

  if (data->is_handled == 2) {
   njs_set_data(&arguments[0], reaction[1], NJS_DATA_TAG_ANY);

   ret = njs_promise_host_rejection_tracker(vm, promise,
       NJS_PROMISE_HANDLE);
   if (ret != 0)
    return ret;
  } else {
   njs_set_data(&arguments[0], reaction[0], NJS_DATA_TAG_ANY);
  }

  arguments[1] = data->result;

  ret = njs_promise_add_event(vm, function, arguments, 2);
  if (ret != 0)
   return ret;
 }

 data->is_then = 1;

 if (capability != NULL) {
  njs_vm_retval_set(vm, &capability->promise);
 } else {
  njs_vm_retval_set(vm, &njs_value_undefined);
 }

 return 0;
}