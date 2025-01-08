#pragma once

typedef enum {
  CTOML_OK = 0,
  CTOML_FILE_NOT_FOUND,
  CTOML_ALLOCATION_ERROR,
  CTOML_READ_ERROR
} ctoml_result_t;

typedef struct {
  char *content;
} ctoml_context_t;

ctoml_result_t ctoml_load(ctoml_context_t *context, char const *filepath);
void ctoml_destroy(ctoml_context_t *context);

