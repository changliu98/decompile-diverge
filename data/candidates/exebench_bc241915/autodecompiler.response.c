__attribute__((used)) static void
fb_hSetDirty(struct pmap *pm, struct vm_page *m, int start,
    int end)
{

	if (pm->pm_dirty_start == m->page_index) {
		pm->pm_dirty_start = start;
		pm->pm_dirty_end = end;
		return;
	}

	if (start < pm->pm_dirty_start)
		pm->pm_dirty_start = start;
	if (end > pm->pm_dirty_end)
		pm->pm_dirty_end = end;
}