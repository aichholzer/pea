#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "pea.h"
#include "pea_op.h"
#include "pea_string.h"
#include "pea_atom.h"
#include "pea_segment.h"
#include "pea_class.h"
#include "pea_function.h"
#include "pea_object.h"
#include "pea_map.h"
#include "pea_stack.h"
#include "pea_variable.h"
#include "pea_array.h"

int pea_eval(pea_interpreter* interpreter,char* buff);

int pea_exit(pea_interpreter* interpreter) {
  exit(0);
}

pea_array* pea_new_array(pea_interpreter* interpreter,ulong arg_count) {
  pea_array*    res;
  pea_variable  v;

  res = pea_array_alloc(interpreter);

  while(arg_count) {
    pea_variable_stack_pop(interpreter,&v);

    arg_count--;

    pea_array_set_int(interpreter,res,arg_count,&v);
  }

  return res;
}


pea_string* pea_date(pea_interpreter* interpreter,char* format) {
  char        buff[2048];
  time_t      t;
  struct  tm* tm;
  char*       d;
  int         l;

  time(&t);

  tm = localtime(&t);

  d = buff;

  while(*format) {
    switch(*format) {
    case 'd':   // Day of the month, 2 digits with leading zeros	01 to 31
      l = sprintf(d,"%02d",tm->tm_mday);
      d += l;
      break;
    case 'D':   // A textual representation of a day, three letters	Mon through Sun
      NYI;
      break;
    case 'j':   // Day of the month without leading zeros	1 to 31
      l = sprintf(d,"%d",tm->tm_mday);
      d += l;
      break;
    case 'l':   // (lowercase 'L')	A full textual representation of the day of the week	Sunday through Saturday
      NYI;
      break;
    case 'S':   // English ordinal suffix for the day of the month, 2 characters	st, nd, rd or th. Works well with j
      NYI;
      break;
    case 'w':   // Numeric representation of the day of the week	0 (for Sunday) through 6 (for Saturday)
      l = sprintf(d,"%d",tm->tm_wday);
      d += l;
      break;
    case 'z':   //The day of the year (starting from 0)	0 through 365
      l = sprintf(d,"%d",tm->tm_yday);
      d += l;
      break;
    case 'W':   //ISO-8601 week number of year, weeks starting on Monday (added in PHP 4.1.0)	Example: 42 (the 42nd week in the year)
      NYI;
      break;
    case 'F':   //A full textual representation of a month, such as January or March	January through December
      NYI;
      break;
    case 'm':   //Numeric representation of a month, with leading zeros	01 through 12
      l = sprintf(d,"%02d",tm->tm_mon+1);
      d += l;
      break;
    case 'M':   //A short textual representation of a month, three letters	Jan through Dec
      NYI;
      break;
    case 'n':   //Numeric representation of a month, without leading zeros	1 through 12
      l = sprintf(d,"%d",tm->tm_mon+1);
      d += l;
      break;
    case 't':   //Number of days in the given month	28 through 31
      NYI;
      break;
    case 'L':   //Whether it's a leap year	1 if it is a leap year, 0 otherwise.
      NYI;
      break;
    case 'o':   //ISO-8601 year number. This has the same value as Y, except that if the ISO week number (W) belongs to the previous or next year, that year is used instead. (added in PHP 5.1.0)	Examples: 1999 or 2003
      NYI;
      break;
    case 'Y':   //A full numeric representation of a year, 4 digits	Examples: 1999 or 2003
      l = sprintf(d,"%04d",tm->tm_year + 1900);
      d += l;
      break;
    case 'y':   //A two digit representation of a year	Examples: 99 or 03
      if (tm->tm_year > 100) {
        l = sprintf(d,"%02d",tm->tm_year - 100);
      } else {
        l = sprintf(d,"%02d",tm->tm_year);
      }
      d += l;
      break;
    case 'a':   //Lowercase Ante meridiem and Post meridiem	am or pm
      NYI;
      break;
    case 'A':   //Uppercase Ante meridiem and Post meridiem	AM or PM
      NYI;
      break;
    case 'B':   //Swatch Internet time	000 through 999
      NYI;
      break;
    case 'g':   //12-hour format of an hour without leading zeros	1 through 12
      l = sprintf(d,"%d",(tm->tm_hour + 1) % 12);
      d += l;
      break;
    case 'G':   //24-hour format of an hour without leading zeros	0 through 23
      l = sprintf(d,"%d",tm->tm_hour);
      d += l;
      break;
    case 'h':   //12-hour format of an hour with leading zeros	01 through 12
      l = sprintf(d,"%d",(tm->tm_hour + 1) % 12);
      d += l;
      break;
    case 'H':   //24-hour format of an hour with leading zeros	00 through 23
      l = sprintf(d,"%d",tm->tm_hour);
      d += l;
      break;
    case 'i':   //Minutes with leading zeros	00 to 59
      l = sprintf(d,"%02d",tm->tm_min);
      d += l;
      break;
    case 's':   //Seconds, with leading zeros	00 through 59
      l = sprintf(d,"%02d",tm->tm_sec);
      d += l;
      break;
    case 'e':   //Timezone identifier (added in PHP 5.1.0)	Examples: UTC, GMT, Atlantic/Azores
      NYI;
      break;
    case 'I':   //(capital i)	Whether or not the date is in daylights savings time	1 if Daylight Savings Time, 0 otherwise.
      NYI;
      break;
    case 'O':   //Difference to Greenwich time (GMT) in hours	Example: +0200
      NYI;
      break;
    case 'T':   //Timezone setting of this machine	Examples: EST, MDT ...
      NYI;
      break;
    case 'Z':   //Timezone offset in seconds. The offset for timezones west of UTC is always negative, and for those east of UTC is always positive.	-43200 through 43200
      NYI;
      break;
    case 'c':   //ISO 8601 date (added in PHP 5)	2004-02-12T15:19:21+00:00
      NYI;
      break;
    case 'r':   //RFC 2822 formatted date	Example: Thu, 21 Dec 2000 16:01:07 +0200
      NYI;
      break;
    case 'U':   //Seconds since the Unix Epoch (January 1 1970 00:00:00 GMT)
      NYI;
      break;
    default:
      *d++ = *format;
      break;
    }
    format++;
  }
  *d = 0;
  return pea_string_alloc(interpreter,0,buff);
}

int pea_rtl_lang(pea_interpreter* interpreter) {
  pea_function_alloc_native(interpreter,NULL,"salir","i",pea_exit);
  pea_function_alloc_native(interpreter,NULL,"arreglo","rv",pea_new_array);
  pea_function_alloc_native(interpreter,NULL,"eval","iS",pea_eval);
  pea_function_alloc_native(interpreter,NULL,"fecha","sS",pea_date);
  return 0;
}
