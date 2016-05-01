#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pea.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_segment.h"
#include "pea_mem.h"
#include "pea_op.h"

pea_segment* pea_segment_alloc(pea_interpreter* interpreter) {
  pea_segment* seg;

  seg = pea_calloc(interpreter,1,sizeof(struct pea_segment_struct));

  seg->m_interpreter = interpreter;

  seg->m_size = 2000;

  seg->m_buffer = pea_malloc(interpreter,seg->m_size * sizeof(ulong));

  return seg;
}

void pea_segment_dump(pea_interpreter* interpreter,pea_segment* seg,FILE* f) {
  ulong i;
  ulong args;

  for(i=0;i<seg->m_count;i++) {
    pea_print(interpreter,f,"%d %s ",i,opInfo[seg->m_buffer[i]].name);
    args = opInfo[seg->m_buffer[i]].args;
    while(args--) {
      pea_print(interpreter,f,"%d ",seg->m_buffer[++i]);
    }
    pea_print(interpreter,f,"\n");
  }

}

void pea_segment_clear(pea_segment* seg) {
  seg->m_count = 0;
}

void pea_segment_add(pea_segment* seg,ulong v) {
  if (seg->m_count >= seg->m_size) {
    seg->m_size *= 2;
    seg->m_buffer = realloc(seg->m_buffer,seg->m_size * sizeof(ulong));
  }
  seg->m_buffer[seg->m_count++] = v;
}

void pea_segment_add_offset(pea_segment* seg,ulong v) {
  if (seg->m_count >= seg->m_size) {
    seg->m_size *= 2;
    seg->m_buffer = realloc(seg->m_buffer,seg->m_size * sizeof(ulong));
  }
  seg->m_buffer[seg->m_count++] =  v - (seg->m_count + 1);
}

void pea_segment_add_string(pea_segment* seg,pea_string* s) {
  if (seg->m_count >= seg->m_size) {
    seg->m_size *= 2;
    seg->m_buffer = realloc(seg->m_buffer,seg->m_size * sizeof(ulong));
  }
  seg->m_buffer[seg->m_count++] = (ulong)s;
}

size_t pea_segment_add_label(pea_segment* seg) {

  if (seg->m_count >= seg->m_size) {
    seg->m_size *= 2;
    seg->m_buffer = realloc(seg->m_buffer,seg->m_size * sizeof(ulong));
  }

  seg->m_buffer[seg->m_count++] = 0;
  
  return seg->m_count-1;
}

void pea_segment_set_label(pea_segment* seg,size_t label) {
  seg->m_buffer[label] = seg->m_count - (label + 1);
}

size_t pea_segment_addr(pea_segment* seg) {
  return seg->m_count;
}

void pea_segment_concat(pea_segment* seg,pea_segment* add) {
  
  while ((seg->m_count + add->m_count) >= seg->m_size) {
    seg->m_size *= 2;
    seg->m_buffer = realloc(seg->m_buffer,seg->m_size * sizeof(ulong));
  }

  memcpy(&seg->m_buffer[seg->m_count],add->m_buffer,add->m_count * sizeof(ulong));
  seg->m_count += add->m_count;

  add->m_count = 0;
}


void pea_segment_backup(pea_segment* seg,unsigned count) {
  seg->m_count -= count;
}

int pea_segment_end(pea_segment* seg) {
  return seg->m_read_pos > seg->m_count;
}

ulong pea_segment_get(pea_segment* seg) {
  return seg->m_buffer[seg->m_read_pos++];
}

void pea_segment_get_string(pea_segment* seg,pea_string** string) {
  *string = (pea_string*)pea_segment_get(seg);
}

ulong pea_segment_pos(pea_segment* seg) {
  return seg->m_read_pos;
}


void pea_segment_jump(pea_segment* seg,ulong pos) {
  seg->m_read_pos = pos;
}

void pea_segment_jump_rel(pea_segment* seg,ulong pos) {
  seg->m_read_pos += pos;
}
