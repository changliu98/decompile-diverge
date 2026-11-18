void gf_dump_vrml_simple_field(GFDumpMgr *mgr, GFNode sf, GFSDict *dict) {
  if (sf.type == 10) {
    assert(*(GFSDict **)sf.data);
    gf_dump_vrml_node(mgr, *(GFSDict **)sf.data, GF_FALSE, NULL);
  } else if (sf.type == 14) {
  } else if (sf.type == 42) {
    GFList *list = *(GFList **)sf.data;
    assert(list);
    mgr->indent_level++;
    while (list) {
      gf_dump_vrml_node(mgr, list->data, GF_TRUE, NULL);
      list = list->next;
    }
    mgr->indent_level--;
  } else if (gf_sg_vrml_is_sf_field(sf.type)) {
    if (mgr->xml) {
      StartAttribute(mgr, "value");
    }
    gf_dump_vrml_sffield(mgr, sf.type, sf.data, GF_FALSE, dict);
    if (mgr->xml) {
      EndAttribute(mgr);
    }
  } else {
    gfcsf_type sf_type = gf_sg_vrml_get_sf_type(sf.type);
    gfcsf_type i;
    if (mgr->xml) {
      if (sf_type == 4) {
        gf_fprintf(mgr->f, " value='");
      } else {
        StartAttribute(mgr, "value");
      }
    } else {
      gf_fprintf(mgr->f, "[");
    }
    for (i = 0; i < *(gfcsf_type *)sf.data; i++) {
      void *item;
      if (i) {
        gf_fprintf(mgr->f, " ");
      }
      gf_sg_vrml_mf_get_item(sf.data, sf.type, &item, i);
      gf_dump_vrml_sffield(mgr, sf_type, item, GF_TRUE, dict);
    }
    if (mgr->xml) {
      if (sf_type == 4) {
        gf_fprintf(mgr->f, "'");
      } else {
        EndAttribute(mgr);
      }
    } else {
      gf_fprintf(mgr->f, "]");
    }
  }
}