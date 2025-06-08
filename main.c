#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/ops.h"

bool validate_expr(const char* expr) {
  for(int i=0; expr[i] != '\0'; i++) {
    const char c = expr[i];
    if(!(
      (c >= ASCII_0 && c <= ASCII_9) ||
      (c == PLUS_OP || c == SUB_OP || c == DIV_OP || c == MUL_OP)
    )) { 
      return false; 
    } 
  }
  return true;
}

int main() { 
  int expr_size = 1024;
  bool keep_running = true;
  char calc_expr_buf[expr_size];

  while(keep_running) {
    printf("Expression (type 'quit' to exit): ");
    fgets(calc_expr_buf, expr_size, stdin);
    calc_expr_buf[strcspn(calc_expr_buf, "\n")] = '\0';

    if(strstr(calc_expr_buf, "quit")) {
      keep_running = false; 
      break;
    }

    const bool valid_expr = validate_expr(calc_expr_buf);
    if(!valid_expr) {
      printf("\nInvalid expression!");
      continue;
    }

    char cleaned_expr[expr_size];
    int non_space_count_track = 0;
    for(long i=0; calc_expr_buf[i] != '\0'; i++) {
      if(calc_expr_buf[i] == ' ') continue;
      cleaned_expr[non_space_count_track++] = calc_expr_buf[i];
    }
    cleaned_expr[non_space_count_track] = '\0';
    
    struct OperandsOperatorsStorage ops_storage = {
      0, 0, {0}, {0}
    };

    char next_operand[50];
    char* tmp_expr = cleaned_expr;
    int idx = 0;
    for(int i=0; tmp_expr[i] != '\0'; i++) {
      char c = cleaned_expr[i];
      if(c != PLUS_OP && c != SUB_OP && c != MUL_OP && c != DIV_OP) {
        next_operand[idx++] = tmp_expr[i];
      } else {
        next_operand[idx] = '\0';
        store_operand(&ops_storage, atoi(next_operand));
        store_operator(&ops_storage, c);
        idx = 0;
      }
    }

    // for the last operand
    if (idx > 0) {
        next_operand[idx] = '\0';
        store_operand(&ops_storage, atoi(next_operand));
    }

    show_operands(&ops_storage);
    printf("\n");
    show_operators(&ops_storage);
    printf("\n");
    for(int i=0; i<ops_storage.operator_count;) {
      const char op = ops_storage.operators[i];
      if(op == MUL_OP || op == DIV_OP) {
        int left_operand = ops_storage.operands[i];
        int right_operand = ops_storage.operands[i+1];
        int result = (op == MUL_OP) ? (left_operand * right_operand) : (left_operand / right_operand);
        ops_storage.operands[i] = result;

        for(int j=i+1; j<=ops_storage.operand_count - 1; j++) {
          ops_storage.operands[j] = ops_storage.operands[j+1];
        }
        --ops_storage.operand_count;

        for(int j=i; j <= ops_storage.operand_count - 1; j++) {
          ops_storage.operators[j] = ops_storage.operators[j+1];
        }
        --ops_storage.operator_count;
      } else {
        i++;
      }
    }

    int result = ops_storage.operands[0];
    printf("Result: %d", result);
  }
}
