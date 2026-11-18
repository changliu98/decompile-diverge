void _cairo_clip_path_reference (cairo_clip_path_t *cp, cairo_clip_path_t *new_clip)
{
    cairo_clip_path_t *prev, *next;

    prev = cp;
    next = new_clip;

    do {
 next = prev->next;
    } while (!(((prev)->ref_count == 0 || ((unsigned long) (prev) & 0x01)) ? 0 : (((prev)->ref_count == 0 || ((unsigned long) (prev) & 0x01)) ? 0 : 1)) && !((next) == NULL || ((unsigned long) (next) & 0x01)) &&
     !((next) == NULL || ((unsigned long) (next) & 0x01)) &&
     !((next) == NULL || ((unsigned long) (next) & 0x01)) &&
     !((next) == NULL || ((unsigned long) (next) & 0x01)) &&
     !((next) == NULL || ((unsigned long) (next) & 0x01)) &&
     !((next) == NULL || ((unsigned long) (next) & 0x01)) &&
nondet__sync_lock_test_and_set (&(prev)->ref_count, (next)->ref_count) != (next)->ref_count);
}