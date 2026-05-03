#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#define strdup _strdup
static char *strndup(const char *s, size_t n)
{
    size_t len = strlen(s);
    if (len > n) len = n;
    char *new = malloc(len + 1);
    if (!new) return NULL;
    new[len] = '\0';
    return memcpy(new, s, len);
}
#endif

#include "utils.h"

#undef malloc
#undef realloc
#undef calloc
#undef strdup
#undef strndup
#undef free

custom_m_alloc my_m_alloc = malloc;
custom_re_alloc my_re_alloc = realloc;
custom_c_alloc my_c_alloc = calloc;
custom_str_dup my_str_dup = strdup;
custom_strn_dup my_strn_dup = strndup;
custom_f_ree my_f_ree = free;

void *m_alloc(size_t size)
{
  return my_m_alloc(size);
}
void *re_alloc(void *ptr, size_t size) {
  return my_re_alloc(ptr, size);
}
void *c_alloc(size_t elementCount, size_t size)
{
  return my_c_alloc(elementCount, size);
}
char *str_dup(const char *s) {
  return my_str_dup(s);
}
char *strn_dup(const char *s, size_t size) {
  return my_strn_dup(s, size);
}
void f_ree(void *ptr)
{
  my_f_ree(ptr);
}
