#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "adjtext.h"


int
main(int argc, char *argv[]) {
  file_t *fp;

  if(argc < 2) {
    fprintf(stderr, "%s: Operand Error.\n", argv[0]);
    return EOF;
  }

  if((fp = file_new(argv[1])) != NULL) {
    file_remove_newline(fp);
    file_display_proofed_data(fp);

    fp = file_free(fp);
  }

	return 0;
}
