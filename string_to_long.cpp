/*
https://sourceware.org/git/?p=glibc.git;a=blob;f=stdlib/strtol_l.c;h=dc47608b0c1ede85f57d8c2220a8a41b6c2c8f08;hb=master
*/


/* Convert NPTR to an `unsigned long int' or `long int' in base BASE.
   If BASE is 0 the base is determined by the presence of a leading
   zero, indicating octal or a leading "0x" or "0X", indicating hexadecimal.
   If BASE is < 2 or > 36, it is reset to 10.
   If ENDPTR is not NULL, a pointer to the character after the last
   one converted is stored in *ENDPTR.  */

INT
INTERNAL (__strtol_l) (nptr, endptr, base, group, loc)
     const STRING_TYPE *nptr;
     STRING_TYPE **endptr;
     int base;
     int group;
     __locale_t loc;
{
  int negative;
  unsigned LONG int cutoff;
  unsigned int cutlim;
  unsigned LONG int i;
  const STRING_TYPE *s;
  UCHAR_TYPE c;
  const STRING_TYPE *save, *end;
  int overflow;
#ifndef USE_WIDE_CHAR
  size_t cnt;
#endif

#ifdef USE_NUMBER_GROUPING
  struct __locale_data *current = loc->__locales[LC_NUMERIC];
  /* The thousands character of the current locale.  */
# ifdef USE_WIDE_CHAR
  wchar_t thousands = L'\0';
# else
  const char *thousands = NULL;
  size_t thousands_len = 0;
# endif
  /* The numeric grouping specification of the current locale,
     in the format described in <locale.h>.  */
  const char *grouping;

  if (__glibc_unlikely (group))
    {
      grouping = _NL_CURRENT (LC_NUMERIC, GROUPING);
      if (*grouping <= 0 || *grouping == CHAR_MAX)
	grouping = NULL;
      else
	{
	  /* Figure out the thousands separator character.  */
# ifdef USE_WIDE_CHAR
#  ifdef _LIBC
	  thousands = _NL_CURRENT_WORD (LC_NUMERIC,
					_NL_NUMERIC_THOUSANDS_SEP_WC);
#  endif
	  if (thousands == L'\0')
	    grouping = NULL;
# else
#  ifdef _LIBC
	  thousands = _NL_CURRENT (LC_NUMERIC, THOUSANDS_SEP);
#  endif
	  if (*thousands == '\0')
	    {
	      thousands = NULL;
	      grouping = NULL;
	    }
# endif
	}
    }
  else
    grouping = NULL;
#endif

  if (base < 0 || base == 1 || base > 36)
    {
      __set_errno (EINVAL);
      return 0;
    }

  save = s = nptr;

  /* Skip white space.  */
  while (ISSPACE (*s))
    ++s;
  if (__glibc_unlikely (*s == L_('\0')))
    goto noconv;

  /* Check for a sign.  */
  negative = 0;
  if (*s == L_('-'))
    {
      negative = 1;
      ++s;
    }
  else if (*s == L_('+'))
    ++s;

  /* Recognize number prefix and if BASE is zero, figure it out ourselves.  */
  if (*s == L_('0'))
    {
      if ((base == 0 || base == 16) && TOUPPER (s[1]) == L_('X'))
	{
	  s += 2;
	  base = 16;
	}
      else if (base == 0)
	base = 8;
    }
  else if (base == 0)
    base = 10;

  /* Save the pointer so we can check later if anything happened.  */
  save = s;

#ifdef USE_NUMBER_GROUPING
  if (base != 10)
    grouping = NULL;

  if (__glibc_unlikely (grouping != NULL))
    {
# ifndef USE_WIDE_CHAR
      thousands_len = strlen (thousands);
# endif

      /* Find the end of the digit string and check its grouping.  */
      end = s;
      if (
# ifdef USE_WIDE_CHAR
	  *s != thousands
# else
	  ({ for (cnt = 0; cnt < thousands_len; ++cnt)
	       if (thousands[cnt] != end[cnt])
		 break;
	     cnt < thousands_len; })
# endif
	  )
	{
	  for (c = *end; c != L_('\0'); c = *++end)
	    if (((STRING_TYPE) c < L_('0') || (STRING_TYPE) c > L_('9'))
# ifdef USE_WIDE_CHAR
		&& (wchar_t) c != thousands
# else
		&& ({ for (cnt = 0; cnt < thousands_len; ++cnt)
		      if (thousands[cnt] != end[cnt])
			break;
		      cnt < thousands_len; })
# endif
		&& (!ISALPHA (c)
		    || (int) (TOUPPER (c) - L_('A') + 10) >= base))
	      break;

# ifdef USE_WIDE_CHAR
	  end = __correctly_grouped_prefixwc (s, end, thousands, grouping);
# else
	  end = __correctly_grouped_prefixmb (s, end, thousands, grouping);
# endif
	}
    }
  else
#endif
    end = NULL;

  /* Avoid runtime division; lookup cutoff and limit.  */
  cutoff = cutoff_tab[base - 2];
  cutlim = cutlim_tab[base - 2];

  overflow = 0;
  i = 0;
  c = *s;
  if (sizeof (long int) != sizeof (LONG int))
    {
      unsigned long int j = 0;
      unsigned long int jmax = jmax_tab[base - 2];

      for (;c != L_('\0'); c = *++s)
	{
	  if (s == end)
	    break;
	  if (c >= L_('0') && c <= L_('9'))
	    c -= L_('0');
#ifdef USE_NUMBER_GROUPING
# ifdef USE_WIDE_CHAR
	  else if (grouping && (wchar_t) c == thousands)
	    continue;
# else
	  else if (thousands_len)
	    {
	      for (cnt = 0; cnt < thousands_len; ++cnt)
		if (thousands[cnt] != s[cnt])
		  break;
	      if (cnt == thousands_len)
		{
		  s += thousands_len - 1;
		  continue;
		}
	      if (ISALPHA (c))
		c = TOUPPER (c) - L_('A') + 10;
	      else
		break;
	    }
# endif
#endif
	  else if (ISALPHA (c))
	    c = TOUPPER (c) - L_('A') + 10;
	  else
	    break;
	  if ((int) c >= base)
	    break;
	  /* Note that we never can have an overflow.  */
	  else if (j >= jmax)
	    {
	      /* We have an overflow.  Now use the long representation.  */
	      i = (unsigned LONG int) j;
	      goto use_long;
	    }
	  else
	    j = j * (unsigned long int) base + c;
	}

      i = (unsigned LONG int) j;
    }
  else
    for (;c != L_('\0'); c = *++s)
      {
	if (s == end)
	  break;
	if (c >= L_('0') && c <= L_('9'))
	  c -= L_('0');
#ifdef USE_NUMBER_GROUPING
# ifdef USE_WIDE_CHAR
	else if (grouping && (wchar_t) c == thousands)
	  continue;
# else
	else if (thousands_len)
	  {
	    for (cnt = 0; cnt < thousands_len; ++cnt)
	      if (thousands[cnt] != s[cnt])
		break;
	    if (cnt == thousands_len)
	      {
		s += thousands_len - 1;
		continue;
	      }
	    if (ISALPHA (c))
	      c = TOUPPER (c) - L_('A') + 10;
	    else
	      break;
	  }
# endif
#endif
	else if (ISALPHA (c))
	  c = TOUPPER (c) - L_('A') + 10;
	else
	  break;
	if ((int) c >= base)
	  break;
	/* Check for overflow.  */
	if (i > cutoff || (i == cutoff && c > cutlim))
	  overflow = 1;
	else
	  {
	  use_long:
	    i *= (unsigned LONG int) base;
	    i += c;
	  }
      }

  /* Check if anything actually happened.  */
  if (s == save)
    goto noconv;

  /* Store in ENDPTR the address of one character
     past the last character we converted.  */
  if (endptr != NULL)
    *endptr = (STRING_TYPE *) s;

#if !UNSIGNED
  /* Check for a value that is within the range of
     `unsigned LONG int', but outside the range of `LONG int'.  */
  if (overflow == 0
      && i > (negative
	      ? -((unsigned LONG int) (STRTOL_LONG_MIN + 1)) + 1
	      : (unsigned LONG int) STRTOL_LONG_MAX))
    overflow = 1;
#endif

  if (__glibc_unlikely (overflow))
    {
      __set_errno (ERANGE);
#if UNSIGNED
      return STRTOL_ULONG_MAX;
#else
      return negative ? STRTOL_LONG_MIN : STRTOL_LONG_MAX;
#endif
    }

  /* Return the result of the appropriate sign.  */
  return negative ? -i : i;

noconv:
  /* We must handle a special case here: the base is 0 or 16 and the
     first two characters are '0' and 'x', but the rest are no
     hexadecimal digits.  This is no error case.  We return 0 and
     ENDPTR points to the `x`.  */
  if (endptr != NULL)
    {
      if (save - nptr >= 2 && TOUPPER (save[-1]) == L_('X')
	  && save[-2] == L_('0'))
	*endptr = (STRING_TYPE *) &save[-1];
      else
	/*  There was no number to convert.  */
	*endptr = (STRING_TYPE *) nptr;
    }

  return 0L;
}
#if defined _LIBC && !defined USE_WIDE_CHAR
libc_hidden_def (INTERNAL (__strtol_l))
#endif

/* External user entry point.  */

#if _LIBC - 0 == 0

/* Prototype.  */
extern INT __strtol_l (const STRING_TYPE *nptr, STRING_TYPE **endptr,
		       int base);
#endif


INT
#ifdef weak_function
weak_function
#endif
__strtol_l (nptr, endptr, base, loc)
     const STRING_TYPE *nptr;
     STRING_TYPE **endptr;
     int base;
     __locale_t loc;
{
  return INTERNAL (__strtol_l) (nptr, endptr, base, 0, loc);
}
libc_hidden_def (__strtol_l)
weak_alias (__strtol_l, strtol_l)

/*

*/
public long stringToLong(String str) {
            if (str==null||str.length()==0){
                return 0;
            }
            
            int sign=1;
            Long sum=(long) 0;
            int i=0;
            
            while(i<str.length()&&str.charAt(i)==' '){
                i++;
            }
            
            if (i==str.length()){
                return 0;
            }
            
            if (str.charAt(i)=='+'){
                sign=1;
                i++;
            }
            else if (str.charAt(i)=='-'){
                sign=-1;
                i++;
            }

            while (i<str.length()){
                if (str.charAt(i)>='0'&&str.charAt(i)<='9'){
                    if (sign>=0){
                       if ((Long.MAX_VALUE-(str.charAt(i)-'0'))/10<=sum){
                            return Long.MAX_VALUE;
                        }
                        sum=sum*10+(str.charAt(i)-'0');
                    }
                    else{
                        if ((Long.MIN_VALUE+(str.charAt(i)-'0'))/10>sum){
                            return Long.MIN_VALUE;
                        }
                        sum=sum*10-(str.charAt(i)-'0');
                    }
                }
                else{
                    return sum;
                }
                
                i++;
            }
            return sum;
        }