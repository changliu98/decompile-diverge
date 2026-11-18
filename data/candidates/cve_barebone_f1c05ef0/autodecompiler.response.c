__attribute__((used)) static int
njs_promise_perform_then(njs_vm_t *vm, njs_value_t *args, njs_value_t *func,
    njs_value_t *reject, njs_value_t *capability)
{
    int         ret;
    njs_value_t *value, *then, *reaction, *reject_func, *resolve_func;
    njs_promise_t  *promise;
    njs_promise_reaction_t  *fulfilled_reaction, *rejected_reaction;

    if (func->type != NJS_FUNCTION) {
        func = &njs_value_undefined;
    }

    if (reject->type != NJS_FUNCTION) {
        reject = &njs_value_undefined;
    }

    value = &args[1];
    promise = value->u.promise;

    fulfilled_reaction = njs_mp_alloc(vm->mem_cache, sizeof(njs_promise_reaction_t));
    if (fulfilled_reaction == NULL) {
        njs_memory_error(vm);
        return -1;
    }

    fulfilled_reaction->capability = capability;
    fulfilled_reaction->func.type = func->type;
    fulfilled_reaction->func.u.function = func->u.function;
    fulfilled_reaction->status = 1;

    rejected_reaction = njs_mp_alloc(vm->mem_cache, sizeof(njs_promise_reaction_t));
    if (rejected_reaction == NULL) {
        njs_memory_error(vm);
        return -1;
    }

    rejected_reaction->capability = capability;
    rejected_reaction->func.type = reject->type;
    rejected_reaction->func.u.function = reject->u.function;
    rejected_reaction->status = 2;

    if (promise->state == 0) {

        for ( ;; ) {
            reaction = &promise->fulfilled;
            if (reaction->type == NJS_NULL) {
                break;
            }

            njs_list_append(&fulfilled_reaction->link, &reaction->u.link);

            njs_list_append(&fulfilled_reaction->link, &reaction->u.link);
        }

        for ( ;; ) {
            reaction = &promise->rejected;
            if (reaction->type == NJS_NULL) {
                break;
            }

            njs_list_append(&rejected_reaction->link, &reaction->u.link);

            njs_list_append(&rejected_reaction->link, &reaction->u.link);
        }

    } else {
        then = njs_promise_create_function(vm, sizeof(njs_promise_reaction_t));

        then->u.function.native = njs_promise_reaction_job;

        if (promise->state == 2) {
            njs_set_data(&then->u.function.arg, rejected_reaction, 0);

            ret = njs_promise_host_rejection_tracker(vm, value, 0);
            if (ret != 0) {
                return ret;
            }

        } else {
            njs_set_data(&then->u.function.arg, fulfilled_reaction, 0);
        }

        njs_value_t  arg[2];

        arg[0] = promise->result;
        arg[1] = promise->this;

        ret = njs_promise_add_event(vm, then, arg, 2);
        if (ret != 0) {
            return ret;
        }
    }

    promise->status = 1;

    if (capability == NULL) {
        njs_vm_retval_set(vm, &njs_value_undefined);

    } else {
        njs_vm_retval_set(vm, capability);
    }

    return 0;
}