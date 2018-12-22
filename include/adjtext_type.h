#ifndef _ADJTEXT_TYPE_H
#define _ADJTEXT_TYPE_H

typedef struct _file_t file_t;
struct _file_t {
  char path[1024];

  size_t memsize;
  size_t length;
  char *content;
};

#endif
