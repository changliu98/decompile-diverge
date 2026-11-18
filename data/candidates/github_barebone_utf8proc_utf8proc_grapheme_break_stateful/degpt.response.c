utf8proc_bool
utf8proc_grapheme_break_stateful(utf8proc_int32_t c1,utf8proc_int32_t c2,utf8proc_int32_t *state)

{
  utf8proc_bool uVar1;
  utf8proc_property_t *puVar2;
  utf8proc_property_t *puVar3;
  utf8proc_property_t *p2;
  utf8proc_property_t *p1;
  utf8proc_int32_t *state_local;
  utf8proc_int32_t c2_local;
  utf8proc_int32_t c1_local;
  
  puVar2 = utf8proc_get_property(c1);
  puVar3 = utf8proc_get_property(c2);
  uVar1 = grapheme_break_extended
                    (puVar2->boundclass,puVar3->boundclass,puVar2->indic_conjunct_break,
                     puVar3->indic_conjunct_break,state);
  return uVar1;
}