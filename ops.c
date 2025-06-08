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