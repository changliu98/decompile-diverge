void validate_rt_entry(struct page *page)
{
  page->pgprot = (page->pgprot & ~0x20);
  page->pgprot = (page->pgprot & ~0x40);
  page->pgprot = (page->pgprot & ~0x80);
  page->pgprot = (page->pgprot | 0x02);
  page->pgprot = (page->pgprot | 0x01);
}