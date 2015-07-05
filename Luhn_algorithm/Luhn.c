//Adam Pinarbasi


/* From the wikipedia entry:

   The Luhn algorithm or Luhn formula, also known as the "modulus 10" or 
   "mod 10" algorithm, is a simple checksum formula used to validate a 
   variety of identification numbers, such as credit card numbers */
   
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20 //this value can be changed to accomidate larger numbers

//doubles every other digit starting with the rightmost digit of original num
//and checks if the sum modulo 10 is equal to 0
bool check_nums (int *dig_array, int length) {
   int sum = 0;
   for (int i = 0; i < length - 1; ++i) {
      if (i % 2 == 0) dig_array[i] *= 2;
      sum += dig_array[i];
   }
   return (sum % 10 == 0);
}
         
//checks if a credit card number is valid
bool handle_number (char *number) {
   int length = strlen((const char *)number);
   int dig_array[length];
   int dig_ind = 0;
   for (int i = length - 2; i >= 0; --i) {
      int digit = number[i] - '0';
      if (digit < 0 || digit > 9) {
         fprintf(stderr, "Invalid character: %c found in file\n", 
                          number[i] + '0');
         return false;
      }
      dig_array[dig_ind++] = digit;
   }
   return check_nums(dig_array, length);
}

int main (int argc, char **argv) {
   if (argc != 3) {
      fprintf(stderr, "Usage: Luhn [infile] [outfile]\n");
      return EXIT_FAILURE;
   }

   FILE *infile = fopen(argv[1], "r");
   if (infile == NULL) {
      fprintf(stderr, "Error, file: %s not found\n", argv[1]);
      return EXIT_FAILURE;
   }

   char number[MAX_LENGTH];
   FILE *outfile = fopen(argv[2], "w");
   for (size_t line = 0; fgets(number, MAX_LENGTH, infile) != NULL; ++line) 
      fprintf(outfile, handle_number(number) ? "true\n" : "false\n");
   fclose(infile);
   fclose(outfile);
   return EXIT_SUCCESS;
}




