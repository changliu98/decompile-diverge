int njs_promise_add_reaction(struct njs_vm *vm, struct njs_value *promise, struct njs_value *onfulfilled, struct njs_value *onrejected, struct njs_promise_capability *capability)
{
  struct njs_promise *p;
  struct njs_promise_data *data;
  struct njs_promise_reaction *reaction;
  struct njs_value args[2];
  struct njs_function *function;
  int r;
  if (onfulfilled->data != njs_value_object)
    onfulfilled = &njs_value_undefined;
  if (onrejected->data != njs_value_object)
    onrejected = &njs_value_undefined;
  p = (struct njs_promise *)promise->data.u.object_value;
  data = (struct njs_promise_data *)p->data.u.object;
  reaction = njs_malloc(vm->mem_pool, sizeof *reaction);
  if (!reaction)
  {
    njs_out_of_memory(vm);
    return -1;
  }
  reaction->capability = capability;
  reaction->handler = onfulfilled->data;
  reaction->type = NJS_PROMISE_FULFILL;
  reaction = njs_malloc(vm->mem_pool, sizeof *reaction);
  if (!reaction)
  {
    njs_out_of_memory(vm);
    return -1;
  }
  reaction->capability = capability;
  reaction->handler = onrejected->data;
  reaction->type = NJS_PROMISE_REJECTED;
  if (data->state != NJS_PROMISE_PENDING)
  {
    function = njs_malloc(vm->mem_pool, sizeof *function);
    function->u.lambda = njs_promise_reaction_job;
    if (data->state == NJS_PROMISE_REJECTED)
    {
      njs_value_set(&args[0], reaction, njs_value_any);
      r = njs_promise_set(vm, p, NJS_PROMISE_HANDLE);
      if (r)
        return r;
    }
    else
      njs_value_set(&args[0], reaction, njs_value_any);
    args[1] = data->result;
    r = njs_function_call(vm, function, args, 2);
    if (r)
      return r;
  }
  else
  {
    do { (reaction)->link.prev = (&(data->fulfill_queue))->head.prev; (reaction)->link.prev->next = (&(reaction)->link); (reaction)->link.next = (&(data->fulfill_queue))->head; (&(data->fulfill_queue))->head.prev = (&(reaction)->link); } while (0);
    do { (reaction)->link.prev = (&(data->reject_queue))->head.prev; (reaction)->link.prev->next = (&(reaction)->link); (reaction)->link.next = (&(data->reject_queue))->head; (&(data->reject_queue))->head.prev = (&(reaction)->link); } while (0);
  }
  data->is_handled = 1;
  if (capability)
    njs_value_set(vm, &capability->promise);
  else
    njs_value_set(vm, &njs_value_undefined);
  return 0;
}