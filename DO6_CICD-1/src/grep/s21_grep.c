#include "s21_grep.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  flags options = {0};
  char pattern[1024] = "\0";
  Parser(argc, argv, &options, pattern);
  ReadFile(argc, argv, &options, pattern);
  return 0;
}

int Parser(int argc, char *argv[], flags *options, char *pattern) {
  int current_flag;
  int option_index;
  int error = 0;
  char short_options[] = "e:ivclnhsf:o";
  while ((current_flag = getopt_long(argc, argv, short_options, NULL,
                                     &option_index)) != -1) {
    switch (current_flag) {
      case 'e':
        AddPattern(pattern, optarg);
        options->regexp = true;
        break;
      case 'i':
        options->ignore_case = true;
        break;
      case 'v':
        options->invert_match = true;
        break;
      case 'c':
        options->count = true;
        break;
      case 'l':
        options->files_with_matches = true;
        break;
      case 'n':
        options->line_number = true;
        break;
      case 'h':
        options->no_filename = true;
        break;
      case 's':
        options->no_messages = true;
        break;
      case 'f':
        options->file = true;
        AddPatternFile(pattern, optarg, options);
        break;
      case 'o':
        options->only_matching = true;
        break;
      default:
        printf(
            "usage: s21_grep [-ivclnhso] [-e pattern] [-f file] [pattern] "
            "[file...]\n");
        error = 1;
        break;
    }
    if (options->invert_match && options->only_matching) {
      options->only_matching = false;
    }
  }
  return error;
}

void ReadFile(int argc, char *argv[], flags *options, char *pattern) {
  FILE *file = NULL;
  if (!(options->regexp || options->file) && argv[optind]) {
    strcpy(pattern, argv[optind]);
    optind++;
  }
  int file_count = 1;
  if ((argc - optind) > 1) {
    file_count++;
  }
  for (int i = optind; i < argc; i++) {
    if (argv[i][0] != '-') {
      if ((file = fopen(argv[i], "r")) == NULL) {
        if (!options->no_messages) {
          fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                  argv[i]);
          continue;
        }
      }
      if (file != NULL) {
        Output(file, options, pattern, argv[i], file_count);
        fclose(file);
      } else {
        if (!options->no_messages) {
          fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                  argv[i]);
        }
      }
    }
  }
}

void Output(FILE *file, flags *options, char *pattern, char *filename,
            int file_count) {
  regex_t reg;
  regmatch_t start;
  int match = 0;
  int counter = 0;
  int str_number = 0;
  int cflags = REG_EXTENDED;
  IgnoreCase(&cflags, options);
  int fmatch = 0;
  regcomp(&reg, pattern, cflags);
  while (fgets(options->str, BUFFER, file) != NULL) {
    match = regexec(&reg, options->str, 1, &start, 0);
    str_number++;
    if (options->only_matching) {
      strcpy(options->str_o, options->str);
    }
    InvertMatch(&match, options);
    Count(&counter, &match, options);
    LineNumber(&str_number, &match, options, file_count, filename);
    if (options->files_with_matches && !match) {
      FilesWithMatches(filename, &fmatch, options);
      fmatch = 1;
    }
    Grep(&match, filename, file_count, options);
    OnlyMatching(&match, options, &reg, filename, file_count, str_number);
  }

  if (options->count && !options->files_with_matches) {
    if (file_count > 1 && !options->no_filename) {
      printf("%s:%d\n", filename, counter);
    } else
      printf("%d\n", counter);
  }
  if (options->files_with_matches && options->count) {
    if (file_count > 1 && !options->no_filename) {
      printf("%s:", filename);
    }
    if (counter > 0) {
      counter = 1;
      printf("%d\n%s\n", counter, filename);
    } else {
      printf("%d\n", counter);
    }
  }
  regfree(&reg);
}

void Grep(int *match, char *filename, int file_count, flags *options) {
  if (!*match && !options->only_matching && !options->count &&
      !options->files_with_matches && !options->line_number) {
    if (file_count > 1 && !options->no_filename) {
      printf("%s:%s", filename, options->str);
    } else
      printf("%s", options->str);
    if (options->str[strlen(options->str) - 1] != '\n') printf("\n");
  }
}

void InvertMatch(int *match, flags *options) {
  if (options->invert_match) {
    *match = !*match;
  }
}

void IgnoreCase(int *cflags, flags *options) {
  if (options->ignore_case) {
    *cflags |= REG_ICASE;
  }
}

void Count(int *counter, int *match, flags *options) {
  if (options->count) {
    if (!*match) (*counter)++;
  }
}

void LineNumber(int *str_number, int *match, flags *options, int file_count,
                char *filename) {
  if (options->line_number && !options->count && !options->files_with_matches &&
      !options->only_matching) {
    if (!*match) {
      if (file_count > 1 && !options->no_filename) {
        printf("%s:%d:%s", filename, *str_number, options->str);

      } else
        printf("%d:%s", *str_number, options->str);
      if (options->str[strlen(options->str) - 1] != '\n') printf("\n");
    }
  }
}

void FilesWithMatches(char *filename, int *match, flags *options) {
  if (options->files_with_matches && !options->count) {
    if (!*match) printf("%s\n", filename);
  }
}

void OnlyMatching(int *match, flags *options, regex_t *reg,
                  const char *filename, int file_count, int str_number) {
  if (!*match && options->only_matching && !options->count &&
      !options->files_with_matches) {
    char *pointer = options->str_o;
    regmatch_t start;

    while ((regexec(reg, pointer, 1, &start, 0) == 0)) {
      if (file_count > 1 && !options->no_filename) {
        printf("%s:", filename);
      }
      if (options->line_number) {
        printf("%d:", str_number);
      }
      printf("%.*s\n", (int)(start.rm_eo - start.rm_so), pointer + start.rm_so);
      pointer += start.rm_eo;
    }
  }
}

void AddPattern(char *pattern, char *str) {
  if (*pattern != '\0') {
    strcat(pattern, "|");
  }
  strcat(pattern, str);
}

void AddPatternFile(char *pattern, char *filename, flags *options) {
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp != NULL) {
    while (fgets(options->str, BUFFER - 1, fp) != NULL) {
      int p = strlen(options->str);
      if (options->str[p - 1] == '\n') {
        options->str[p - 1] = '\0';
      }
      if (options->str[0] == '\0') {
        strcpy(options->str, ".");
      }
      AddPattern(pattern, options->str);
    }
  } else {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
  }
  fclose(fp);
}
