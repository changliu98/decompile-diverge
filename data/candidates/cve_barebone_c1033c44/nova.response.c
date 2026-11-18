static struct demangle_component *
mrb_realloc (struct d_info *di,
		      struct demangle_component *class_type,
		      struct demangle_component *template_param)
{
  struct demangle_component *member;
  struct demangle_component *template_id;

  member = d_extract_qualified_name (di, class_type, template_param);

  if (template_param == NULL)
    {
      template_id = member;
    }
  else if (member == NULL)
    {
      d_add_subst (di, class_type);
      d_add_subst (di, template_param);
      template_id = d_make_empty (di);
      template_id->type = DEMANGLE_COMPONENT_TEMPLATE_ID;
    }
  else
    {
      di->last_sub->next = NULL;
      template_id = d_make_empty (di);
      template_id->type = DEMANGLE_COMPONENT_TEMPLATE_ID;
    }

  return template_id;
}