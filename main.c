#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/ops.h"

int main() { 
  const short MAX_EXPR_TOKENS = 1000;
  int keep_running = 1;
  char calc_expr_buf[MAX_EXPR_TOKENS];

  while(keep_running) {
    printf("Expression (type 'quit' to exit): ");
    fgets(calc_expr_buf, MAX_EXPR_TOKENS, stdin);
    calc_expr_buf[strcspn(calc_expr_buf, "\n")] = '\0';

    if(strstr(calc_expr_buf, "quit")) {
      keep_running = 0; 
      break;
    }

    char cleaned_expr[MAX_EXPR_TOKENS];
    int non_space_count_track = 0;
    for(long i=0; calc_expr_buf[i] != '\0'; i++) {
      if(calc_expr_buf[i] == ' ') continue;
      cleaned_expr[non_space_count_track++] = calc_expr_buf[i];
    }
    cleaned_expr[non_space_count_track] = '\0';

    if(!validate_op_expr(cleaned_expr)) {
      printf("\nInvalid expression!");
      continue;
    }
    
    struct OperandsOperatorsStorage ops_storage = { 0, 0, {0}, {0} };
    char next_operand[MAX_OPERAND_DIGITS];
    char* tmp_expr = cleaned_expr;
    int next_operand_digit_idx = 0;

    for(int i=0; tmp_expr[i] != '\0'; i++) {
      char c = cleaned_expr[i];
      if(c != PLUS_OP && c != SUB_OP && c != MUL_OP && c != DIV_OP) {
        next_operand[next_operand_digit_idx++] = tmp_expr[i];
      } else {
        next_operand[next_operand_digit_idx] = '\0';
        store_operand(&ops_storage, atoi(next_operand));
        store_operator(&ops_storage, c);
        next_operand_digit_idx = 0;
      }
    }

    // for the last operand
    if (next_operand_digit_idx > 0) {
        next_operand[next_operand_digit_idx] = '\0';
        store_operand(&ops_storage, atoi(next_operand));
    }

    const int result = evaluate_expr(ops_storage);
    printf("Result: %d\n", result);
  }
}
