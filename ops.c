#include <stdio.h>
#include "headers/ops.h"

void store_operand(struct OperandsOperatorsStorage* const ops_store, int operand) {
  ops_store->operands[ops_store->operand_count++] = operand;
}

void store_operator(struct OperandsOperatorsStorage* const ops_store, int operator) {
  ops_store->operators[ops_store->operator_count++] = operator;
}

void show_operands(struct OperandsOperatorsStorage* ops_store) {
  for(int i=0; i<ops_store->operand_count;i++) {
    printf("%d, ", ops_store->operands[i]);
  }
}

void show_operators(struct OperandsOperatorsStorage* ops_store) {
  for(int i=0; i<ops_store->operator_count;i++) {
    printf("%c, ", ops_store->operators[i]);
  }
}

int make_op(int l, int r, char op) {
  switch(op) {
    case PLUS_OP: return l + r;
    case SUB_OP: return l - r;
    case MUL_OP: return l * r;
    case DIV_OP: return l / r;
  }
}

int validate_op_expr(const char* expr) {
  for(int i=0; expr[i] != '\0'; i++) {
    const char c = expr[i];
    if(!(
      (c >= ASCII_0 && c <= ASCII_9) ||
      (c == PLUS_OP || c == SUB_OP || c == DIV_OP || c == MUL_OP)
    )) { 
      return 0; 
    } 
  }
  return 1;
}

int evaluate_expr(struct OperandsOperatorsStorage ops_storage) {
  // first multiplication and division operations
  for(int i=0; i<ops_storage.operator_count;) {
    const char op = ops_storage.operators[i];
    if(op == MUL_OP || op == DIV_OP) {
      int first_precedence_res = make_op(ops_storage.operands[i], ops_storage.operands[i+1], op);
      ops_storage.operands[i] = first_precedence_res;

      for(int j=i+1; j < ops_storage.operand_count - 1; j++) {
        ops_storage.operands[j] = ops_storage.operands[j+1];
      }
      --ops_storage.operand_count;

      for(int j=i; j < ops_storage.operator_count - 1; j++) {
        ops_storage.operators[j] = ops_storage.operators[j+1];
      }
      --ops_storage.operator_count;
    } else {
      i++;
    }
  }

  int result = ops_storage.operands[0];
  for(int i=0; i<ops_storage.operator_count; i++) {
    if(ops_storage.operators[i] == PLUS_OP) {
      result += ops_storage.operands[i+1];
    } else if(ops_storage.operators[i] == SUB_OP) {
      result -= ops_storage.operands[i+1];
    }
  }

  return result;
}