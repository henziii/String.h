#ifndef _SRC_UTL_H_
#define _SRC_UTL_H_

//----------------------------------sprintf------------------------------------------------------------

#include <stdarg.h>
#include <stdbool.h>
#define FLAG_MINUS (1U << 0U)  //  1 = 00001
#define FLAG_PLUS (1U << 1U)   //  2 = 00010
#define FLAG_SPACE (1U << 2U)  //  4 = 00100
#define FLAG_SHARP (1U << 3U)  //  8 = 01000
#define FLAG_ZERO (1U << 4U)   // 16 = 10000

typedef unsigned long int s21_intptr_t;

char* s21_itoa(const long long num, char* str);
char* s21_hexitoa(char base, const long num, char* str);
char* s21_octitoa(const long num, char* str);

int dig_num(unsigned long int num);
int hexdig_num(long unsigned int num);
int octdig_num(long unsigned int num);
int dig_float(float num);

bool is_flag(char str);
bool is_width(char str);
bool is_precision(char str);
bool is_length(char str);
bool is_specifier(char str);
bool is_digit(char str);

unsigned int get_flag(char** str);
int get_width(char** str);
int get_precision(char** str);
char* get_specifier(char* str, char* format_str, unsigned int flags, int width,
                    int precision, char length, unsigned int* num,
                    va_list parlist);
int get_zeros(int width, int precision, int flags);
int get_spaces(int width, int zeros);
int get_dig_num(char base, long long int trg);
int floatdig_num(long double trg);

char* ftos(long double trg, char* str, int precision);

char* str_out(char* dest_str, char* trg, int width, int precision,
              unsigned int* num, unsigned int flags);
char* ptr_out(char* dest_str, s21_intptr_t adress, int width, int precision,
              unsigned int* num, unsigned int flags);
char* spec_char_out(char* dest_str, char sym, int width, unsigned int* num,
                    unsigned int flags);
char* char_out(char* dest_str, char sym, unsigned int* num);
char* int_out(char* dest_str, long int trg, int width, int precision,
              char length, unsigned int* num, unsigned int flags);
char* uint_out(char base, char* dest_str, long unsigned int trg, int width,
               int precision, char length, unsigned int* num,
               unsigned int flags);
char* float_out(char* dest_str, long double trg, int width, int precision,
                unsigned int* num, unsigned int flags);
char* efloat_out(char spec, char* dest_str, long double trg, int width,
                 int precision, unsigned int* num, unsigned int flags);
char* gfloat_out(char spec, char* dest_str, long double trg, int width,
                 int precision, unsigned int* num, unsigned int flags);
char* zeros_out(int zeros, unsigned int* num, char* dest_str);
char* spaces_out(int spaces, unsigned int* num, char* dest_str);
char* sign_out(char sign, unsigned int* num, char* dest_str,
               unsigned int flags);
char* extra_space_out(int extra_space, unsigned int* num, char* dest_str);
char* rounding(char* str);
char* remove_zeros(char* str, int* num);
void remove_zeros_from_end(char* str);

char* sci_out(char spec, int digits_before_point, unsigned int* num,
              char* dest_str);
// void s21_null();

//-----------------------------------------------------sscanf--------------------------------------

typedef struct variables {
  int base;
  int star_flag;
  int width;
  int count_of_characters;

  int lenght_with_h;
  int lenght_with_l;
  int lenght_with_L;
  long long int result_strtol;

  short int* h_lengt;
  int* int_spec;
  long long int* l_lengt;

  unsigned short int* unsigned_h_lenght;
  unsigned long long int* unsigned_l_lenght;
  unsigned int* uo_spec;

  float* efg_spec;
  long double* L_efg_spec;

  char* c_spec;
  char* s_spec;
  void** p_spec;
} Specifiers;

int s21_sscanf(char* str, char* format, ...);

char* get_string(Specifiers* spec, char* arg, char* str);
char* get_int(Specifiers* spec, char* str, int* flag);
void removing_spaces(Specifiers* spec, char** str);
char* negative_check(Specifiers* spec, char* str, int* num);
unsigned long long int get_unsigned_int(Specifiers* spec, int* error,
                                        char** str);
char* format_parsing(Specifiers* spec, char* str);
char* get_pointer(Specifiers* spec, char* str, int* error);

#endif  // _SRC_UTL_H_