/* str.c -- 
 * Created: Fri Aug  8 15:42:10 2003 by vle@gmx.net
 * Copyright 2003 Aleksey Cheusov <vle@gmx.net>
 * This program comes with ABSOLUTELY NO WARRANTY.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 1, or (at your option) any
 * later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "str.h"

#include <ctype.h>
#include <wctype.h>
#include <errno.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
  Copy alphanumeric and space characters converting them to lower case.
  Strings are encoded using 8-bit character set.
*/
static int tolower_alnumspace_8bit (
   const char *src, char *dest,
   int allchars_mode,
   int cs_mode)
{
   int c;

   for (; *src; ++src) {
      c = * (const unsigned char *) src;

      if (isspace (c)) {
         *dest++ = ' ';
      }else if (allchars_mode || isalnum (c)){
	 if (!cs_mode)
	    c = tolower (c);

	 *dest++ = c;
      }
   }

   *dest = '\0';
   return 0;
}

/*
  Copies alphanumeric and space characters converting them to lower case.
  Strings are UTF-8 encoded.
*/
static int tolower_alnumspace_utf8 (
   const char *src, char *dest,
   int allchars_mode,
   int cs_mode)
{
   wchar_t      ucs4_char;
   size_t len;
   int    len2;

   mbstate_t ps;
   mbstate_t ps2;

   memset (&ps,  0, sizeof (ps));
   memset (&ps2, 0, sizeof (ps2));

   while (src && src [0]){
      len = mbrtowc (&ucs4_char, src, MB_CUR_MAX, &ps);
      if ((int) len < 0)
	 return errno;

      if (iswspace (ucs4_char)){
	 *dest++ = ' ';
      }else if (allchars_mode || iswalnum (ucs4_char)){
	 if (!cs_mode)
	    ucs4_char = towlower (ucs4_char);

	 len2 = wcrtomb (dest, ucs4_char, &ps2);
	 if (len2 < 0)
	    return errno;

	 dest += len2;
      }

      src += len;
   }

   *dest = 0;

   assert (strlen (src) == strlen (dest));

   return (src == NULL);
}

/* returns 0 if failed */
int tolower_alnumspace (
   const char *src, char *dest,
   int allchars_mode,
   int cs_mode,
   int utf8_mode)
{
   if (utf8_mode){
      return tolower_alnumspace_utf8 (src, dest, allchars_mode, cs_mode);
   }else{
      return tolower_alnumspace_8bit (src, dest, allchars_mode, cs_mode);
   }
}

char *strlwr_8bit (char *str)
{
   char *p;
   for (p = str; *p; ++p){
      *p = tolower ((unsigned char) *p);
   }

   return str;
}

char *copy_utf8_string (
   const char *src,
   char *dest,
   size_t len)
{
   size_t i;
   const char *p;

   for (i=0; i < len; ++i){
      p = src + i * (MB_CUR_MAX + 1);

      while (*p){
	 *dest++ = *p++;
      }
   }

   *dest = 0;
   return dest;
}
