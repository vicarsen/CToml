#include "ctoml.h"

#include <stdio.h>
#include <stdlib.h>

static long __file_length(FILE *file)
{
  long pos = ftell(file);
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, pos, SEEK_SET);
  return length;
}

typedef struct {
  FILE *file;
  char *content;
} __load_context_t;

static void __load_cleanup(__load_context_t *ctx)
{
  fclose(ctx->file);
  free(ctx->content);

  ctx->file = NULL;
  ctx->content = NULL;
}

ctoml_result_t ctoml_load(ctoml_context_t *context, char const *filepath)
{
  __load_context_t ctx;
  ctx.file = NULL;
  ctx.content = NULL;

  ctx.file = fopen(filepath, "rb");
  if (ctx.file == NULL) {
    __load_cleanup(&ctx);
    return CTOML_FILE_NOT_FOUND;
  }

  long length = __file_length(ctx.file);
  ctx.content = malloc(sizeof(char) * length);
  if (ctx.content == NULL) {
    __load_cleanup(&ctx);
    return CTOML_ALLOCATION_ERROR;
  }

  if (fread(ctx.content, sizeof(char), length, ctx.file) != length) {
    __load_cleanup(&ctx);
    return CTOML_READ_ERROR;
  }



  context->content = ctx.content;
  ctx.content = NULL;

  __load_cleanup(&ctx);
  return CTOML_OK;
}

void ctoml_destroy(ctoml_context_t *context)
{
  free(context->content);
  context->content = NULL;
}

