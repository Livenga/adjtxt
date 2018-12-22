#ifndef _ADJTEXT_H
#define _ADJTEXT_H

#include "adjtext_type.h"

/* src/adjtext.c */
extern file_t *
file_new(const char *path);
extern void *
file_free(file_t *fp);

extern file_t *
file_remove_newline(file_t *fp);
extern file_t *
file_proofed_data_to(file_t *fp, FILE *strm);

#define file_display_proofed_data(fp) file_proofed_data_to(fp, stdout)

#endif
