static struct mrb_time*
func0(mrb_state *mrb, mrb_value sec, mrb_value usec)
{
  struct mrb_time *tm;
  time_t time;
  mrb_int msec;

  time = time_wrap(sec);
  if (mrb_time_make(mrb, sec, usec, &time, 0)) {
    tm = (struct mrb_time *)mrb_malloc(mrb, sizeof(struct mrb_time));
  }
  else {
    mrb_gc_arena_save(time);
    tm = NULL;
  }

  return tm;
}