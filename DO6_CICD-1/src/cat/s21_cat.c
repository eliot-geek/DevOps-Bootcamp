#include "s21_cat.h"

#include <getopt.h>

int main(int argc, char *argv[]) {
  flags options = {0};
  if (argc > 1) {
    if (Parser(argc, argv, &options) == 0) {
      ReadFile(argc, argv, &options);
    }
  }

  return 0;
}

int Parser(int argc, char *argv[], flags *options) {
  static const char short_options[] = "+benstvTE";
  static struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                         {"number", 0, NULL, 'n'},
                                         {"squeeze-blank", 0, NULL, 's'},
                                         {NULL, 0, NULL, 0}};
  int current_flag;
  int error = 0;
  int option_index;

  while ((current_flag = getopt_long(argc, argv, short_options, long_options,
                                     &option_index)) != -1) {
    switch (current_flag) {
      case 'b':
        options->number_non_blank = true;
        break;
      case 'e':
        options->show_ends = true;
        options->show_non_printing = true;
        break;
      case 'n':
        options->number = true;
        break;
      case 's':
        options->squeeze_blank = true;
        break;
      case 't':
        options->show_tabs = true;
        options->show_non_printing = true;
        break;
      case 'v':
        options->show_non_printing = true;
        break;
      case 'E':
        options->show_ends = true;
        break;
      case 'T':
        options->show_tabs = true;
        break;
      default:
        fprintf(stdout,
                "usage: s21_cat [-benstvET] or [--number-nonblank --number "
                "--squeeze-blank] [file...]\n");
        error = 1;
        break;
    }
  }
  return error;
}

void ReadFile(int argc, char *argv[], flags *options) {
  FILE *file = NULL;
  static unsigned line_count = 0;
  for (int i = optind; i < argc; i++) {
    line_count = 0;
    file = fopen(argv[i], "r");
    if (file == NULL) {
      fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], argv[i]);
      continue;
    }
    Output(file, options, &line_count);
    fclose(file);
  }
}

void Output(FILE *file, flags *options, unsigned *line_count) {
  int cur_char;
  int prev_char = '\n';

  while ((cur_char = fgetc(file)) != EOF) {
    SqueezeBlank(file, cur_char, prev_char, options);
    NumberLine(cur_char, prev_char, options, line_count);
    ShowNonPrinting(&cur_char, options);
    ShowEnds(cur_char, options);
    ShowTabs(&cur_char, options);

    printf("%c", cur_char);
    prev_char = cur_char;
  }
}

void SqueezeBlank(FILE *file, int cur_char, int prev_char, flags *options) {
  if (options->squeeze_blank && prev_char == '\n' && cur_char == '\n') {
    cur_char = fgetc(file);
    while (cur_char == '\n') {
      cur_char = fgetc(file);
    }
    ungetc(cur_char, file);
  }
}

void NumberLine(int cur_char, int prev_char, flags *options,
                unsigned *line_count) {
  if (options->number_non_blank && prev_char == '\n' && cur_char != '\n') {
    fprintf(stdout, "%6u\t", ++(*line_count));
  } else if (!options->number_non_blank && options->number &&
             prev_char == '\n') {
    fprintf(stdout, "%6u\t", ++(*line_count));
  }
}

void ShowNonPrinting(int *cur_char, flags *options) {
  if (options->show_non_printing) {
    if (*cur_char > 127 && *cur_char < 160) fprintf(stdout, "M-^");
    if ((*cur_char < 32 && *cur_char != '\n' && *cur_char != '\t') ||
        *cur_char == 127)
      fprintf(stdout, "^");
    if ((*cur_char < 32 || (*cur_char > 126 && *cur_char < 160)) &&
        *cur_char != '\n' && *cur_char != '\t')
      *cur_char = *cur_char > 126 ? *cur_char - 128 + 64 : *cur_char + 64;
  }
}

void ShowEnds(int cur_char, flags *options) {
  if (options->show_ends && cur_char == '\n') {
    printf("%c", '$');
  }
}

void ShowTabs(int *cur_char, flags *options) {
  if (options->show_tabs && *cur_char == '\t') {
    printf("^");
    *cur_char = *cur_char + 64;
  }
}
