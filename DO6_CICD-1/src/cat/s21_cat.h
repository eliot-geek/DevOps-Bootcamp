#ifndef S21_CAT_H_
#define S21_CAT_H_
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool number_non_blank;   // -b
  bool show_ends;          // -E
  bool number;             // -n
  bool squeeze_blank;      // -s
  bool show_non_printing;  // -v
  bool show_tabs;          // -T
} flags;

int Parser(int argc, char *argv[], flags *options);
void ReadFile(int argc, char *argv[], flags *options);
void Output(FILE *file, flags *options, unsigned *line_count);
void SqueezeBlank(FILE *file, int cur_char, int prev_char, flags *options);
void NumberLine(int cur_char, int prev_char, flags *options,
                unsigned *line_count);
void ShowNonPrinting(int *cur_char, flags *options);
void ShowEnds(int cur_char, flags *options);
void ShowTabs(int *cur_char, flags *options);

#endif
