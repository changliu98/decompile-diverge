VALUE __cdecl rb_xml_reader_attribute_hash(VALUE rb_reader)
{
  xmlChar *c_value; // [rsp+8h] [rbp-48h]
  VALUE rb_value; // [rsp+10h] [rbp-40h]
  VALUE rb_name; // [rsp+18h] [rbp-38h]
  const xmlNode *c_property; // [rsp+20h] [rbp-30h]
  VALUE rb_attributes; // [rsp+38h] [rbp-18h]

  rb_attributes = rb_hash_new();
  if ( !has_attributes((xmlTextReaderPtr)rb_reader) )
    return rb_attributes;
  for ( c_property = (const xmlNode *)xmlTextReaderExpand((xmlTextReaderPtr)rb_reader)->properties;
        c_property;
        c_property = c_property->next )
  {
    rb_name = nokogiri_str_new2_stub((const char *)c_property->name);
    rb_value = 0LL;
    c_value = xmlNodeGetContent(c_property);
    if ( c_value )
    {
      rb_value = nokogiri_str_new2_stub((const char *)c_value);
      free(c_value);
    }
    rb_hash_aset(rb_attributes, rb_name, rb_value);
  }
  return rb_attributes;
}