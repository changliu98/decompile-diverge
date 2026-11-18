void gf_dump_vrml_simple_field(GF_SceneDumper *sdump, GF_FieldInfo field, GF_Node *parent)
{
 u32 i, sf_type;
 void *slot_ptr;
 GF_ChildNodeItem *list;

 switch (field.fieldType) {
 case 10:
  do { if (!(*(GF_Node **)field.far_ptr)) __assert_fail("*(GF_Node **)field.far_ptr", "/work/harness.c", 225, "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)"); } while (0);
  gf_dump_vrml_node(sdump, *(GF_Node **)field.far_ptr, GF_FALSE, NULL);
  break;
 case 42:
  list = *(GF_ChildNodeItem **) field.far_ptr;
  do { if (!list) __assert_fail("list", "/work/harness.c", 230, "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *)"); } while (0);
  sdump->indent++;
  while (list) {
   gf_dump_vrml_node(sdump, list->node, GF_TRUE, NULL);
   list = list->next;
  }
  sdump->indent--;
  break;
 case 14:
  break;
 default:
  if (gf_sg_vrml_is_sf_field(field.fieldType) == GF_FALSE) {
   sf_type = gf_sg_vrml_get_sf_type(field.fieldType);
   if (sdump->XMLDump==GF_FALSE) {
    gf_fprintf(sdump->trace, "[");
   } else {
    if (sf_type==4) {
     gf_fprintf(sdump->trace, " value='");
    } else {
     StartAttribute(sdump, "value");
    }
   }
   for (i=0; i<*(u32*)field.far_ptr; i++) {
    if (i) gf_fprintf(sdump->trace, " ");
    gf_sg_vrml_mf_get_item(field.far_ptr, field.fieldType, &slot_ptr, i);
    gf_dump_vrml_sffield(sdump, sf_type, slot_ptr, GF_TRUE, parent);
   }
   if (sdump->XMLDump==GF_FALSE) {
    gf_fprintf(sdump->trace, "]");
   } else {
    if (sf_type==4) {
     gf_fprintf(sdump->trace, "'");
    } else {
     EndAttribute(sdump);
    }
   }
  } else {
   if (sdump->XMLDump!=GF_FALSE) StartAttribute(sdump, "value");
   gf_dump_vrml_sffield(sdump, field.fieldType, field.far_ptr, GF_FALSE, parent);
   if (sdump->XMLDump!=GF_FALSE) EndAttribute(sdump);
  }
  break;
 }
}