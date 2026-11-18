void gf_dump_vrml_simple_field(GF_SceneDumper *sdump, GF_FieldInfo field, GF_Node *node)
{
 int ftype;
 unsigned int i;
 char *cptr;
 GF_MFNode *mf;
 GF_MFVec3f *mfvec3f;
 GF_MFFloat *mffloat;
 GF_MFString *mfstring;
 GF_MFVec2f *mfvec2f;
 GF_MFVec2d *mfvec2d;
 GF_MFVec3d *mfvec3d;
 GF_MFVec4f *mfvec4f;
 GF_MFVec4d *mfvec4d;
 GF_MFColor *mfcolor;
 GF_MFColorRGBA *mfcolorrgba;
 GF_MFVec3i32 *mfvec3i32;
 GF_MFVec2i32 *mfvec2i32;
 GF_MFVec4i32 *mfvec4i32;
 GF_MFInt32 *mfint32;
 GF_MFTime *mf_time;
 GF_MFVec3f *mfvec3f_2;
 GF_MFVec2f *mfvec2f_2;
 GF_MFVec2d *mfvec2d_2;
 GF_MFVec3d *mfvec3d_2;
 GF_MFVec4f *mfvec4f_2;
 GF_MFVec4d *mfvec4d_2;
 GF_MFInt32 *mfint32_2;
 GF_MFVec3i32 *mfvec3i32_2;
 GF_MFVec2i32 *mfvec2i32_2;
 GF_MFVec4i32 *mfvec4i32_2;
 GF_MFTime *mf_time_2;

 switch (ftype = field.type) {
 case 10:
  if (!(*(GF_Node **)field.far_ptr)) { ___assert_fail("*(GF_Node **)field.far_ptr", "harness.c", 225, "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *"); };
  gf_dump_vrml_node(sdump, *(GF_Node **)field.far_ptr, 0, NULL);
  return;
 case 14:
  return;
 case 42:

  mf = (GF_MFNode *) *(GF_MFNode **)field.far_ptr;
  { if (!(mf)) { ___assert_fail("list", "harness.c", 230, "void gf_dump_vrml_simple_field(GF_SceneDumper *, GF_FieldInfo, GF_Node *"); } };
  sdump->indent_level++;
  while (mf) {
   gf_dump_vrml_node(sdump, mf->node, 1, NULL);
   mf = mf->next;
  }
  sdump->indent_level--;
  return;
 }

 if (gf_sg_vrml_is_sf_field(field.type)) {

  if (sdump->use_names) StartAttribute(sdump, "value");
  gf_dump_vrml_sffield(sdump, field.type, (char *)field.far_ptr, 0, node);
  if (sdump->use_names) EndAttribute(sdump);
  return;
 }


 mf = (GF_MFNode *)field.far_ptr;
 ftype = gf_sg_vrml_get_sf_type(field.type);

 if (!sdump->use_names) gf_fprintf(sdump->out, "[");
 else {
  switch (ftype) {
  case 4:
   gf_fprintf(sdump->out, " value='");
   break;
  default:
   StartAttribute(sdump, "value");
  }
 }

 for (i=0; i<mf->count; i++) {
  if (i) gf_fprintf(sdump->out, " ");
  gf_sg_vrml_mf_get_item((char *)field.far_ptr, field.type, &cptr, i);
  gf_dump_vrml_sffield(sdump, ftype, cptr, 1, node);
 }
 if (!sdump->use_names) gf_fprintf(sdump->out, "]");
 else {
  switch (ftype) {
  case 4:
   gf_fprintf(sdump->out, "'/>");
   break;
  default:
   EndAttribute(sdump);
  }
 }
}