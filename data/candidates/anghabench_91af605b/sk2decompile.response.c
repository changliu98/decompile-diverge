static const char *freezer_state_strs(unsigned int state) {
  if (state & IOPRIO_CLASS_FREEZER_FROZEN)
    return "FROZEN";
  else if (state & IOPRIO_CLASS_FREEZER_FREEZING)
    return "FREEZING";
  else
    return "THAWED";
}