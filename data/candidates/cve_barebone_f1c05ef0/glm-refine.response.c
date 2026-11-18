njs_int_t __cdecl njs_promise_perform_then(
        njs_vm_t *vm,
        njs_value_t *value,
        njs_value_t *fulfilled,
        njs_value_t *rejected,
        njs_promise_capability_t *capability)
{
    njs_promise_reaction_t *rejected_reaction;
    njs_promise_reaction_t *fulfilled_reaction;
    njs_promise_data_t *data;
    njs_function_t *function;
    njs_promise_t *promise;
    njs_value_t arguments[2];
    njs_int_t ret;

    // Check if the provided handlers are actual functions (type 18).
    // If not, replace them with `undefined` to maintain Promise semantics.
    if (fulfilled->data != 18) {
        fulfilled = &njs_value_undefined;
    }
    if (rejected->data != 18) {
        rejected = &njs_value_undefined;
    }

    promise = value->data.u.object_value;
    data = (njs_promise_data_t *)promise->value.data.u.object;

    // Allocate and initialize the fulfilled reaction
    fulfilled_reaction = (njs_promise_reaction_t *)njs_mp_alloc(vm->mem_pool, 0x30uLL);
    if (fulfilled_reaction == NULL) {
        njs_memory_error(vm);
        return -1;
    }

    fulfilled_reaction->capability = capability;
    fulfilled_reaction->handler = (njs_value_t)fulfilled->data;
    fulfilled_reaction->type = NJS_PROMISE_FULFILL;

    // Allocate and initialize the rejected reaction
    rejected_reaction = (njs_promise_reaction_t *)njs_mp_alloc(vm->mem_pool, 0x30uLL);
    if (rejected_reaction == NULL) {
        njs_memory_error(vm);
        return -1;
    }

    rejected_reaction->capability = capability;
    rejected_reaction->handler = (njs_value_t)rejected->data;
    rejected_reaction->type = NJS_PROMISE_REJECTED;

    if (data->state != NJS_PROMISE_PENDING) {
        // The promise is already settled, schedule the appropriate reaction job.
        function = njs_promise_create_function(vm, 0x50uLL);
        function->u.lambda = njs_promise_reaction_job;

        if (data->state == NJS_PROMISE_REJECTED) {
            njs_set_data(arguments, rejected_reaction, NJS_DATA_TAG_ANY);
            
            ret = njs_promise_host_rejection_tracker(vm, promise, NJS_PROMISE_HANDLE);
            if (ret != 0) {
                return ret;
            }
        } else {
            // Assume NJS_PROMISE_FULFILLED
            njs_set_data(arguments, fulfilled_reaction, NJS_DATA_TAG_ANY);
        }

        arguments[1] = data->result;
        
        ret = njs_promise_add_event(vm, function, arguments, 2u);
        if (ret != 0) {
            return ret;
        }
    } else {
        // The promise is pending, add reactions to the corresponding queues.
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

    // Set the return value to the capability's promise (or undefined if no capability)
    if (capability != NULL) {
        njs_vm_retval_set(vm, &capability->promise);
    } else {
        njs_vm_retval_set(vm, &njs_value_undefined);
    }

    return 0;
}