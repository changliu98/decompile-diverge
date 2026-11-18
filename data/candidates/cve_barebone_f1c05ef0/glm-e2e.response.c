int njs_promise_perform_then(njs_vm_t *vm, njs_promise_t *promise, njs_value_t *fulfilled, njs_value_t *rejected, njs_value_t *retval) {
    njs_promise_reaction_t *reaction_fulfilled;
    njs_promise_reaction_t *reaction_rejected;
    njs_promise_create_function_t *create_function;
    njs_value_t args[2];
    int ret;

    // 0x12 is likely NJS_UNDEFINED
    if (*(uint8_t *)fulfilled != 0x12) {
        fulfilled = &njs_value_undefined;
    }

    if (*(uint8_t *)rejected != 0x12) {
        rejected = &njs_value_undefined;
    }

    njs_promise_t *promise_data = (njs_promise_t *)promise->data; // offset 0x08 of njs_function_t
    njs_promise_t *p = promise_data; // offset 0x30 of njs_function_t

    reaction_fulfilled = njs_mp_alloc(vm->mp, 0x30);
    if (reaction_fulfilled == NULL) {
        njs_memory_error(vm);
        return -1; // NJS_ERROR
    }

    reaction_fulfilled->data = retval;
    reaction_fulfilled->value = *fulfilled;
    reaction_fulfilled->type = 1;

    reaction_rejected = njs_mp_alloc(vm->mp, 0x30);
    if (reaction_rejected == NULL) {
        njs_memory_error(vm);
        return -1; // NJS_ERROR
    }

    reaction_rejected->data = retval;
    reaction_rejected->value = *rejected;
    reaction_rejected->type = 2;

    if (p->state == 0) { // Pending
        // Add to fulfill reactions list
        reaction_fulfilled->handler = p->fulfill_reactions;
        if (p->fulfill_reactions != NULL) {
            p->fulfill_reactions->next = reaction_fulfilled;
        }
        reaction_fulfilled->next = &p->fulfill_reactions;
        p->fulfill_reactions = reaction_fulfilled;

        // Add to reject reactions list
        reaction_rejected->handler = p->reject_reactions;
        if (p->reject_reactions != NULL) {
            p->reject_reactions->next = reaction_rejected;
        }
        reaction_rejected->next = &p->reject_reactions;
        p->reject_reactions = reaction_rejected;

    } else { // Fulfilled or Rejected
        create_function = njs_promise_create_function(vm, 0x50);
        create_function->function = njs_promise_reaction_job;

        if (p->state == 2) { // Rejected
            njs_set_data(args, reaction_rejected, 0);
            ret = njs_promise_host_rejection_tracker(vm, promise_data, 0);
            if (ret != 0) {
                return ret;
            }
        } else { // Fulfilled
            njs_set_data(args, reaction_fulfilled, 0);
        }

        args[1] = p->result;
        
        ret = njs_promise_add_event(vm, create_function, args, 2);
        if (ret != 0) {
            return ret;
        }
    }

    p->is_handled = 1;

    if (retval == NULL) {
        njs_vm_retval_set(vm, &njs_value_undefined);
    } else {
        njs_vm_retval_set(vm, retval);
    }

    return 0; // NJS_OK
}