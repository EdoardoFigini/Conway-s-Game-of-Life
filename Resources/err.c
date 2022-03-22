#include <stdio.h>
#include "err.h"

#define FORMAT "\x1b[31;1m"
#define RESET "\x1b[0m"

void printerr(char err[]){
  fprintf(stderr, "%s[!]%s %s", FORMAT, RESET, err);
}
