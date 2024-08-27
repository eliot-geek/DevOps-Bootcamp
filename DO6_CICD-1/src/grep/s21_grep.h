#ifndef S21_GREP_H_
#define S21_GREP_H_
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFFER 10000

typedef struct {
  bool regexp;              // -e
  bool ignore_case;         // -i
  bool invert_match;        // -v
  bool count;               // -c
  bool files_with_matches;  // -l
  bool line_number;         // -n
  bool no_filename;         // -h
  bool no_messages;         // -s
  bool file;                // -f
  bool only_matching;       // -o
  char str[BUFFER];
  char str_o[BUFFER];
} flags;

int Parser(int argc, char *argv[], flags *options, char *pattern);
void ReadFile(int argc, char *argv[], flags *options, char *pattern);
void Output(FILE *file, flags *options, char *pattern, char *filename,
            int file_count);
void Grep(int *match, char *filename, int file_count, flags *options);
void InvertMatch(int *match, flags *options);
void IgnoreCase(int *cflags, flags *options);
void Count(int *counter, int *match, flags *options);
void LineNumber(int *str_number, int *match, flags *options, int file_count,
                char *filename);
void FilesWithMatches(char *filename, int *match, flags *options);
void OnlyMatching(int *match, flags *options, regex_t *reg,
                  const char *filename, int file_count, int str_number);
void AddPattern(char *pattern, char *str);
void AddPatternFile(char *pattern, char *filename, flags *options);

#endif
