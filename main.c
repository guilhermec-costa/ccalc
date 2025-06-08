#include <stdio.h>
#include <stdlib.h>
#include "ops.h"

#define PLUS_OP '+'

struct OperandsStorage {
  int next_idx;
  int operands[20];
};

void store_operand(struct OperandsStorage* ops_store, int operand) {
  ops_store->operands[ops_store->next_idx++] = operand;
}

int main() { 
  printf("Expression: ");
  int expr_size = 1024;
  char calc_expr_buf[expr_size];
  fgets(calc_expr_buf, expr_size, stdin);
  
  char cleaned_expr[expr_size];
  int non_space_count_track = 0;
  for(long i=0; calc_expr_buf[i] != '\0'; i++) {
    if(calc_expr_buf[i] == ' ') continue;
    cleaned_expr[non_space_count_track++] = calc_expr_buf[i];
  }
  cleaned_expr[non_space_count_track] = '\0';
  
  struct OperandsStorage ops_storage = {
    0, {0}
  };
  
  char next_operand[50];
  char* tmp_expr = cleaned_expr;
  int idx = 0;
  for(int i=0; tmp_expr[i] != '\0'; i++) {
    if(cleaned_expr[i] != '+') {
      next_operand[idx++] = tmp_expr[i];
    } else {
      next_operand[idx] = '\0';
      store_operand(&ops_storage, atoi(next_operand));
      idx = 0;
    }
  }

  // for the last operand
  if (idx > 0) {
      next_operand[idx] = '\0';
      store_operand(&ops_storage, atoi(next_operand));
  }

  printf("%d", ops_storage.operands[1]);
}
