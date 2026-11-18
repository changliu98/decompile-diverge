njs_int_t njs_promise_perform_then
                    (njs_vm_t *vm,njs_value_t *value,njs_value_t *fulfilled,njs_value_t *rejected,
                    njs_promise_capability_t *capability)

{
  njs_promise_t *promise_00;
  njs_string_t *pnVar1;
  njs_int_t nVar2;
  undefined8 *data_00;
  undefined8 *data_01;
  njs_function_t *function_00;
  njs_promise_reaction_t *rejected_reaction;
  njs_promise_reaction_t *fulfilled_reaction;
  njs_promise_data_t *data;
  njs_function_t *function;
  njs_promise_t *promise;
  njs_value_t arguments [2];
  njs_int_t ret;
  njs_promise_capability_t *capability_local;
  njs_value_t *rejected_local;
  njs_value_t *fulfilled_local;
  njs_value_t *value_local;
  njs_vm_t *vm_local;
  njs_int_t local_c;
  
  fulfilled_local = fulfilled;
  if ((fulfilled->data).type != 0x12) {
    fulfilled_local = &njs_value_undefined;
  }
  rejected_local = rejected;
  if ((rejected->data).type != 0x12) {
    rejected_local = &njs_value_undefined;
  }
  promise_00 = (njs_promise_t *)(value->long_string).data;
  pnVar1 = (promise_00->value).long_string.data;
  data_00 = njs_mp_alloc(vm->mem_pool,0x30);
  if (data_00 == (undefined8 *)0x0) {
    njs_memory_error(vm);
    local_c = -1;
  }
  else {
    *data_00 = capability;
    data_00[4] = *(undefined8 *)fulfilled_local;
    *(anon_union_8_16_5fa0025e_for_u *)(data_00 + 5) = (fulfilled_local->data).u;
    *(undefined4 *)(data_00 + 1) = 1;
    data_01 = njs_mp_alloc(vm->mem_pool,0x30);
    if (data_01 == (undefined8 *)0x0) {
      njs_memory_error(vm);
      local_c = -1;
    }
    else {
      *data_01 = capability;
      data_01[4] = *(undefined8 *)rejected_local;
      *(anon_union_8_16_5fa0025e_for_u *)(data_01 + 5) = (rejected_local->data).u;
      *(undefined4 *)(data_01 + 1) = 2;
      if (*(int *)pnVar1 == 0) {
        data_00[2] = *(undefined8 *)(pnVar1 + 0x18);
        *(undefined8 **)(data_00[2] + 8) = data_00 + 2;
        data_00[3] = pnVar1 + 0x18;
        *(undefined8 **)(pnVar1 + 0x18) = data_00 + 2;
        data_01[2] = *(undefined8 *)(pnVar1 + 0x28);
        *(undefined8 **)(data_01[2] + 8) = data_01 + 2;
        data_01[3] = pnVar1 + 0x28;
        *(undefined8 **)(pnVar1 + 0x28) = data_01 + 2;
      }
      else {
        function_00 = njs_promise_create_function(vm,0x50);
        (function_00->u).lambda = (njs_function_lambda_t *)njs_promise_reaction_job;
        if (*(int *)pnVar1 == 2) {
          njs_set_data(arguments,data_01,NJS_DATA_TAG_ANY);
          nVar2 = njs_promise_host_rejection_tracker(vm,promise_00,NJS_PROMISE_HANDLE);
          if (nVar2 != 0) {
            return nVar2;
          }
        }
        else {
          njs_set_data(arguments,data_00,NJS_DATA_TAG_ANY);
        }
        arguments[1]._0_8_ = *(undefined8 *)(pnVar1 + 8);
        arguments[1]._8_8_ = *(anon_union_8_16_5fa0025e_for_u *)(pnVar1 + 0x10);
        nVar2 = njs_promise_add_event(vm,function_00,arguments,2);
        if (nVar2 != 0) {
          return nVar2;
        }
      }
      *(int *)(pnVar1 + 0x38) = 1;
      if (capability == (njs_promise_capability_t *)0x0) {
        njs_vm_retval_set(vm,&njs_value_undefined);
      }
      else {
        njs_vm_retval_set(vm,&capability->promise);
      }
      local_c = 0;
    }
  }
  return local_c;
}