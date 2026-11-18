/* WARNING: Restarted to delay deadcode elimination for space: stack */

void gf_dump_vrml_simple_field(GF_SceneDumper *sdump,GF_FieldInfo field,GF_Node *parent)

{
  Bool BVar1;
  GenMFField *mffield;
  void *slot_ptr;
  GF_ChildNodeItem *list;
  u32 sf_type;
  u32 i;
  GF_Node *parent_local;
  GF_SceneDumper *sdump_local;
  
  parent_local = parent;
  sdump_local = sdump;
  if (field.fieldType == 10) {
    if (*(long *)field.far_ptr == 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("*(GF_Node **)field.far_ptr","/work/harness.c",0xe1,
                    "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)");
    }
    gf_dump_vrml_node(sdump,*(GF_Node **)field.far_ptr,GF_FALSE,(char *)0x0);
  }
  else if (field.fieldType != 0xe) {
    if (field.fieldType == 0x2a) {
      list = *(GF_ChildNodeItem **)field.far_ptr;
      if (list == (GF_ChildNodeItem *)0x0) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("list","/work/harness.c",0xe6,
                      "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)");
      }
      sdump->indent = sdump->indent + 1;
      for (; list != (GF_ChildNodeItem *)0x0; list = list->next) {
        gf_dump_vrml_node(sdump_local,list->node,GF_TRUE,(char *)0x0);
      }
      sdump_local->indent = sdump_local->indent - 1;
    }
    else {
      BVar1 = gf_sg_vrml_is_sf_field(field.fieldType);
      if (BVar1 == GF_FALSE) {
        sf_type = gf_sg_vrml_get_sf_type(field.fieldType);
        if (sdump_local->XMLDump == GF_FALSE) {
          gf_fprintf(sdump_local->trace,"[");
        }
        else if (sf_type == 4) {
          gf_fprintf(sdump_local->trace," value=\'");
        }
        else {
          StartAttribute(sdump_local,"value");
        }
        for (i = 0; i < *(uint *)field.far_ptr; i = i + 1) {
          if (i != 0) {
            gf_fprintf(sdump_local->trace," ");
          }
          gf_sg_vrml_mf_get_item(field.far_ptr,field.fieldType,&slot_ptr,i);
          gf_dump_vrml_sffield(sdump_local,sf_type,slot_ptr,GF_TRUE,parent_local);
        }
        if (sdump_local->XMLDump == GF_FALSE) {
          gf_fprintf(sdump_local->trace,"]");
        }
        else if (sf_type == 4) {
          gf_fprintf(sdump_local->trace,"\'");
        }
        else {
          EndAttribute(sdump_local);
        }
      }
      else {
        if (sdump_local->XMLDump != GF_FALSE) {
          StartAttribute(sdump_local,"value");
        }
        gf_dump_vrml_sffield(sdump_local,field.fieldType,field.far_ptr,GF_FALSE,parent_local);
        if (sdump_local->XMLDump != GF_FALSE) {
          EndAttribute(sdump_local);
        }
      }
    }
  }
  return;
}