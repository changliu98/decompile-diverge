static struct mrb_irep *
set_to_array(mrb_irep *top)
{
  struct mrb_irep *irep;
  struct mrb_irep *cur_irep;
  struct RProc *proc;
  struct RProc *cur_proc;
  struct RProc *tmp_proc;
  mrb_sym *cur_syms;
  uint8_t i;
  uint8_t j;

  cur_syms = (mrb_sym*)mrb_malloc(top->rlen * sizeof(mrb_sym));
  if (!cur_syms) {
    return NULL;
  }

  i = 0;
  j = 0;
  while (1) {
    if (j >= top->rlen) {
      j = 0;
      i++;
    }
    if (i >= top->rlen) {
      break;
    }
    proc = top->reps[i];
    cur_irep = NULL;
    while (proc) {
      cur_irep = proc->body.irep;
      if (cur_irep) {
        cur_syms[j] = proc->body.irep->sym;
        j++;
      }
      tmp_proc = proc;
      proc = proc->next;
      mrb_irep_decref(tmp_proc);
    }
  }
  irep = mrb_irep_new(top->rlen, cur_syms);
  return irep;
}