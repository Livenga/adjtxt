#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "adjtext_type.h"

file_t *
file_new(const char *path) {
  FILE *fp;
  file_t *p_ret;

  if((fp = fopen(path, "rb")) == NULL) {
    return NULL;
  }

  if((p_ret = (file_t *)calloc(1, sizeof(file_t))) != NULL) {
    strncpy((char *)p_ret->path, path, 1023);

    fseek(fp, 0L, SEEK_END);
    p_ret->length = ftell(fp);
    p_ret->memsize = p_ret->length;
    fseek(fp, 0L, SEEK_SET);

    char *buf = (char *)calloc(p_ret->length + 1, sizeof(char));
    if(buf != NULL) {
      size_t s_read, s_cur;

      s_cur = 0L;
      while((s_read = fread((void *)buf, sizeof(char), p_ret->length - s_cur, fp)) > 0) {
        s_cur += s_read;
      }

      p_ret->content = buf;
    } else {
      memset((void *)p_ret, '\0', sizeof(file_t));
      free((void *)p_ret);
      p_ret = NULL;
    }

    fclose(fp);
  }

  return p_ret;
}

void *
file_free(file_t *fp) {
  memset((void *)fp->path, '\0', sizeof(char) * 1024);
  memset((void *)fp->content, '\0', sizeof(char) * fp->memsize);

  fp->length  = 0L;
  fp->memsize = 0L;

  free((void *)fp->content);
  fp->content = NULL;
  free((void *)fp);

  return NULL;
}

file_t *
file_remove_newline(file_t *fp) {
  char *p_nl;

  for(p_nl = strchr(fp->content, '\n'); p_nl != NULL; p_nl = strchr(p_nl + 1, '\n')) {
    if(*(p_nl - 1) == '.') {
      size_t size = fp->length - (p_nl - fp->content);

      memcpy((void *)p_nl, (const void *)p_nl + 1, size);
      *(p_nl + size) = '\0';
    } else {
      *p_nl = ' ';
    }
  }
  fp->length = strlen(fp->content);

  return fp;
}


#define IS_NUMBER(c) (0 <= (c - '0') && (c - '0') < 10)
#define PUT_NEWLINE(strm) fwrite((void *)"\n", sizeof(char), 1, strm)

file_t *
file_proofed_data_to(file_t *fp, FILE *strm) {
  char *p_start, *p_end;

  if(strm == NULL) { strm = stdout; }

  for(p_start = fp->content, p_end = strchr(p_start, '.');
      p_end != NULL;
      p_start = p_end + 1, p_end = strchr(p_start, '.')) {
    while(IS_NUMBER(*(p_end - 1)) &&
        ((p_end - fp->content) < fp->length) &&
        IS_NUMBER(*(p_end + 1))) {
      p_end = strchr(p_end + 1, '.');

      if(p_end == NULL) {
        p_end = fp->content + fp->length;
        break;
      }
    }

    for(; *p_start == ' '; p_start += 1);
    fwrite((void *)p_start, sizeof(char), (p_end - p_start) + 1, strm);
    PUT_NEWLINE(strm);
    PUT_NEWLINE(strm);
  }

  return fp;
}
