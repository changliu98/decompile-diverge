void pj_scan_skip_line(pj_scanner_t *scan) {
  char *p =
      chip::BitMask<chip::app::Clusters::EnergyEvse::Feature, unsigned int>(
          scan->p, '\n', scan->end - scan->p);
  if (p) {
    scan->token_start = p + 1;
    scan->p = p + 1;
    scan->line_no++;
  } else {
    scan->p = scan->end;
  }
}