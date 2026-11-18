static njs_int_t njs_promise_perform_then(njs_vm_t *vm, njs_value_t *value,
                                          njs_value_t *on_fulfilled,
                                          njs_value_t *on_rejected,
                                          njs_host_event_t *hev) {
  njs_promise_t *promise;
  njs_promise_event_t *fulfilled, *rejected;
  njs_value_t args[2];
  njs_function_t *func;
  njs_int_t ret;
  if (on_fulfilled->type != (1 << 4) + 2) {
    on_fulfilled = &njs_value_undefined;
  }
  if (on_rejected->type != (1 << 4) + 2) {
    on_rejected = &njs_value_undefined;
  }
  promise = value->u.promise;
  func = promise->events.resolve;
  fulfilled = njs_mp_alloc(vm->mem_pool, sizeof(njs_promise_event_t));
  if (fulfilled == NULL) {
    njs_memory_error(vm);
    return -1;
  }
  fulfilled->hev = hev;
  fulfilled->value = *on_fulfilled;
  fulfilled->type = NJS_PROMISE_EVENT_FULFILLED;
  rejected = njs_mp_alloc(vm->mem_pool, sizeof(njs_promise_event_t));
  if (rejected == NULL) {
    njs_memory_error(vm);
    return -1;
  }
  rejected->hev = hev;
  rejected->value = *on_rejected;
  rejected->type = NJS_PROMISE_EVENT_REJECTED;
  if (func->type == NJS_FUNCTION_CTOR) {
    fulfilled->link.next = func->u.constructor.next;
    fulfilled->link.next->prev = &fulfilled->link;
    fulfilled->link.prev = &func->u.constructor;
    func->u.constructor.next = &fulfilled->link;
    rejected->link.next = func->u.reject.next;
    rejected->link.next->prev = &rejected->link;
    rejected->link.prev = &func->u.reject;
    func->u.reject.next = &rejected->link;
  } else {
    func = njs_promise_create_function(vm, 80);
    func->entry = njs_promise_then_entry;
    if (func == NULL) {
      return -1;
    }
    if (func->type == NJS_PROMISE_EVENT_REJECTED) {
      njs_set_data(&args[0], rejected, NJS_VALUE_ARRAY);
      ret = njs_promise_host_rejection_tracker(vm, promise,
                                               njs_promise_rejection_tracker);
      if (ret != 0) {
        return ret;
      }
    } else {
      njs_set_data(&args[0], fulfilled, NJS_VALUE_ARRAY);
    }
    args[1] = func->prototype;
    ret = njs_promise_add_event(vm, func, args, 2);
    if (ret != 0) {
      return ret;
    }
  }
  func->resolved = 1;
  if (hev != NULL) {
    njs_vm_retval_set(vm, &hev->retval);
  } else {
    njs_vm_retval_set(vm, &njs_value_undefined);
  }
  return 0;
}