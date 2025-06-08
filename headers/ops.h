#define PLUS_OP '+'
#define SUB_OP '-'
#define DIV_OP '/'
#define MUL_OP '*'
#define ASCII_0 48
#define ASCII_9 57

struct OperandsOperatorsStorage {
  int operand_count;
  int operator_count;
  int operands[20];
  char operators[20];
};

void store_operand(struct OperandsOperatorsStorage* const ops_store, int operand);
void store_operator(struct OperandsOperatorsStorage* const ops_store, int operator);
void show_operands(struct OperandsOperatorsStorage* const ops_store);
void show_operators(struct OperandsOperatorsStorage* const ops_store);

