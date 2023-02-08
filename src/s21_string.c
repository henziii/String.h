#include "s21_string.h"

#include "utl.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result;
  result = 0;
  for (s21_size_t num = 0; n > num; num += 1) {
    if (*((unsigned char *)str1 + num) != *((unsigned char *)str2 + num)) {
      result = *((unsigned char *)str1 + num) - *((unsigned char *)str2 + num);
      break;
    }
  }
  return result;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result = s21_NULL;
  for (s21_size_t num = 0; n > num; num += 1) {
    if (*((unsigned char *)str + num) == (int unsigned)c) {
      result = ((unsigned char *)str + num);
      break;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *current_mem_ptr = (unsigned char *)dest;
  for (s21_size_t num = 0; n > num; num++) {
    *current_mem_ptr++ = *((unsigned char *)src + num);
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *current_mem = dest;
  unsigned const char *source = src;
  if (current_mem < source) {
    while (n--) {
      *current_mem = *source;
      current_mem++;
      source++;
    }
  } else {
    source = source + (n - 1);
    current_mem = current_mem + (n - 1);
    while (n--) {
      *current_mem = *source;
      current_mem = current_mem - 1;
      source = source - 1;
    }
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *res = (unsigned char *)str;
  while (n--) {
    *res++ = c;
  }
  return str;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t res = 0;
  while (*str) {
    res++;
    str++;
  }
  return res;
}

char *s21_strcat(char *dest, const char *src) {
  char *str = dest;
  str = str + s21_strlen(dest);
  while (*src) {
    *str++ = *src++;
  }
  *str = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *str = dest;
  str = str + s21_strlen(dest);
  while (*src && n--) {
    *str++ = *src++;
  }
  *str = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  while (*(str + i) != '\0' && *(str + i) != c) {
    i += 1;
  }
  return str[i] ? (char *)(str + i) : s21_NULL;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*(str1) && *(str2) && *str1 == *str2) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  while (--n && *(str1) && *(str2) && *str1 == *str2) {
    str1++;
    str2++;
  }
  return *(char *)str1 - *(char *)str2;
}

char *s21_strcpy(char *dest, const char *src) {
  char *res = dest;
  s21_size_t len_wtih_zero_src = s21_strlen(src) + 1;
  s21_size_t index = 0;
  while (len_wtih_zero_src > index) {
    res[index] = src[index];
    index += 1;
  }
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *res = dest;
  s21_size_t len_wtih_zero_src = s21_strlen(src) + 1;
  s21_size_t index = 0;
  while (n-- && len_wtih_zero_src > index) {
    res[index] = src[index];
    index += 1;
  }
  return dest;
}

char *s21_strerror(int errnum) {
#ifdef __APPLE__
  const char *arr[] = {
      [0] = "Undefined error: 0",
      [1] = "Operation not permitted",
      [2] = "No such file or directory",
      [3] = "No such process",
      [4] = "Interrupted system call",
      [5] = "Input/output error",
      [6] = "Device not configured",
      [7] = "Argument list too long",
      [8] = "Exec format error",
      [9] = "Bad file descriptor",
      [10] = "No child processes",
      [11] = "Resource deadlock avoided",
      [12] = "Cannot allocate memory",
      [13] = "Permission denied",
      [14] = "Bad address",
      [15] = "Block device required",
      [16] = "Resource busy",
      [17] = "File exists",
      [18] = "Cross-device link",
      [19] = "Operation not supported by device",
      [20] = "Not a directory",
      [21] = "Is a directory",
      [22] = "Invalid argument",
      [23] = "Too many open files in system",
      [24] = "Too many open files",
      [25] = "Inappropriate ioctl for device",
      [26] = "Text file busy",
      [27] = "File too large",
      [28] = "No space left on device",
      [29] = "Illegal seek",
      [30] = "Read-only file system",
      [31] = "Too many links",
      [32] = "Broken pipe",
      [33] = "Numerical argument out of domain",
      [34] = "Result too large",
      [35] = "Resource temporarily unavailable",
      [36] = "Operation now in progress",
      [37] = "Operation already in progress",
      [38] = "Socket operation on non-socket",
      [39] = "Destination address required",
      [40] = "Message too long",
      [41] = "Protocol wrong type for socket",
      [42] = "Protocol not available",
      [43] = "Protocol not supported",
      [44] = "Socket type not supported",
      [45] = "Operation not supported",
      [46] = "Protocol family not supported",
      [47] = "Address family not supported by protocol family",
      [48] = "Address already in use",
      [49] = "Can't assign requested address",
      [50] = "Network is down",
      [51] = "Network is unreachable",
      [52] = "Network dropped connection on reset",
      [53] = "Software caused connection abort",
      [54] = "Connection reset by peer",
      [55] = "No buffer space available",
      [56] = "Socket is already connected",
      [57] = "Socket is not connected",
      [58] = "Can't send after socket shutdown",
      [59] = "Too many references: can't splice",
      [60] = "Operation timed out",
      [61] = "Connection refused",
      [62] = "Too many levels of symbolic links",
      [63] = "File name too long",
      [64] = "Host is down",
      [65] = "No route to host",
      [66] = "Directory not empty",
      [67] = "Too many processes",
      [68] = "Too many users",
      [69] = "Disc quota exceeded",
      [70] = "Stale NFS file handle",
      [71] = "Too many levels of remote in path",
      [72] = "RPC struct is bad",
      [73] = "RPC version wrong",
      [74] = "RPC prog. not avail",
      [75] = "Program version wrong",
      [76] = "Bad procedure for program",
      [77] = "No locks available",
      [78] = "Function not implemented",
      [79] = "Inappropriate file type or format",
      [80] = "Authentication error",
      [81] = "Need authenticator",
      [82] = "Device power is off",
      [83] = "Device error",
      [84] = "Value too large to be stored in data type",
      [85] = "Bad executable (or shared library)",
      [86] = "Bad CPU type in executable",
      [87] = "Shared library version mismatch",
      [88] = "Malformed Mach-o file",
      [89] = "Operation canceled",
      [90] = "Identifier removed",
      [91] = "No message of desired type",
      [92] = "Illegal byte sequence",
      [93] = "Attribute not found",
      [94] = "Bad message",
      [95] = "EMULTIHOP (Reserved)",
      [96] = "No message available on STREAM",
      [97] = "ENOLINK (Reserved)",
      [98] = "No STREAM resources",
      [99] = "Not a STREAM",
      [100] = "Protocol error",
      [101] = "STREAM ioctl timeout",
      [102] = "Operation not supported on socket",
      [103] = "Policy not found",
      [104] = "State not recoverable",
      [105] = "Previous owner died",
      [106] = "Interface output queue is full",
  };
  int size = 107;
  char error[] = "Unknown error: ";
#elif __linux__
  const char *arr[] = {"Success",
                       "Operation not permitted",
                       "No such file or directory",
                       "No such process",
                       "Interrupted system call",
                       "Input/output error",
                       "No such device or address",
                       "Argument list too long",
                       "Exec format error",
                       "Bad file descriptor",
                       "No child processes",
                       "Resource temporarily unavailable",
                       "Cannot allocate memory",
                       "Permission denied",
                       "Bad address",
                       "Block device required",
                       "Device or resource busy",
                       "File exists",
                       "Invalid cross-device link",
                       "No such device",
                       "Not a directory",
                       "Is a directory",
                       "Invalid argument",
                       "Too many open files in system",
                       "Too many open files",
                       "Inappropriate ioctl for device",
                       "Text file busy",
                       "File too large",
                       "No space left on device",
                       "Illegal seek",
                       "Read-only file system",
                       "Too many links",
                       "Broken pipe",
                       "Numerical argument out of domain",
                       "Numerical result out of range",
                       "Resource deadlock avoided",
                       "File name too long",
                       "No locks available",
                       "Function not implemented",
                       "Directory not empty",
                       "Too many levels of symbolic links",
                       "Unknown error 41",
                       "No message of desired type",
                       "Identifier removed",
                       "Channel number out of range",
                       "Level 2 not synchronized",
                       "Level 3 halted",
                       "Level 3 reset",
                       "Link number out of range",
                       "Protocol driver not attached",
                       "No CSI structure available",
                       "Level 2 halted",
                       "Invalid exchange",
                       "Invalid request descriptor",
                       "Exchange full",
                       "No anode",
                       "Invalid request code",
                       "Invalid slot",
                       "Unknown error 58",
                       "Bad font file format",
                       "Device not a stream",
                       "No data available",
                       "Timer expired",
                       "Out of streams resources",
                       "Machine is not on the network",
                       "Package not installed",
                       "Object is remote",
                       "Link has been severed",
                       "Advertise error",
                       "Srmount error",
                       "Communication error on send",
                       "Protocol error",
                       "Multihop attempted",
                       "RFS specific error",
                       "Bad message",
                       "Value too large for defined data type",
                       "Name not unique on network",
                       "File descriptor in bad state",
                       "Remote address changed",
                       "Can not access a needed shared library",
                       "Accessing a corrupted shared library",
                       ".lib section in a.out corrupted",
                       "Attempting to link in too many shared libraries",
                       "Cannot exec a shared library directly",
                       "Invalid or incomplete multibyte or wide character",
                       "Interrupted system call should be restarted",
                       "Streams pipe error",
                       "Too many users",
                       "Socket operation on non-socket",
                       "Destination address required",
                       "Message too long",
                       "Protocol wrong type for socket",
                       "Protocol not available",
                       "Protocol not supported",
                       "Socket type not supported",
                       "Operation not supported",
                       "Protocol family not supported",
                       "Address family not supported by protocol",
                       "Address already in use",
                       "Cannot assign requested address",
                       "Network is down",
                       "Network is unreachable",
                       "Network dropped connection on reset",
                       "Software caused connection abort",
                       "Connection reset by peer",
                       "No buffer space available",
                       "Transport endpoint is already connected",
                       "Transport endpoint is not connected",
                       "Cannot send after transport endpoint shutdown",
                       "Too many references: cannot splice",
                       "Connection timed out",
                       "Connection refused",
                       "Host is down",
                       "No route to host",
                       "Operation already in progress",
                       "Operation now in progress",
                       "Stale file handle",
                       "Structure needs cleaning",
                       "Not a XENIX named type file",
                       "No XENIX semaphores available",
                       "Is a named type file",
                       "Remote I/O error",
                       "Disk quota exceeded",
                       "No medium found",
                       "Wrong medium type",
                       "Operation canceled",
                       "Required key not available",
                       "Key has expired",
                       "Key has been revoked",
                       "Key was rejected by service",
                       "Owner died",
                       "State not recoverable",
                       "Operation not possible due to RF-kill",
                       "Memory page has hardware error"};
  char error[] = "Unknown error ";
  int size = 135;
#endif
  char *buff_num;
  char *result = calloc(100, sizeof(char));
  if (errnum <= 0 || errnum >= size) {
    s21_strcpy(result, error);
    buff_num = calloc(20, sizeof(char));
    if (errnum < 0) {
      s21_strcpy(result + s21_strlen(result), "-");
      errnum = -errnum;
    }
    int size = 0, temp_int = errnum;
    while (temp_int > 0) {
      temp_int /= 10;
      size += 1;
    }
    for (int i = 0; i < size; i++) {
      buff_num[size - i - 1] = '0' + errnum % 10;
      errnum /= 10;
    }
    s21_strcpy(result + s21_strlen(result), buff_num);
  } else {
    s21_strcpy(result, arr[errnum]);
  }
  return result;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t num = 0;
  int unsigned n_str2;
  for (; str1[num]; num++) {
    for (n_str2 = 0; str2[n_str2] != str1[num] && str2[n_str2]; n_str2++)
      ;
    if (str2[n_str2] == '\0') {
      break;
    }
  }
  return num;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  while (*str1) {
    char *req = (char *)str2;
    while (*req) {
      if (*str1 != *req) {
        req++;
      } else {
        res = (char *)str1;
        break;
      }
    }
    if (res) {
      break;
    }
    str1++;
  }
  return res;
}

char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  int index = s21_strlen(str);
  str = str + index;
  while (index != (int)s21_strlen(str)) {
    if ((int)*(char *)str == c) {
      res = (char *)str;
      break;
    }
    str--;
  }
  if ((int)*(char *)str == c) {
    res = (char *)str;
  }
  return res;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t num = 0;
  int unsigned n_str2;
  for (; str1[num]; num++) {
    for (n_str2 = 0; str2[n_str2] != str1[num] && str2[n_str2]; n_str2++)
      ;
    if (str2[n_str2] != '\0') {
      break;
    }
  }
  return num;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = s21_NULL;
  int num = 0;
  char *req = (char *)needle;
  int size_s2 = s21_strlen(needle);
  while (haystack[num]) {
    if (haystack[num] == *needle) {
      if (s21_strncmp(haystack + num, req, size_s2) == 0) {
        res = (char *)haystack + num;
        break;
      }
    }
    num++;
  }
  return (*needle) ? res : (char *)haystack;
}

char *s21_strtok(char *str, const char *delim) {
  static char *strtok_s;
  char *work_ptr;
  char *separator_ptr;
  char *res;

  if (str == s21_NULL) {
    work_ptr = strtok_s ? strtok_s : s21_NULL;
  } else {
    work_ptr = str;
  }

  if (work_ptr != s21_NULL) {
    separator_ptr = s21_strpbrk(work_ptr, delim);
    if (separator_ptr != s21_NULL) {
      *separator_ptr = 0;
      strtok_s = separator_ptr + 1;
      while (strtok_s && s21_strchr(delim, *strtok_s) != 0) {
        strtok_s++;
      }
    } else {
      strtok_s = s21_NULL;
    }
  }
  res = work_ptr;
  return res;
}

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    result = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
  }
  if (result != s21_NULL) {
    char *res = result;
    while (*str) {
      if (*str >= 'a' && *str <= 'z') {
        *res = *str - 32;
      } else {
        *res = *str;
      }
      res++;
      str++;
    }
  }
  return (void *)result;
}

void *s21_to_lower(const char *str) {
  char *result = s21_NULL;
  if (str) {
    result = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
    char *res = result;
    while (*str) {
      if (*str >= 'A' && *str <= 'Z') {
        *res = *str + 32;
      } else {
        *res = *str;
      }
      res++;
      str++;
    }
  }
  return (void *)result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = s21_NULL;
  s21_size_t index = s21_strlen(src) + s21_strlen(str) + 1;

  if (start_index <= s21_strlen(src) &&
      (result = (char *)calloc(index, sizeof(char))) != s21_NULL) {
    s21_strncpy(result, src, start_index + 1);
    s21_strncpy(result + start_index, str, s21_strlen(str) + 1);
    s21_strncpy(result + start_index + s21_strlen(str), src + start_index,
                s21_strlen(src) - start_index + 1);
  }
  return (void *)result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  s21_size_t start;
  start = s21_strspn(src, trim_chars);
  s21_size_t end = s21_strlen(src) - 1;

  if (start <= end) {
    while (end > 0 && (s21_strchr(trim_chars, src[end--]) != s21_NULL))
      ;
    result = (char *)calloc(end - start + 3, sizeof(char));
    s21_strncpy(result, src + start, end - start + 2);
  }
  return (void *)result;
}

//--------------------------------------------------------sprintf-----------------------------------------------------------

int s21_sprintf(char *str, char *format, ...) {
  va_list parlist;  // list of parameters "..."
  int width = 0, precision = -2;
  unsigned int flags = 0U, num = 0U;
  char length = ' ';

  va_start(parlist, format);  // fills parlist by arguments that comes after
                              // "char* format" in func
  for (char *format_str = format; *format_str;
       format_str++) {  // check every symbol
    if (*format_str !=
        '%') {  // while symbol not percent we just printing this symbol
      *str++ = *format_str;
      num++;
    } else {  // "%[flags][width][.precision][length]specifier" parsing
      flags = 0U;
      width = 0;
      precision = -2;
      length = ' ';
      format_str++;
      while (!is_specifier(*format_str)) {
        if (is_flag(*format_str)) {  // [flags]
          flags |= get_flag(&format_str);
        } else if (is_width(*format_str)) {  // [width]
          width = get_width(&format_str);
          if (width == -1) {
            width = va_arg(parlist, int);
          }
        } else if (is_precision(*format_str)) {  // [.precision]
          precision = get_precision(&format_str);
          if (precision == -1) {
            precision = va_arg(parlist, int);
          }
        } else if (is_length(*format_str)) {  // [length]
          length = *format_str++;
        }
      }
      str = get_specifier(str, format_str, flags, width, precision, length,
                          &num, parlist);
    }
  }
  *str = 0;
  va_end(parlist);
  return num;
}

//--------------------------------------------------------sscanf-----------------------------------------------------------

int s21_sscanf(char *str    , char *format, ...) {
  Specifiers spec = {0,        0,        0,        0,        0,
                     0,        0,        0,        s21_NULL, s21_NULL,
                     s21_NULL, s21_NULL, s21_NULL, s21_NULL, s21_NULL,
                     s21_NULL, s21_NULL, s21_NULL, s21_NULL};
  va_list args;
  va_start(args, format);
  int result, error, count, amount, zero_flag, negative;
  result = error = count = amount = zero_flag = negative = 0;
  long long int check_int;
  long double check_float;
  void *check_void_with_star;
  char *ptr;

  int check_int_with_star;  //переменные которым будет присвоено значение в
                            //случае звездочки со спецификатором i
  short int h_check_int_with_star;
  long long int l_check_int_with_star;

  unsigned int
      check_unsigned_int_with_star;  //переменные которым будет присвоено
                                     //значение в случае звездочки со
                                     //спецификаторами ouxX
  unsigned short int h_check_unsigned_int_with_star;
  unsigned long long int l_check_unsigned_int_with_star;

  if (s21_strcmp(str, "") == 0) return -1;
  for (char *p = format; *p != '\0'; p++) {
    if (*p == '%') {
      p++;
      p = format_parsing(&spec, p);
      switch (*p) {
        case 'd':
          if (spec.lenght_with_h) {  // проверка на наличие флагов длинны в
                                     // format
            if (!spec.star_flag)
              spec.h_lengt = va_arg(args, short int*);  //присвоение адреса для записи значения
          } else if (spec.lenght_with_l) {
            if (!spec.star_flag) spec.l_lengt = va_arg(args, long long int *);
          } else {
            if (!spec.star_flag) spec.int_spec = va_arg(args, int *);
          }
          removing_spaces(&spec, &str);
          str = negative_check(&spec, str, &negative);
          amount = s21_strlen(str);
          if (isdigit(*str)) {
            if (negative == -1) str--;
            check_int = strtoll(str, &str, 10);
            spec.count_of_characters += amount - s21_strlen(str);
            if (!spec.star_flag) {
              if (spec.lenght_with_h) {
                *spec.h_lengt = check_int;  // запись значения в аргумент
              } else if (spec.lenght_with_l) {
                *spec.l_lengt = check_int;
              } else {
                *spec.int_spec = check_int;
              }
              result++;
            }
            negative = 0;
          } else {
            error = 1;
          }
          break;
        case 'c':
          if (!spec.star_flag) {
            spec.c_spec = va_arg(args, char *);  //присвоение адреса для записи значения
            *spec.c_spec = *str;  // запись значения в аргумент
            result++;
          }
          if (*str) {
            str++;
            spec.count_of_characters++;
          }
          break;
        case 'i':
          removing_spaces(&spec, &str);
          if (spec.lenght_with_h) {
            spec.h_lengt = !spec.star_flag
                               ? va_arg(args, short int *)
                               : &h_check_int_with_star;  //присвоение адреса
                                                          //для записи значения
            str = get_int(&spec, str, &error);
            *spec.h_lengt = spec.result_strtol;  //запись значения в аргумент
          } else if (spec.lenght_with_l) {
            spec.l_lengt = !spec.star_flag ? va_arg(args, long long int*)
                                           : &l_check_int_with_star;
            str = get_int(&spec, str, &error);
            *spec.l_lengt = spec.result_strtol;
          } else {
            spec.int_spec =
                !spec.star_flag ? va_arg(args, int *) : &check_int_with_star;
            str = get_int(&spec, str, &error);
            *spec.int_spec = spec.result_strtol;
          }
          if (!error) {
            if (!spec.star_flag) {
              result++;
            }
          }
          break;
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
          amount = s21_strlen(str);
          ptr = str;
          check_float = strtold(
              str, &str);  // получаем из строки число с плавающей запятой
          if (check_float == 0 && ptr == str)
            error = 1;
          else {
            if (!spec.star_flag) {
              if (spec.lenght_with_L) {
                spec.L_efg_spec = va_arg(
                    args,
                    long double *);  //присвоение адреса для записи значения
                *spec.L_efg_spec = check_float;  // запись значения в аргумент
              } else {
                spec.efg_spec = va_arg(args, float *);
                *spec.efg_spec = check_float;
              }
              result++;
            }
          }
          spec.count_of_characters +=
              amount -
              s21_strlen(
                  str);  //плюсуем кол-во считанных символов для спецификатора n
          break;
        case 'o':
        case 'u':
        case 'x':
        case 'X':
          amount = s21_strlen(str);
          spec.base = *p == 'o'   ? 8
                      : *p == 'u' ? 10
                                  : 16;  //выбор системы счисления для strtoul
          if (spec.lenght_with_h) {
            spec.unsigned_h_lenght =
                !spec.star_flag
                    ? va_arg(args, unsigned short int *)
                    : &h_check_unsigned_int_with_star;  //присвоение адреса для
                                                        //записи значения
            *spec.unsigned_h_lenght = get_unsigned_int(
                &spec, &error, &str);  // запись значения в аргумент
          } else if (spec.lenght_with_l) {
            spec.unsigned_l_lenght =
                !spec.star_flag ? va_arg(args, unsigned long long int *)
                                : &l_check_unsigned_int_with_star;
            *spec.unsigned_l_lenght = get_unsigned_int(&spec, &error, &str);
          } else {
            spec.uo_spec = !spec.star_flag ? va_arg(args, unsigned int *)
                                           : &check_unsigned_int_with_star;
            *spec.uo_spec = get_unsigned_int(&spec, &error, &str);
          }
          if (!error && !spec.star_flag) result++;
          spec.count_of_characters +=
              amount -
              s21_strlen(
                  str);  //плюсуем кол-во считанных символов для спецификатора n
          break;
        case 'p':
          spec.p_spec = !spec.star_flag
                            ? va_arg(args, void **)
                            : &check_void_with_star;  //присвоение адреса для
                                                      //записи значения
          str = get_pointer(&spec, str, &error);
          if (!spec.star_flag && !error) result++;
          break;
        case 's':
          removing_spaces(&spec, &str);
          if (!spec.star_flag) {
            spec.s_spec = va_arg(args, char *);
            result++;
          }
          str = get_string(&spec, spec.s_spec, str);
          break;
        case 'n':
          spec.int_spec = va_arg(args, int *);
          *spec.int_spec = spec.count_of_characters;
          break;
        case '%':
          removing_spaces(&spec, &str);
          if (*str == '%') {
            str++;
            spec.count_of_characters++;
          } else {
            error = 1;
          }
          break;
        default:
          error = 1;
          break;
      }
      spec.width = 0;
      spec.star_flag = 0;
      spec.lenght_with_h = 0;
      spec.lenght_with_l = 0;
      spec.lenght_with_L = 0;
    }
    if (error == 1) return result;
  }
  va_end(args);
  return result;
}