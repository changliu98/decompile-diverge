void __cdecl pj_scan_skip_line(pj_scanner *scanner)
{
  char *s; // [rsp+0h] [rbp-10h]

  s = (char *)chip::BitMask<chip::app::Clusters::EnergyEvse::Feature,unsigned int>::BitMask<chip::app::Clusters::EnergyEvse::Feature>(
                scanner->curptr,
                10,
                scanner->end - scanner->curptr);
  if ( s )
  {
    scanner->start_line = s + 1;
    scanner->curptr = s + 1;
    ++scanner->line;
  }
  else
  {
    scanner->curptr = scanner->end;
  }
}