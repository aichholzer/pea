

struct pea_segment_struct {
  pea_interpreter*  m_interpreter;
  ulong*            m_buffer;
  ulong             m_size;
  ulong             m_count;
  ulong             m_read_pos;
};

pea_segment*  pea_segment_alloc(pea_interpreter* interpreter);
void          pea_segment_dump(pea_interpreter* interpreter,pea_segment* seg,FILE* f);
void          pea_segment_clear(pea_segment* seg);
void          pea_segment_add(pea_segment* seg,ulong v);
void          pea_segment_add_string(pea_segment* seg,pea_string* s);
void          pea_segment_add_offset(pea_segment* seg,ulong v);

size_t        pea_segment_add_label(pea_segment* seg);
void          pea_segment_set_label(pea_segment* seg,size_t label);

size_t        pea_segment_addr(pea_segment* seg);
void          pea_segment_concat(pea_segment* seg,pea_segment* add);
void          pea_segment_backup(pea_segment* seg,unsigned count);
int           pea_segment_end(pea_segment* seg);
ulong         pea_segment_get(pea_segment* seg);
void          pea_segment_get_string(pea_segment* seg,pea_string** string);
ulong         pea_segment_pos(pea_segment* seg);
void          pea_segment_jump(pea_segment* seg,ulong pos);
void          pea_segment_jump_rel(pea_segment* seg,ulong pos);
