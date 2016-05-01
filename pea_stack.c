#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pea.h"
#include "pea_stack.h"

#define PEA_STACK_PAGESIZE  100

pea_stack* pea_stack_alloc(pea_interpreter* interpreter,ulong elem_size) {
  pea_stack* stack;
  
  stack = calloc(1,sizeof(struct pea_stack_struct));

  stack->m_elem_size = elem_size;
  stack->m_page = 0;
  stack->m_prev = NULL;
  stack->m_count = 0;
  stack->m_vector = calloc(PEA_STACK_PAGESIZE,elem_size);
  stack->m_top = stack;
  
  return stack;
}

void pea_stack_free(pea_interpreter* interpreter,pea_stack* stack) {
  pea_stack*  page;

  stack = page = stack->m_top;
  while(stack) {
    stack = page->m_prev;

    free(page->m_vector);
    free(page);

    page = stack;
  }
}

void pea_stack_push(pea_stack* stack,void* elem) {
  pea_stack*  page;

  //
  // Locate the top page of the stack
  //
  page = stack->m_top;

  //
  // Check if page is full
  //
  if (stack->m_count >= PEA_STACK_PAGESIZE) {
    pea_stack* next;
  
    //
    // Allocate a new page
    //
    next = calloc(1,sizeof(struct pea_stack_struct));

    next->m_elem_size = stack->m_elem_size;
    next->m_page = page->m_page + 1;
    next->m_prev = page;
    next->m_count = 0;
    next->m_vector = calloc(PEA_STACK_PAGESIZE,next->m_elem_size);
  
    stack->m_top = next;

    page = next;
  }

  //
  // Push element on top of stack
  //
  memcpy((char*)page->m_vector + (page->m_count * page->m_elem_size),elem,page->m_elem_size);

  page->m_count++;
}

int pea_stack_pop(pea_stack* stack,void* elem) {
  pea_stack*  page;

  //
  // Locate the top page of the stack
  //
  page = stack->m_top;

  //
  // Check if at page bottom
  // 
  if (page->m_count == 0) {
    pea_stack*  prev;

    //
    // Check if we have a previous page
    // 
    prev = page->m_prev;
    if (prev == NULL) {
      return 0;
    }

    //
    // Make this page the current page
    //
    stack->m_top = prev;

    //
    // Free the page
    free(page->m_vector);
    free(page);

    page = prev;
  }

  //
  // Return the element on top of the stack
  //
  page->m_count--;

  memcpy(elem,(char*)page->m_vector + (page->m_count * page->m_elem_size),page->m_elem_size);

  return 1;
}

void pea_stack_pop_ex(pea_stack* stack,ulong back,void* elem) {
  pea_stack*  page;

  //
  // Locate the top page of the stack
  //
  page = stack->m_top;

  if (back > page->m_count) {
    pea_stack*  prev;

    //
    // Check if we have a previous page
    // 
    prev = page->m_prev;
    if (prev == NULL) {
      // BUGBUG: Underflow of stack
      return;
    }

    back -= page->m_count;

    page = prev;
  }


  memcpy(elem,(char*)page->m_vector + ((page->m_count - 1 - back) * page->m_elem_size),page->m_elem_size);

  memmove((char*)page->m_vector + ((page->m_count - 1 - back) * page->m_elem_size),(char*)page->m_vector + ((page->m_count - back ) * page->m_elem_size),back * page->m_elem_size);

  page->m_count--;
}

ulong pea_stack_size(pea_stack* stack) {
  pea_stack*  page;

  //
  // Locate the top page of the stack
  //
  page = stack->m_top;

  return page->m_count + page->m_page * PEA_STACK_PAGESIZE;
}

void pea_stack_top(pea_stack* stack,void* elem) {
  pea_stack*  page;

  //
  // Locate the top page of the stack
  //
  page = stack->m_top;

  //
  // Check if at page bottom
  // 
  if (page->m_count == 0) {
    pea_stack*  prev;

    //
    // Check if we have a previous page
    // 
    prev = page->m_prev;
    if (prev == NULL) {
      NYI;
      return;
    }
  
    page = prev;
  }

  memcpy(elem,(char*)page->m_vector + ((page->m_count - 1) * page->m_elem_size),page->m_elem_size);
}

void pea_stack_get(pea_stack* stack,ulong index,void* elem) {
  pea_stack*  page;

  //
  // Locate the top page of the stack
  //
  page = stack->m_top;

  while (index >= PEA_STACK_PAGESIZE) {
    index -= PEA_STACK_PAGESIZE;
    page = page->m_prev;
  }

  memcpy(elem,(char*)page->m_vector + (index * page->m_elem_size),page->m_elem_size);
}

