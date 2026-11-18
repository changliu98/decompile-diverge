njs_int_t __cdecl njs_promise_perform_then(
        njs_vm_t *vm,
        njs_value_t *value,
        njs_value_t *fulfilled,
        njs_value_t *rejected,
        njs_promise_capability_t *capability)
{
  njs_promise_reaction_t *rejected_reaction; // [rsp+8h] [rbp-88h]
  njs_promise_reaction_t *fulfilled_reaction; // [rsp+10h] [rbp-80h]
  njs_promise_data_t *data; // [rsp+18h] [rbp-78h]
  njs_function_t *function; // [rsp+20h] [rbp-70h]
  njs_promise_t *promise; // [rsp+28h] [rbp-68h]
  njs_value_t arguments[2]; // [rsp+30h] [rbp-60h] BYREF
  njs_int_t ret; // [rsp+5Ch] [rbp-34h]
  njs_promise_capability_t *capabilitya; // [rsp+60h] [rbp-30h]
  njs_value_t *rejecteda; // [rsp+68h] [rbp-28h]
  njs_value_t *fulfilleda; // [rsp+70h] [rbp-20h]
  njs_value_t *valuea; // [rsp+78h] [rbp-18h]
  njs_vm_t *vma; // [rsp+80h] [rbp-10h]

  vma = vm;
  valuea = value;
  fulfilleda = fulfilled;
  rejecteda = rejected;
  capabilitya = capability;
  if ( fulfilled->data != 18 )
    fulfilleda = (njs_value_t *)&njs_value_undefined;
  if ( rejecteda->data != 18 )
    rejecteda = (njs_value_t *)&njs_value_undefined;
  promise = valuea->data.u.object_value;
  data = (njs_promise_data_t *)promise->value.data.u.object;
  fulfilled_reaction = (njs_promise_reaction_t *)njs_mp_alloc(vma->mem_pool, 0x30uLL);
  if ( fulfilled_reaction
    && (fulfilled_reaction->capability = capabilitya,
        fulfilled_reaction->handler = (njs_value_t)fulfilleda->data,
        fulfilled_reaction->type = NJS_PROMISE_FULFILL,
        (rejected_reaction = (njs_promise_reaction_t *)njs_mp_alloc(vma->mem_pool, 0x30uLL)) != 0LL) )
  {
    rejected_reaction->capability = capabilitya;
    rejected_reaction->handler = (njs_value_t)rejecteda->data;
    rejected_reaction->type = NJS_PROMISE_REJECTED;
    if ( data->state )
    {
      function = njs_promise_create_function(vma, 0x50uLL);
      function->u.lambda = njs_promise_reaction_job;
      if ( data->state == NJS_PROMISE_REJECTED )
      {
        njs_set_data(arguments, rejected_reaction, NJS_DATA_TAG_ANY);
        ret = njs_promise_host_rejection_tracker(vma, promise, NJS_PROMISE_HANDLE);
        if ( ret )
          return ret;
      }
      else
      {
        njs_set_data(arguments, fulfilled_reaction, NJS_DATA_TAG_ANY);
      }
      arguments[1] = data->result;
      ret = njs_promise_add_event(vma, function, arguments, 2u);
      if ( ret )
        return ret;
    }
    else
    {
      fulfilled_reaction->link.prev = data->fulfill_queue.head.prev;
      fulfilled_reaction->link.prev->next = &fulfilled_reaction->link;
      fulfilled_reaction->link.next = &data->fulfill_queue.head;
      data->fulfill_queue.head.prev = &fulfilled_reaction->link;
      rejected_reaction->link.prev = data->reject_queue.head.prev;
      rejected_reaction->link.prev->next = &rejected_reaction->link;
      rejected_reaction->link.next = &data->reject_queue.head;
      data->reject_queue.head.prev = &rejected_reaction->link;
    }
    data->is_handled = 1;
    if ( capabilitya )
      njs_vm_retval_set(vma, &capabilitya->promise);
    else
      njs_vm_retval_set(vma, &njs_value_undefined);
    return 0;
  }
  else
  {
    njs_memory_error(vma);
    return -1;
  }
}