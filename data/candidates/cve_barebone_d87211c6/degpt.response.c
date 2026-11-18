VALUE rb_xml_reader_attribute_hash(VALUE rb_reader)

{
  int iVar1;
  VALUE hash;
  xmlNodePtr pxVar2;
  VALUE key;
  xmlChar *cstr;
  xmlChar *c_value;
  VALUE rb_value;
  VALUE rb_name;
  xmlAttrPtr c_property;
  xmlNodePtr c_node;
  xmlTextReaderPtr c_reader;
  VALUE rb_attributes;
  VALUE rb_reader_local;
  
  hash = rb_hash_new();
  iVar1 = has_attributes((xmlTextReaderPtr)rb_reader);
  if (iVar1 != 0) {
    pxVar2 = xmlTextReaderExpand((xmlTextReaderPtr)rb_reader);
    for (c_property = pxVar2->properties; c_property != (xmlAttrPtr)0x0;
        c_property = c_property->next) {
      key = nokogiri_str_new2_stub((char *)c_property->name);
      rb_value = 0;
      cstr = xmlNodeGetContent((xmlNode *)c_property);
      if (cstr != (xmlChar *)0x0) {
        rb_value = nokogiri_str_new2_stub((char *)cstr);
        free(cstr);
      }
      rb_hash_aset(hash,key,rb_value);
    }
  }
  return hash;
}