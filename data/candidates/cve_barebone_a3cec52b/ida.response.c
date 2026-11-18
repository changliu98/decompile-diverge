void __cdecl gf_dump_vrml_simple_field(GF_SceneDumper *sdump, GF_FieldInfo field, GF_Node *parent)
{
  void *slot_ptr; // [rsp+18h] [rbp-28h] BYREF
  GF_ChildNodeItem *list; // [rsp+20h] [rbp-20h]
  u32 sf_type; // [rsp+28h] [rbp-18h]
  u32 i; // [rsp+2Ch] [rbp-14h]
  GF_Node *parenta; // [rsp+30h] [rbp-10h]
  GF_SceneDumper *sdumpa; // [rsp+38h] [rbp-8h]

  sdumpa = sdump;
  parenta = parent;
  if ( field.fieldType == 10 )
  {
    if ( !*(_QWORD *)field.far_ptr )
      __assert_fail(
        "*(GF_Node **)field.far_ptr",
        "/work/harness.c",
        0xE1u,
        "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)");
    gf_dump_vrml_node(sdumpa, *(GF_Node **)field.far_ptr, GF_FALSE, 0LL);
  }
  else if ( field.fieldType != 14 )
  {
    if ( field.fieldType == 42 )
    {
      list = *(GF_ChildNodeItem **)field.far_ptr;
      if ( !list )
        __assert_fail(
          "list",
          "/work/harness.c",
          0xE6u,
          "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)");
      ++sdumpa->indent;
      while ( list )
      {
        gf_dump_vrml_node(sdumpa, list->node, GF_TRUE, 0LL);
        list = list->next;
      }
      --sdumpa->indent;
    }
    else if ( gf_sg_vrml_is_sf_field(field.fieldType) )
    {
      if ( sdumpa->XMLDump )
        StartAttribute(sdumpa, "value");
      gf_dump_vrml_sffield(sdumpa, field.fieldType, field.far_ptr, GF_FALSE, parenta);
      if ( sdumpa->XMLDump )
        EndAttribute(sdumpa);
    }
    else
    {
      sf_type = gf_sg_vrml_get_sf_type(field.fieldType);
      if ( sdumpa->XMLDump )
      {
        if ( sf_type == 4 )
          gf_fprintf(sdumpa->trace, " value='");
        else
          StartAttribute(sdumpa, "value");
      }
      else
      {
        gf_fprintf(sdumpa->trace, "[");
      }
      for ( i = 0; i < *(_DWORD *)field.far_ptr; ++i )
      {
        if ( i )
          gf_fprintf(sdumpa->trace, " ");
        gf_sg_vrml_mf_get_item(field.far_ptr, field.fieldType, &slot_ptr, i);
        gf_dump_vrml_sffield(sdumpa, sf_type, slot_ptr, GF_TRUE, parenta);
      }
      if ( sdumpa->XMLDump )
      {
        if ( sf_type == 4 )
          gf_fprintf(sdumpa->trace, "'");
        else
          EndAttribute(sdumpa);
      }
      else
      {
        gf_fprintf(sdumpa->trace, "]");
      }
    }
  }
}