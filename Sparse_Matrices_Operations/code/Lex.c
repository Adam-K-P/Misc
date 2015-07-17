/* Adam Pinarbasi
   akpinarb
   pa2           */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LENGTH 160

typedef struct file_info {
   char **line_array;
   size_t nr_lines;
} file_info;

void file_not_found (char *file) {
   fprintf(stderr, "File: %s not found\n", file);
   exit(EXIT_FAILURE);
}
// insert_file
/* inserts a file into an array and records the number of lines */
file_info insert_file (FILE *infile, char **line_array, size_t nr_lines) {
   file_info this_file;
   char buffer[MAX_LENGTH];
   for (size_t i = 0; fgets(buffer, MAX_LENGTH, infile) != NULL; ++i) {
      char *line = malloc(strlen(buffer) + 1);
      strcpy(line, buffer);
      line_array[i] = line;
   }
   this_file.line_array = line_array;
   this_file.nr_lines   = nr_lines;
   return this_file;  
}

// in_list
/* checks to see if an index is in the list */
bool in_list (int ind, List list) {
   if (list == NULL || !length(list)) return false;
   for (moveFront(list); index(list) >= 0; moveNext(list))
      if (*(int *)get(list) == ind) return true;
   return false;
}

// sort_array
/* sorts array indices into lexicographic order */
void sort_array (List list, file_info this_file) {
   for (size_t i = 0; i < this_file.nr_lines; ++i) {
      char *smallstr = NULL;
      int smallind = 0;
      for (size_t j = 0; j < this_file.nr_lines; ++j) {
         if (!in_list(j, list)) {
            if (smallstr == NULL) 
               { smallstr = this_file.line_array[j]; smallind = j; }
            if (strcmp((const char *)smallstr, 
                       (const char *)this_file.line_array[j]) > 0) 
               { smallstr = this_file.line_array[j]; smallind = j; }
            printf("smallstr: %s\n", smallstr);
         }
      }
      printf("smallind: %d\nsmallstr: %s\n", smallind, smallstr);
      append(list, &smallind);
   }
}

// print_array
/* prints out the array in lexicographic order then frees each string*/
void print_array (List list, FILE *outfile, char **line_array) {
   for (moveFront(list); index(list) >= 0; moveNext(list)) {
      int index = (int)*((int *)get(list));
      fprintf(outfile, "%s\n", line_array[index]);
      free(line_array[index]);
      line_array[index] = NULL;
   }
}

int main (int argc, char **argv) {
   List list = newList();
   if (argc != 3) {
      fprintf(stderr, "Usage: Lex [input file] [output file]\n");
      return EXIT_FAILURE;
   }
   FILE *infile = fopen(argv[1], "r");
   if (!infile) {
      fprintf(stderr, "File: %s not found\n", argv[1]);
      return EXIT_FAILURE;
   }
   size_t nr_lines = 0;
   char buffer[MAX_LENGTH];
   while (fgets(buffer, MAX_LENGTH, infile)) ++nr_lines;
   rewind(infile);
   FILE *outfile = fopen(argv[2], "w");
   char *line_array[nr_lines];
   sort_array(list, insert_file(infile, line_array, nr_lines));
   //print_array(list, outfile, line_array);
   fclose(infile);
   fclose(outfile);
   freeList(&list);
   return EXIT_SUCCESS;
}
