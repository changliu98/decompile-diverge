void __cdecl gf_dump_vrml_simple_field(GF_SceneDumper *sdump, GF_FieldInfo field, GF_Node *parent)
{
  void *slot_ptr;
  GF_ChildNodeItem *list;
  u32 sf_type;
  u32 i;

  // fieldType == 14 is ignored (early return)
  if ( field.fieldType == 14 )
    return;

  if ( field.fieldType == 10 ) // SFNode
  {
    if ( !*(_QWORD *)field.far_ptr )
      __assert_fail("*(GF_Node **)field.far_ptr", "/work/harness.c", 0xE1u, "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)");
    gf_dump_vrml_node(sdump, *(GF_Node **)field.far_ptr, GF_FALSE, 0LL);
  }
  else if ( field.fieldType == 42 ) // MFNode
  {
    list = *(GF_ChildNodeItem **)field.far_ptr;
    if ( !list )
      __assert_fail("list", "/work/harness.c", 0xE6u, "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)");
    ++sdump->indent;
    while ( list )
    {
      gf_dump_vrml_node(sdump, list->node, GF_TRUE, 0LL);
      list = list->next;
    }
    --sdump->indent;
  }
  else if ( gf_sg_vrml_is_sf_field(field.fieldType) ) // Single Field (SF)
  {
    if ( sdump->XMLDump )
      StartAttribute(sdump, "value");
    gf_dump_vrml_sffield(sdump, field.fieldType, field.far_ptr, GF_FALSE, parent);
    if ( sdump->XMLDump )
      EndAttribute(sdump);
  }
  else // Multiple Field (MF)
  {
    sf_type = gf_sg_vrml_get_sf_type(field.fieldType);
    if ( sdump->XMLDump )
    {
      if ( sf_type == 4 )
        gf_fprintf(sdump->trace, " value='");
      else
        StartAttribute(sdump, "value");
    }
    else
    {
      gf_fprintf(sdump->trace, "[");
    }
    
    for ( i = 0; i < *(_DWORD *)field.far_ptr; ++i )
    {
      if ( i )
        gf_fprintf(sdump->trace, " ");
      gf_sg_vrml_mf_get_item(field.far_ptr, field.fieldType, &slot_ptr, i);
      gf_dump_vrml_sffield(sdump, sf_type, slot_ptr, GF_TRUE, parent);
    }
    
    if ( sdump->XMLDump )
    {
      if ( sf_type == 4 )
        gf_fprintf(sdump->trace, "'");
      else
        EndAttribute(sdump);
    }
    else
    {
      gf_fprintf(sdump->trace, "]");
    }
  }
}