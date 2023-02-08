#include "utl.h"

#include "s21_string.h"

//--------------------------------------------------------sprintf-----------------------------------------------------------

bool is_digit(char str) { return str >= '0' && str <= '9'; }

bool is_specifier(char str) {
  return str == 'c' || str == 'd' || str == 'i' || str == 'e' || str == 'E' ||
         str == 'f' || str == 'g' || str == 'G' || str == 'o' || str == 's' ||
         str == 'u' || str == 'x' || str == 'X' || str == 'p' || str == 'n' ||
         str == '%';
}

bool is_width(char str) { return is_digit(str) || str == '*'; }

bool is_precision(char str) { return str == '.'; }

bool is_flag(char str) {
  return str == '-' || str == '+' || str == ' ' || str == '#' || str == '0';
}

bool is_length(char str) { return str == 'h' || str == 'l' || str == 'L'; }

unsigned int get_flag(char** str) {  // func should return flags  as bit flags
  unsigned int flags = 0U;
  switch (**str) {
    case '-':
      flags |= FLAG_MINUS;
      break;
    case '+':
      flags |= FLAG_PLUS;
      break;
    case ' ':
      flags |= FLAG_SPACE;
      break;
    case '#':
      flags |= FLAG_SHARP;
      break;
    case '0':
      flags |= FLAG_ZERO;
      break;
  }
  (*str)++;
  return flags;
}

int get_width(char** str) {  // func should return number of width or -1 if
                             // number of width is in va_list
  int num = 0;
  if (**str == '*') {
    num = -1;
    (*str)++;
  } else
    while (is_digit(**str)) {
      num *= 10;
      num += (**str - '0');
      (*str)++;
    }
  return num;
}

int get_precision(char** str) {  // func should return number of precision or -1
                                 // if number of precision is in va_list
  int num = 0;
  (*str)++;
  if (**str == '*') {
    num = -1;
    (*str)++;
  } else
    while (is_digit(**str)) {
      num *= 10;
      num += (**str - '0');
      (*str)++;
    }
  return num;
}

char* s21_itoa(const long long num,
               char* str) {  // we use this func to converts int to string
  int dig = 0, i = 0;

  unsigned long int itoa_num = labs(num);

  i = dig_num(itoa_num);
  itoa_num = labs(num);
  str = str + i;
  *str-- = '\0';
  for (int j = 0; j < i - 1; j++) {
    dig = itoa_num % 10;
    itoa_num = itoa_num / 10;
    *str-- = 48 + dig;
  }
  dig = itoa_num % 10;
  *str-- = 48 + dig;
  return str + i + 1;
}

char* s21_hexitoa(char base, const long num, char* str) {
  int dig = 0, i = 0;

  unsigned long int itoa_num = num;
  i = hexdig_num(itoa_num);
  str = str + i;
  *str-- = '\0';
  for (int j = 0; j < i - 1; j++) {
    dig = itoa_num % 16;
    itoa_num = itoa_num / 16;
    if (dig > 9) {
      *str-- = base == 'x' ? 87 + dig : 55 + dig;
    } else {
      *str-- = 48 + dig;
    }
  }

  dig = itoa_num % 16;
  if (dig > 9) {
    *str-- = base == 'x' ? 87 + dig : 55 + dig;
  } else {
    *str-- = 48 + dig;
  }
  return str + i + 1;
}

char* s21_octitoa(const long num, char* str) {
  int dig = 0, i = 0;

  unsigned long int itoa_num = labs(num);
  i = octdig_num(itoa_num);
  itoa_num = labs(num);
  str = str + i;
  *str-- = '\0';
  for (int j = 0; j < i - 1; j++) {
    dig = itoa_num % 8;
    itoa_num = itoa_num / 8;
    *str-- = 48 + dig;
  }

  dig = itoa_num % 8;
  *str-- = 48 + dig;
  return str + i + 1;
}

int dig_num(unsigned long int num) {
  int i = 0;
  if (num == 0) i = 1;
  for (; num > 0; num /= 10, i++)
    ;
  return i;
}

int hexdig_num(long unsigned int num) {
  int i = 0;
  if (num == 0) i = 1;
  for (; num > 0; num /= 16, i++)
    ;
  return i;
}

int octdig_num(long unsigned int num) {
  int i = 0;
  if (num == 0) i = 1;
  for (; num > 0; num /= 8, i++)
    ;
  return i;
}

int floatdig_num(long double trg) {
  int digits_before_point = 0;
  if (trg == 0) {
    digits_before_point++;
  }
  while (trg != 0) {
    trg /= 10;
    modfl(trg, &trg);
    digits_before_point++;
  }
  return digits_before_point;
}

char* get_specifier(char* str, char* format_str, unsigned int flags, int width,
                    int precision, char length, unsigned int* num,
                    va_list parlist) {
  char* buffstring;
  int* nspec;
  switch (*format_str) {  // specifier
    case 's':             // SPECIFIER
      buffstring = va_arg(parlist, char*);
      str = str_out(str, buffstring, width, precision, num, flags);
      break;
    case 'p':  // SPECIFIER
      str = ptr_out(str, va_arg(parlist, s21_intptr_t), width, precision, num,
                    flags);
      break;
    case 'i':
    case 'd':  // SPECIFIER
      str = int_out(str, va_arg(parlist, long int), width, precision, length,
                    num, flags);
      break;
    case 'o':
    case 'x':
    case 'X':
    case 'u':  // SPECIFIER
      str = uint_out(*format_str, str, va_arg(parlist, long unsigned int),
                     width, precision, length, num, flags);
      break;
    case 'c':  // SPECIFIER
      str = spec_char_out(str, va_arg(parlist, int), width, num, flags);
      break;
    case '%':  // SPECIFIER
      str = spec_char_out(str, '%', width, num, flags);
      break;
    case 'f':
      if (length == 'L') {
        str = float_out(str, va_arg(parlist, long double), width, precision,
                        num, flags);
      } else {
        str = float_out(str, va_arg(parlist, double), width, precision, num,
                        flags);
      }
      break;
    case 'E':
    case 'e':
      if (length == 'L') {
        str = efloat_out(*format_str, str, va_arg(parlist, long double), width,
                         precision, num, flags);
      } else {
        str = efloat_out(*format_str, str, va_arg(parlist, double), width,
                         precision, num, flags);
      }
      break;
    case 'G':
    case 'g':
      if (length == 'L') {
        str = gfloat_out(*format_str, str, va_arg(parlist, long double), width,
                         precision, num, flags);
      } else {
        str = gfloat_out(*format_str, str, va_arg(parlist, double), width,
                         precision, num, flags);
      }
      break;
    case 'n':
      nspec = va_arg(parlist, int*);
      *nspec = *num;
      break;
    default:
      break;
  }
  return str;
}

char* str_out(
    char* dest_str, char* trg, int width, int precision, unsigned int* num,
    unsigned int flags) {  // func add target string to destonation sting with
                           // width and counting number of printed sym
  char space = ' ';
  if (precision < 0) {
    precision = (int)s21_strlen(trg);
  }
  if (flags & FLAG_ZERO) {
    space = '0';
  }
  width = width > precision ? width - precision : 0;
  if (!(flags & FLAG_MINUS)) {
    while (width-- != 0) {
      dest_str = char_out(dest_str, space, num);
    }
  }
  while (precision-- != 0) {
    dest_str = char_out(dest_str, *trg++, num);
  }
  if (flags & FLAG_MINUS) {
    while (width-- != 0) {
      dest_str = char_out(dest_str, ' ', num);
    }
  }
  return dest_str;
}

char* char_out(char* dest_str, char sym, unsigned int* num) {
  *dest_str++ = sym;
  (*num)++;
  return dest_str;
}

int get_zeros(int width, int precision, int flags) {
  int zeros = 0;
  if (precision <= 0 && (flags & FLAG_ZERO) && !(flags & FLAG_MINUS)) {
    zeros = width;
  } else if (precision > 0) {
    zeros = precision;
  }
  return zeros;
}

int get_spaces(int width, int zeros) {
  int spaces = 0;
  spaces = width - zeros;
  spaces = spaces < 0 ? 0 : spaces;

  return spaces;
}

int get_dig_num(char base, long long int trg) {
  int num = 0;
  if (base == 'x' || base == 'X') {
    num = hexdig_num(trg);
  } else if (base == 'o') {
    num = octdig_num(trg);
  } else {
    num = dig_num(trg);
  }

  return num;
}

char* int_out(char* dest_str, long int trg, int width, int precision,
              char length, unsigned int* num, unsigned int flags) {
  trg = length == 'h'   ? (short int)trg
        : length == 'l' ? (long int)trg
                        : (int)trg;

  char sign = ' ';
  flags |= trg < 0 ? FLAG_PLUS : 0;
  if (flags & FLAG_PLUS) {
    sign = trg < 0 ? '-' : '+';
    width -= 1;
  }
  trg = labs(trg);
  int legth_trg = get_dig_num('d', trg);
  int extra_space = (flags & FLAG_SPACE) && !(flags & FLAG_PLUS) ? 1 : 0;

  width = width - legth_trg - extra_space;
  precision = precision > legth_trg ? precision - legth_trg : -2;

  int zeros = get_zeros(width, precision, flags);
  int spaces = get_spaces(width, zeros);

  dest_str = extra_space_out(extra_space, num, dest_str);
  if (!(flags & FLAG_MINUS)) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  dest_str = sign_out(sign, num, dest_str, flags);
  dest_str = zeros_out(zeros, num, dest_str);
  dest_str = s21_itoa(trg, dest_str);
  if (flags & FLAG_MINUS) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  *num += legth_trg;
  return dest_str;
}

char* uint_out(char base, char* dest_str, long unsigned int trg, int width,
               int precision, char length, unsigned int* num,
               unsigned int flags) {
  trg = length == 'h'   ? (short unsigned int)trg
        : length == 'l' ? (long unsigned int)trg
                        : (unsigned int)trg;

  int legth_trg = get_dig_num(base, trg);

  width = width - legth_trg;
  precision = precision > legth_trg ? precision - legth_trg : 0;
  if (flags & FLAG_SHARP) {
    if (base == 'x' || base == 'X') {
      width -= 2;
    }
  }
  int zeros = get_zeros(width, precision, flags);
  int spaces = get_spaces(width, zeros);

  if (flags & FLAG_SHARP) {
    if (base == 'o') {
      spaces = zeros <= 0 ? spaces - 1 : spaces;
      zeros = zeros <= 0 ? 1 : zeros;
    }
  }

  if (!(flags & FLAG_MINUS)) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  if (flags & FLAG_SHARP) {
    if (base == 'x' || base == 'X') {
      dest_str = char_out(dest_str, '0', num);
      dest_str = char_out(dest_str, base, num);
    }
  }
  dest_str = zeros_out(zeros, num, dest_str);
  if (base == 'x' || base == 'X') {
    dest_str = s21_hexitoa(base, trg, dest_str);
  } else if (base == 'o') {
    dest_str = s21_octitoa(trg, dest_str);
  } else {
    dest_str = s21_itoa(trg, dest_str);
  }
  if (flags & FLAG_MINUS) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  *num += legth_trg;
  return dest_str;
}

char* float_out(char* dest_str, long double trg, int width, int precision,
                unsigned int* num, unsigned int flags) {
  char sign;
  flags |= trg < 0 ? FLAG_PLUS : 0;
  if (flags & FLAG_PLUS) {
    sign = trg < 0 ? '-' : '+';
    width -= 1;
  }
  trg = fabsl(trg);

  precision = precision < 0 ? 6 : precision;

  int extra_space = (flags & FLAG_SPACE) && !(flags & FLAG_PLUS) ? 1 : 0;
  char* str_without_point = (char*)calloc(500, sizeof(char));
  char* str_with_point = (char*)calloc(500, sizeof(char));
  char* without = str_without_point;
  char* with = str_with_point;
  ftos(trg, str_without_point, precision + 1);
  rounding(str_without_point);
  s21_memcpy(str_with_point, str_without_point,
             (s21_strlen(str_without_point) - precision));
  if (precision != 0 || (flags & FLAG_SHARP)) {
    s21_strcat(str_with_point, ".");
  }
  s21_strcat(str_with_point,
             &str_without_point[(s21_strlen(str_without_point) - precision)]);
  *num += s21_strlen(str_with_point);

  width = width - s21_strlen(str_with_point) - extra_space;
  int zeros = (flags & FLAG_ZERO) && !(flags & FLAG_MINUS) ? width : 0;
  int spaces = get_spaces(width, zeros);
  zeros -= spaces;

  dest_str = extra_space_out(extra_space, num, dest_str);
  if (!(flags & FLAG_MINUS)) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  dest_str = sign_out(sign, num, dest_str, flags);
  if (!(flags & FLAG_MINUS)) {
    dest_str = zeros_out(zeros, num, dest_str);
  }
  s21_strcat(dest_str, str_with_point);
  dest_str += s21_strlen(str_with_point);
  if (flags & FLAG_MINUS) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  free(with);
  free(without);
  return dest_str;
}

char* ftos(long double trg, char* str, int precision) {
  unsigned short digit;
  long double before_point = 0.0;
  long double after_point = 0.0;

  char* buffer_after_point = (char*)calloc(315, sizeof(char));
  char* buffer_before_point = (char*)calloc(315, sizeof(char));
  precision++;

  for (int i = 0; i < precision; i++) {
    after_point = trg;
    for (int j = 0; j < precision - i; j++) {
      after_point = modfl(after_point, &before_point) * 10.0;
    }
    digit = after_point;
    if (i != 0) {
      buffer_after_point[precision - i - 1] = '0' + digit;
    }
  }
  buffer_after_point[precision - 1] = '\0';
  int digits_before_point = floatdig_num(trg);
  for (int i = 1; i <= digits_before_point; i++) {
    digit = fmodl(trg, pow(10, i)) / pow(10, i - 1);
    buffer_before_point[digits_before_point - i] = '0' + digit;
  }
  buffer_before_point[digits_before_point + 1] = '\0';

  int length = s21_strlen(buffer_before_point);
  s21_strcpy(str, buffer_before_point);
  str = &(str[length]);
  length = s21_strlen(buffer_after_point);
  s21_strcpy(str, buffer_after_point);
  str = &(str[length - 1]);
  free(buffer_after_point);
  free(buffer_before_point);
  return str;
}

char* zeros_out(int zeros, unsigned int* num, char* dest_str) {
  unsigned int a;
  while (zeros-- > 0) {
    dest_str = char_out(dest_str, '0', num);
  }
  char_out(dest_str, '\0', &a);
  return dest_str;
}
char* spaces_out(int spaces, unsigned int* num, char* dest_str) {
  unsigned int a;
  while (spaces-- > 0) {
    dest_str = char_out(dest_str, ' ', num);
  }
  char_out(dest_str, '\0', &a);
  return dest_str;
}

char* sign_out(char sign, unsigned int* num, char* dest_str,
               unsigned int flags) {
  unsigned int a;
  if (flags & FLAG_PLUS) {
    dest_str = char_out(dest_str, sign, num);
  }
  char_out(dest_str, '\0', &a);
  return dest_str;
}
char* extra_space_out(int extra_space, unsigned int* num, char* dest_str) {
  unsigned int a;
  if (extra_space == 1) {
    dest_str = char_out(dest_str, ' ', num);
  }
  char_out(dest_str, '\0', &a);
  return dest_str;
}

char* rounding(char* str) {
  int rounder = 0;
  int len = (int)s21_strlen(str);
  if (str[len - 1] > '4') {
    rounder = 1;
  }
  str[len - 1] = '\0';
  int i = 2;
  while (rounder == 1 && (len - i) >= 0) {
    str[len - i] += 1;
    if (str[len - i] > 57) {
      str[len - i] = '0';
    } else {
      rounder = 0;
    }
    i++;
  }
  if (rounder == 1) {
    while (len-- != 0) {
      str[len] = str[len - 1];
    }
    str[0] = '1';
  }
  return NULL;
}

char* efloat_out(char spec, char* dest_str, long double trg, int width,
                 int precision, unsigned int* num, unsigned int flags) {
  char sign;
  flags |= trg < 0 ? FLAG_PLUS : 0;
  if (flags & FLAG_PLUS) {
    sign = trg < 0 ? '-' : '+';
    width -= 1;
  }
  trg = fabsl(trg);

  precision = precision < 0 ? 6 : precision;

  int extra_space = (flags & FLAG_SPACE) && !(flags & FLAG_PLUS) ? 1 : 0;
  char* str_without_point = (char*)calloc(1000, sizeof(char));
  char* str_with_point = (char*)calloc(1000, sizeof(char));
  char* without = str_without_point;
  char* with = str_with_point;

  int digits_before_point = (int)trg == 0 ? 0 : floatdig_num(trg) - 1;

  ftos(trg, str_without_point, 300);
  str_without_point = remove_zeros(str_without_point, &digits_before_point);

  str_without_point[precision + 2] = '\0';
  if (s21_strcmp(str_without_point, "") == 0) {
    s21_memset(str_without_point, '0', precision + 2);
    digits_before_point = 0;
  }
  rounding(str_without_point);
  s21_memcpy(str_with_point, str_without_point,
             (s21_strlen(str_without_point) - precision));
  if (precision != 0 || (flags & FLAG_SHARP)) {
    s21_strcat(str_with_point, ".");
  }
  s21_strcat(str_with_point,
             &str_without_point[(s21_strlen(str_without_point) - precision)]);
  *num += s21_strlen(str_with_point);
  width = width - s21_strlen(str_with_point) - extra_space - 2 -
          dig_num(abs(digits_before_point));
  width -= dig_num(abs(digits_before_point)) < 2 ? 1 : 0;
  int zeros = (flags & FLAG_ZERO) && !(flags & FLAG_MINUS) ? width : 0;
  int spaces = get_spaces(width, zeros);
  zeros -= spaces;

  dest_str = extra_space_out(extra_space, num, dest_str);
  if (!(flags & FLAG_MINUS)) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  dest_str = sign_out(sign, num, dest_str, flags);
  if (!(flags & FLAG_MINUS)) {
    dest_str = zeros_out(zeros, num, dest_str);
  }
  s21_strcat(dest_str, str_with_point);
  dest_str += s21_strlen(str_with_point);
  dest_str = sci_out(spec, digits_before_point, num, dest_str);
  if (flags & FLAG_MINUS) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  free(with);
  free(without);
  return dest_str;
}

char* gfloat_out(char spec, char* dest_str, long double trg, int width,
                 int precision, unsigned int* num, unsigned int flags) {
  spec = spec == 'g' ? 'e' : 'E';
  char sign;
  flags |= trg < 0 ? FLAG_PLUS : 0;
  if (flags & FLAG_PLUS) {
    sign = trg < 0 ? '-' : '+';
    width -= 1;
  }
  trg = fabsl(trg);
  bool is_espec = false;
  precision = precision < 0 ? 6 : precision;
  precision = precision == 0 ? 1 : precision;
  int extra_space = (flags & FLAG_SPACE) && !(flags & FLAG_PLUS) ? 1 : 0;

  char* str_without_point = (char*)calloc(500, sizeof(char));
  char* str_with_point = (char*)calloc(500, sizeof(char));
  char* without = str_without_point;
  char* with = str_with_point;
  int digits_before_point = (int)trg == 0 ? 0 : floatdig_num(trg) - 1;
  int a = floatdig_num(trg);
  ftos(trg, str_without_point, 300);
  char* zeros_str = str_without_point;
  int zeros_in_str = 0;
  while (*zeros_str == '0' && zeros_in_str < 5) {
    zeros_str++;
    zeros_in_str++;
  }
  if (zeros_in_str > 4) {
    str_without_point = remove_zeros(str_without_point, &digits_before_point);
    is_espec = true;
  }
  if (precision <= a - 1) {
    is_espec = true;
  }
  if (is_espec == false) {
    str_without_point[precision + 1 + zeros_in_str] = '\0';
    rounding(str_without_point);
    precision += zeros_in_str;
    precision -= a;
  } else {
    str_without_point = remove_zeros(str_without_point, &digits_before_point);
    str_without_point[precision + 1] = '\0';
    if (s21_strcmp(str_without_point, "") == 0) {
      s21_memset(str_without_point, '0', precision + 1);
      digits_before_point = 0;
      is_espec = false;
      precision -= 1;
      precision = precision < 0 ? 0 : precision;
    } else {
      precision -= 1;
      precision = precision < 0 ? 0 : precision;
      width = width - 2 - dig_num(abs(digits_before_point));
      width -= dig_num(abs(digits_before_point)) < 2 ? 1 : 0;
    }
    rounding(str_without_point);
  }
  s21_memcpy(str_with_point, str_without_point,
             (s21_strlen(str_without_point) - precision));
  s21_strcat(str_with_point, ".");
  s21_strcat(str_with_point,
             &str_without_point[(s21_strlen(str_without_point) - precision)]);
  if (!(flags & FLAG_SHARP)) {
    remove_zeros_from_end(s21_strrchr(str_with_point, '\0') - 1);
  }
  if ((*(s21_strrchr(str_with_point, '\0') - 1) == '.') &&
      !(flags & FLAG_SHARP)) {
    *(s21_strrchr(str_with_point, '\0') - 1) = '\0';
  }
  width = width - s21_strlen(str_with_point) - extra_space;
  int zeros = (flags & FLAG_ZERO) && !(flags & FLAG_MINUS) ? width : 0;
  int spaces = get_spaces(width, zeros);
  zeros -= spaces;
  dest_str = extra_space_out(extra_space, num, dest_str);
  if (!(flags & FLAG_MINUS)) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  dest_str = sign_out(sign, num, dest_str, flags);
  if (!(flags & FLAG_MINUS)) {
    dest_str = zeros_out(zeros, num, dest_str);
  }
  s21_strcat(dest_str, str_with_point);
  dest_str += s21_strlen(str_with_point);
  if (is_espec == true) {
    dest_str = sci_out(spec, digits_before_point, num, dest_str);
  }
  if (flags & FLAG_MINUS) {
    dest_str = spaces_out(spaces, num, dest_str);
  }
  *num += s21_strlen(str_with_point);
  free(with);
  free(without);
  return dest_str;
}

char* remove_zeros(char* str, int* num) {
  while (*str == '0') {
    str++;
    (*num)--;
  }
  return str;
}

void remove_zeros_from_end(char* str) {
  while (*str == '0') {
    *str = '\0';
    str--;
  }
}

char* sci_out(char spec, int digits_before_point, unsigned int* num,
              char* dest_str) {
  *num += s21_sprintf(dest_str, "%c%+03d", spec, digits_before_point);
  dest_str += s21_strlen(dest_str);
  return dest_str;
}

char* spec_char_out(char* dest_str, char sym, int width, unsigned int* num,
                    unsigned int flags) {
  char space = ' ';
  if (flags & FLAG_ZERO) {
    space = '0';
  }
  width--;
  if (!(flags & FLAG_MINUS)) {
    while (width-- > 0) {
      dest_str = char_out(dest_str, space, num);
    }
  }
  dest_str = char_out(dest_str, sym, num);
  if (flags & FLAG_MINUS) {
    while (width-- > 0) {
      dest_str = char_out(dest_str, ' ', num);
    }
  }
  return dest_str;
}

char* ptr_out(char* dest_str, s21_intptr_t adress, int width, int precision,
              unsigned int* num, unsigned int flags) {
  int zeros, spaces = 0;
  char s[2 * sizeof(adress)];
  if (adress) {
    // вычисляю адрес
    for (int i = 2 * sizeof(adress) - 1; i >= 0; --i) {
      s[i] = "0123456789abcdef"[adress & 0x0F];
      adress >>= 4;
    }
    // подстравиваю адрес под нас
    char* adresswidth = s + 4;
    *(adresswidth + 12) = '\0';
    *(adresswidth + 12) = '\0';
    width -= 14;
    precision -= 12;
    zeros = get_zeros(width, precision, flags);
    spaces = get_spaces(width, zeros);

    if (!(flags & FLAG_MINUS)) {
      dest_str = spaces_out(spaces, num, dest_str);
    }
    dest_str = char_out(dest_str, '0', num);
    dest_str = char_out(dest_str, 'x', num);
    dest_str = zeros_out(zeros, num, dest_str);
    s21_strcat(dest_str, adresswidth);
    dest_str = &dest_str[12];
    if (flags & FLAG_MINUS) {
      dest_str = spaces_out(spaces, num, dest_str);
    }
    *num += 12;
  } else if (!adress) {
    width = width - 2;
    if (precision < 0 && (flags & FLAG_ZERO) && !(flags & FLAG_MINUS) &&
        width > 0) {
      zeros = width;
    } else if (precision > 0) {
      zeros = precision;
    } else {
      zeros = 1;
    }
    spaces = get_spaces(width, zeros);

    if (!(flags & FLAG_MINUS)) {
      dest_str = spaces_out(spaces, num, dest_str);
    }
    dest_str = char_out(dest_str, '0', num);
    dest_str = char_out(dest_str, 'x', num);
    dest_str = zeros_out(zeros, num, dest_str);
    if (flags & FLAG_MINUS) {
      dest_str = spaces_out(spaces, num, dest_str);
    }
  }
  return dest_str;
}

//--------------------------------------------------------sscanf-----------------------------------------------------------

char* get_string(Specifiers* spec, char* arg, char* str) {
  int count = 0;
  for (char* p = str; *p != ' ' && *p != '\0' && *p != '\n' && *p != '\t' &&
                      (spec->width != count || spec->width == 0);
       p++, arg++, count++) {
    if (!spec->star_flag) {
      *arg = *p;
    }
  }
  spec->count_of_characters += count;
  if (!spec->star_flag) *arg = '\0';
  return str + count;
}

char* get_int(Specifiers* spec, char* str, int* flag) {
  char* ptr = s21_NULL;
  int fl = 0;
  int negative;
  str = negative_check(spec, str, &fl);  // проверка на отрицание
  negative = fl ? -1 : 1;
  if (*str == '0' &&
      (*(str + 1) == 'X' ||
       *(str + 1) ==
           'x')) {  //получаем из строки число в любой системе счисления
    spec->result_strtol = strtoll(str, &ptr, 16) * negative;
  } else if ((*str == '0' && isdigit(*(str + 1)))) {
    spec->result_strtol = strtoll(str, &ptr, 8) * negative;
  } else if ((*str != '0' && isdigit(*str)) ||
             (*str == '0' && !isdigit(*(str + 1)))) {
    spec->result_strtol = strtoll(str, &ptr, 10) * negative;
  } else if (!isdigit(*str)) {
    *flag = 1;
    ptr = str;
  }
  spec->count_of_characters += s21_strlen(str) - s21_strlen(ptr);
  return ptr;
}

void removing_spaces(Specifiers* spec, char** str) {
  // пропуск пробелов
  while (**str == ' ' || **str == '\n' || **str == '\t') {
    (*str)++;
    spec->count_of_characters++;
  }
}

char* negative_check(Specifiers* spec, char* str, int* num) {
  // проверка на отрицание
  if (*str == '-') {
    *num = -1;
    str++;
    spec->count_of_characters++;
  } else if (*str == '+') {
    str++;
    spec->count_of_characters++;
  }
  return str;
}

unsigned long long int get_unsigned_int(Specifiers* spec, int* error,
                                        char** str) {
  // получаем из строки положительное число
  char* ptr = *str;
  unsigned long long int num = strtoull(*str, str, spec->base);
  if (num == 0 && ptr == *str) {
    *error = 1;
  }
  return num;
}

char* format_parsing(Specifiers* spec, char* str) {
  // парсинг спецификаторов/длинны/ширины
  int zero = '0';
  while (1) {
    if (*str == '*') {
      spec->star_flag = 1;
      str++;
    }
    if (isdigit(*str)) {
      spec->width = spec->width * 10 + ((int)*str - zero);
      str++;
    }
    if (*str == 'h') {
      spec->lenght_with_h = 1;
      str++;
    }
    if (*str == 'l') {
      spec->lenght_with_l = 1;
      str++;
    }
    if (*str == 'L') {
      spec->lenght_with_L = 1;
      str++;
    }
    if (*(str + 1) == '\0' || *(str + 1) == '%') break;
  }
  return str;
}

char* get_pointer(Specifiers* spec, char* str, int* error) {
  char buffer[4096] = "0x";
  char* string = buffer;
  int len = s21_strlen(str);
  long num;
  while (*str == ' ' || *str == '\n' || *str == '\t') {
    str++;
  }
  if (*str == '0' && *(str + 1) == 'x') {
    num = (long)strtol(str, &str, 16);
    if (num != 0)
      *spec->p_spec = (void*)num;
    else {
      *error = 1;
    }
  } else {
    string = s21_strcat(string, str);
    num = (long)strtol(string, &string, 16);
    if (num != 0) {
      *spec->p_spec = (void*)num;
      str = string;
    } else {
      *error = 1;
    }
  }
  spec->count_of_characters += len - s21_strlen(str);
  return str;
}