#pragma once

#include "../util/util.h"
#include <stdlib.h>//size_t
// #include "../modules/signal_handler/signal_handler.h"

typedef struct inv_files{
  char ** file_paths;
  int num_files;
} inv_files_t;
