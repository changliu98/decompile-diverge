void gf_dump_vrml_simple_field(struct GF_SceneDumper *sdump, struct GF_FieldInfo field, struct GF_Node *parent)
{
  struct GF_Node *parenta = (GF_Node *)parent;
  struct GF_ChildNodeItem *list;
  void *ptr;
  unsigned int i;
  unsigned int sf_type;
  if ( field.fieldType == eSF_Node )
  {
    if ( !*(struct GF_Node **)field.far_ptr )
      do { if (0) printf("*(GF_Node **)field.far_ptr"); else fputs("*(GF_Node **)field.far_ptr",stderr); fputs(" ",stderr); do { if (0) printf("/work/harness.c"); else fputs("/work/harness.c",stderr); do { if (0) printf(":%d:", 225); else fputs(":225:",stderr); } while (0); do { if (0) printf(" : "); else fputs(" : ",stderr); } while (0); } while (0); do { if (0) printf("void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)"); else fputs("void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)",stderr); fputs("\n",stderr); } while (0); } while (0);
    gf_dump_node( sdump, *(struct GF_Node **)field.far_ptr, GF_FALSE, ((void *)0) );
  }
  else if ( field.fieldType == eSF_String )
  {
    list = *(struct GF_ChildNodeItem **)field.far_ptr;
    if ( !list )
      do { if (0) printf("list"); else fputs("list",stderr); fputs(" ",stderr); do { if (0) printf("/work/harness.c"); else fputs("/work/harness.c",stderr); do { if (0) printf(":%d:", 229); else fputs(":229:",stderr); } while (0); do { if (0) printf(" : "); else fputs(" : ",stderr); } while (0); } while (0); do { if (0) printf("void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)"); else fputs("void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)",stderr); fputs("\n",stderr); } while (0); } while (0);
    sdump->indent++;
    while ( list )
    {
      gf_dump_node( sdump, list->node, GF_TRUE, ((void *)0) );
      list = list->next;
    }
    sdump->indent--;
  }
  else
  {
    if ( is_array_type( field.fieldType ) )
    {
      if ( sdump->XMLDump )
        gf_dump_xml_field( sdump, "value" );
      gf_dump_value( sdump, field.fieldType, field.far_ptr, GF_FALSE, parenta );
      if ( sdump->XMLDump )
        gf_dump_xml_end( sdump );
    }
    else
    {
      sf_type = get_array_type( field.fieldType );
      if ( sdump->XMLDump )
      {
        if ( sf_type == eSF_String )
          gf_dump_xml_string( sdump->trace, " value='");
        else
          gf_dump_xml_field( sdump, "value" );
      }
      else
      {
        gf_dump_xml_string( sdump->trace, "[");
      }
      for ( i = 0; i < *(unsigned int *)field.far_ptr; i++ )
      {
        if ( i )
          gf_dump_xml_string( sdump->trace, " " );
        gf_get_array_ptr( field.far_ptr, field.fieldType, &ptr, i );
        gf_dump_value( sdump, sf_type, ptr, GF_TRUE, parenta );
      }
      if ( sdump->XMLDump )
      {
        if ( sf_type == eSF_String )
          gf_dump_xml_string( sdump->trace, "'");
        else
          gf_dump_xml_end( sdump );
      }
      else
      {
        gf_dump_xml_string( sdump->trace, "]" );
      }
    }
  }
}