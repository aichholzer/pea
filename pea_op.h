
enum eOp {
  OP_HTML,
  OP_INCLUDE,
  OP_PUSH,
  OP_POP,
  OP_POP_EX,
  OP_CONST_INT,
  OP_CONST_STRING,
  OP_CONST_ATOM,
  OP_COMPARE_EQ,
  OP_COMPARE_NE,
  OP_COMPARE_GT,
  OP_COMPARE_LT,
  OP_COMPARE_GTE,
  OP_COMPARE_LTE,
  OP_JMP_TRUE,
  OP_JMP_FALSE,
  OP_JMP,
  OP_READ,
  OP_ASSIGN,
  OP_GLOBAL_VAR,
  OP_LOCAL_VAR,
  OP_MEMBER_VAR,
  OP_BINARY_OR,
  OP_BINARY_AND,
  OP_BINARY_XOR,
  OP_BINARY_SL,
  OP_BINARY_SR,
  OP_BINARY_NOT,
  OP_LOGICAL_AND,
  OP_LOGICAL_OR,
  OP_LOGICAL_NOT,
  OP_ADD,
  OP_SUB,
  OP_DIV,
  OP_MUL,
  OP_MOD,
  OP_CONCAT,
  OP_NEG,
  OP_EXIT,
  OP_CALL,
  OP_RETURN,
  OP_DUP_2,
  OP_SWAP,
  OP_ENUM_CREATE,
  OP_ENUM_NEXT,
  OP_ENUM_CLOSE,
  OP_ARRAY,
  OP_LINE,
  OP_NEW,
  OP_ECHO,
  OP_ASSIGN_ARG,
  OP_ASSIGN_DEF_ARG,
  OP_ASSIGN_REF_ARG
};

struct opInfoStruct {
  char* name;
  int   args;
};

#ifdef PEA_CPP
struct opInfoStruct opInfo[] = {
  "OP_HTML",1,
  "OP_INCLUDE",0,
  "OP_PUSH",0,
  "OP_POP",0,
  "OP_POP_EX",1,
  "OP_CONST_INT",1,
  "OP_CONST_STRING",1,
  "OP_CONST_ATOM",1,
  "OP_COMPARE_EQ",0,
  "OP_COMPARE_NE",0,
  "OP_COMPARE_GT",0,
  "OP_COMPARE_LT",0,
  "OP_COMPARE_GTE",0,
  "OP_COMPARE_LTE",0,
  "OP_JMP_TRUE",1,
  "OP_JMP_FALSE",1,
  "OP_JMP",1,
  "OP_READ",0,
  "OP_ASSIGN",0,
  "OP_GLOBAL_VAR",1,
  "OP_LOCAL_VAR",1,
  "OP_MEMBER_VAR",0,
  "OP_BINARY_OR",0,
  "OP_BINARY_AND",0,
  "OP_BINARY_XOR",0,
  "OP_BINARY_SL",0,
  "OP_BINARY_SR",0,
  "OP_BINARY_NOT",0,
  "OP_LOGICAL_AND",0,
  "OP_LOGICAL_OR",0,
  "OP_LOGICAL_NOT",0,
  "OP_ADD",0,
  "OP_SUB",0,
  "OP_DIV",0,
  "OP_MUL",0,
  "OP_MOD",0,
  "OP_CONCAT",0,
  "OP_NEG",0,
  "OP_EXIT",0,
  "OP_CALL",1,
  "OP_RETURN",0,
  "OP_DUP_2",0,
  "OP_SWAP",0,
  "OP_ENUM_CREATE",0,
  "OP_ENUM_NEXT",0,
  "OP_ENUM_CLOSE",0,
  "OP_ARRAY",0,
  "OP_LINE",2,
  "OP_NEW",1,
  "OP_ECHO",0,
  "OP_ASSIGN_ARG",0,
  "OP_ASSIGN_DEF_ARG",0,
  "OP_ASSIGN_REF_ARG",0,
};
#else
extern struct opInfoStruct opInfo[];

#endif
