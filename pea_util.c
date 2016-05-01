#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pea.h"

char * pea_strtok(char *s, const char *delim, char **last) {
   char *p;
   char *d;
   int found_delim;

   if (s == '\0') {
      s = *last;
      *last = '\0';
   } else {
      *last = '\0';
   }
   
   if (s == '\0') {
      return '\0';
   }

   /* search for anything not in the delimiter list */
   for (; *s != '\0'; s++) {
      found_delim = 0;

      for (d = (char *) delim; *d != '\0'; d++) {
         if (*s == *d) {
            found_delim = 1;
            break;
         }
      }
      
      if (found_delim == 0) {
         break;
      }
   }
   
   if (*s == '\0') {
      return '\0';
   }

   /* search for anything in the delimiter list */
   for (p = s; *p != '\0'; p++) {
      found_delim = 0;

      for (d = (char *) delim; *d != '\0'; d++) {
         if (*p == *d) {
            found_delim = 1;
            *p = '\0';
            *last = p + 1;
            break;
         }
      }

      if (found_delim == 1) {
         break;
      }
   }

   return s;
}

char pea_hex(char c) {	
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'a' && c <= 'f') {
    return (c - 'a') + 10;
  }
  if (c >= 'A' && c <= 'F') {
    return (c - 'a') + 10;
  }
  return 0;
}

ulong pea_urldecode(const char *src,char *dst,ulong max) {	
  char  c;
	ulong l = 0;

  while((c = *src++) && max) {	
    if (c == '+') {
      c = ' ';
    } else if (c == '%') {	
      c = *src++;
			c = (pea_hex(c) << 4) | pea_hex(*src++);
    } 
		*dst++ = c;
    max--;
    l++;
	}
	*dst = '\0';

  return l;
}
