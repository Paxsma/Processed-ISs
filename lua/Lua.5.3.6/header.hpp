#include <map>
#include <vector>

enum class opcodes {
      OP_MOVE,     /* (0) | Move source register to dest register. | * dest(8_Bits), * src(9_Bits) */
      OP_LOADK,    /* (1) | Load kvalue to destination register. | * dest(8_Bits), * kidx(18_Bits) */
      OP_LOADKX,   /* (2) | Load kvalue extended. | * dest(26_Bits) */
      OP_LOADBOOL, /* (3) | Load boolean to register and take jump. | * dest(8_Bits), * val(9_Bits), * jmp(9_Bits) */
      OP_LOADNIL,  /* (4) | Iteration start at first target register then increments above the stack and fills with NIL set by source value. | * dest(8_Bits), * val(9_Bits) */
      OP_GETUPVAL, /* (5) | Load upvalue to destination register. | * dest(8_Bits), * upv(9_Bits) */
      OP_GETTABUP, /* (6) | Gets table upvalue as B and index element as C which gets load to A. | * dest(8_Bits), * upv(9_Bits), * val(9_Bits) */
      OP_GETTABLE, /* (7) | Gets table as B and index element as C which gets load to A. | * dest(8_Bits), * val(9_Bits), * val(9_Bits) */
      OP_SETTABUP, /* (8) | Gets table upvalue as A and index element as B and sets A to the index. | * upv(8_Bits), * val(9_Bits), * val(9_Bits) */
      OP_SETUPVAL, /* (9) | * upv(8_Bits), * val(9_Bits) */
      OP_SETTABLE, /* (a) | * src(8_Bits), * val(9_Bits), * val(9_Bits) */
      OP_NEWTABLE, /* (b) | Creates new table with B being array size and C being hash size. | * dest(8_Bits), * tsize(9_Bits), * tsize(9_Bits) */
      OP_SELF,     /* (c) | Call to self. | * dest(8_Bits), * val(9_Bits), * val(9_Bits) */
      OP_ADD,      /* (d) | Add B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_SUB,      /* (e) | Sub B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_MUL,      /* (f) | Multiply B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_MOD,      /* (10) | Modulus B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_POW,      /* (11) | Power B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_DIV,      /* (12) | Divide B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_IDIV,     /* (13) | Floor division B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_BAND,     /* (14) | Bitwise and B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_BOR,      /* (15) | Bitwise or B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_BXOR,     /* (16) | Bitwise xor division B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_SHL,      /* (17) | Shift left B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_SHR,      /* (18) | Shift right B to C and load results to A. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_UNM,      /* (19) | Unary minus A to B and load results to A. | * dest(8_Bits), * src(9_Bits) */
      OP_BNOT,     /* (1a) | Binary not A to B and load results to A. | * dest(8_Bits), * src(9_Bits) */
      OP_NOT,      /* (1b) | Unary not A to B and load results to A. | * dest(8_Bits), * src(9_Bits) */
      OP_LEN,      /* (1c) | Unary length of table B and load results to A. | * dest(8_Bits), * src(9_Bits) */
      OP_CONCAT,   /* (1d) | Concat string where start of stack B to C. | * dest(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_JMP,      /* (1e) | Jump to sBx if A is not 0 then all upvalues >= A - 1 will be closed. | * va;(8_Bits), * jmp(MAXINT) */
      OP_EQ,       /* (1f) | Compare equal B to C and if comparision is not A skip next instruction. | * va;(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_LT,       /* (20) | Compare less than B to C and if comparision is not A skip next instruction. | * va;(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_LE,       /* (21) | Compare less than equal B to C and if comparision is not A skip next instruction. | * va;(8_Bits), * src(9_Bits), * src(9_Bits) */
      OP_TEST,     /* (22) | Compare A to C and if false skip next instruction | * src(8_Bits), * val(9_Bits) */
      OP_TESTSET,  /* (23) | Compare B to C and if false skip next instruction else set A to B. | * src(8_Bits), * src(9_Bits), * val(9_Bits) */
      OP_CALL,     /* (24) | Call A with B args and C return. | * src(8_Bits), * multret(9_Bits), * multret(9_Bits) */
      OP_TAILCALL, /* (25) | Return call A with B args and C return. | * src(8_Bits), * multret(9_Bits), * multret(9_Bits) */
      OP_RETURN,   /* (26) | Return from start A to A + B - 2. | * src(8_Bits), * multret(9_Bits) */
      OP_FORLOOP,  /* (27) | For loop follows for format starting A with sBx jump. | * src(8_Bits), * jmp(MAXINT) */
      OP_FORPREP,  /* (28) | For loop follows for format starting A with sBx jump. | * src(8_Bits), * jmp(MAXINT) */
      OP_TFORCALL, /* (29) | For prep calls iterator function. | * src(8_Bits), * val(9_Bits) */
      OP_TFORLOOP, /* (2a) | For loop follows T for format starting A with sBx jump. | * src(8_Bits), * jmp(MAXINT) */
      OP_SETLIST,  /* (2b) | Sets the values for a range of array elements in a table referenced by A, B is the number of elements to set, C encodes the block number initialized. | * src(8_Bits), * multret(9_Bits), * multret(9_Bits) */
      OP_CLOSURE,  /* (2c) | Set to kvalue proto. | * src(8_Bits), * kidxp(18_Bits) */
      OP_VARARG,   /* (2d) | Set range A + 1 to A + B - e1 to vararg. | * src(8_Bits), * multret(9_Bits) */
      OP_EXTRAARG  /* (2e) | Extra arg Ax for previous opcode. | * src(26_Bits) */
};

enum class operand_encoding {
      A,
      B,
      Bx,
      Ax,
      C,
      sBx
};

enum class operand_kind {
      dest,
      reg,
      k_idx,
      val,
      jmp,
      upvalue,
      table_size,
      val_multret,
      k_idx_p
};

struct optable_encoding {
      opcodes op;
      std::vector<operand_encoding> encodings;
};
static std::map<opcodes, optable_encoding> opencodings = {
    {opcodes::OP_MOVE, {opcodes::OP_MOVE, {operand_encoding::A, operand_encoding::B}}},                              /* 0 */
    {opcodes::OP_LOADK, {opcodes::OP_LOADK, {operand_encoding::A, operand_encoding::Bx}}},                           /* 1 */
    {opcodes::OP_LOADKX, {opcodes::OP_LOADKX, {operand_encoding::Ax}}},                                              /* 2 */
    {opcodes::OP_LOADBOOL, {opcodes::OP_LOADBOOL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 3 */
    {opcodes::OP_LOADNIL, {opcodes::OP_LOADNIL, {operand_encoding::A, operand_encoding::B}}},                        /* 4 */
    {opcodes::OP_GETUPVAL, {opcodes::OP_GETUPVAL, {operand_encoding::A, operand_encoding::B}}},                      /* 5 */
    {opcodes::OP_GETTABUP, {opcodes::OP_GETTABUP, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 6 */
    {opcodes::OP_GETTABLE, {opcodes::OP_GETTABLE, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 7 */
    {opcodes::OP_SETTABUP, {opcodes::OP_SETTABUP, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 8 */
    {opcodes::OP_SETUPVAL, {opcodes::OP_SETUPVAL, {operand_encoding::A, operand_encoding::B}}},                      /* 9 */
    {opcodes::OP_SETTABLE, {opcodes::OP_SETTABLE, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* a */
    {opcodes::OP_NEWTABLE, {opcodes::OP_NEWTABLE, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* b */
    {opcodes::OP_SELF, {opcodes::OP_SELF, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* c */
    {opcodes::OP_ADD, {opcodes::OP_ADD, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* d */
    {opcodes::OP_SUB, {opcodes::OP_SUB, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* e */
    {opcodes::OP_MUL, {opcodes::OP_MUL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* f */
    {opcodes::OP_MOD, {opcodes::OP_MOD, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 10 */
    {opcodes::OP_POW, {opcodes::OP_POW, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 11 */
    {opcodes::OP_DIV, {opcodes::OP_DIV, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 12 */
    {opcodes::OP_IDIV, {opcodes::OP_IDIV, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* 13 */
    {opcodes::OP_BAND, {opcodes::OP_BAND, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* 14 */
    {opcodes::OP_BOR, {opcodes::OP_BOR, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 15 */
    {opcodes::OP_BXOR, {opcodes::OP_BXOR, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* 16 */
    {opcodes::OP_SHL, {opcodes::OP_SHL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 17 */
    {opcodes::OP_SHR, {opcodes::OP_SHR, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},           /* 18 */
    {opcodes::OP_UNM, {opcodes::OP_UNM, {operand_encoding::A, operand_encoding::B}}},                                /* 19 */
    {opcodes::OP_BNOT, {opcodes::OP_BNOT, {operand_encoding::A, operand_encoding::B}}},                              /* 1a */
    {opcodes::OP_NOT, {opcodes::OP_NOT, {operand_encoding::A, operand_encoding::B}}},                                /* 1b */
    {opcodes::OP_LEN, {opcodes::OP_LEN, {operand_encoding::A, operand_encoding::B}}},                                /* 1c */
    {opcodes::OP_CONCAT, {opcodes::OP_CONCAT, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},     /* 1d */
    {opcodes::OP_JMP, {opcodes::OP_JMP, {operand_encoding::A, operand_encoding::sBx}}},                              /* 1e */
    {opcodes::OP_EQ, {opcodes::OP_EQ, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},             /* 1f */
    {opcodes::OP_LT, {opcodes::OP_LT, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},             /* 20 */
    {opcodes::OP_LE, {opcodes::OP_LE, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},             /* 21 */
    {opcodes::OP_TEST, {opcodes::OP_TEST, {operand_encoding::A, operand_encoding::C}}},                              /* 22 */
    {opcodes::OP_TESTSET, {opcodes::OP_TESTSET, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},   /* 23 */
    {opcodes::OP_CALL, {opcodes::OP_CALL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},         /* 24 */
    {opcodes::OP_TAILCALL, {opcodes::OP_TAILCALL, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}}, /* 25 */
    {opcodes::OP_RETURN, {opcodes::OP_RETURN, {operand_encoding::A, operand_encoding::B}}},                          /* 26 */
    {opcodes::OP_FORLOOP, {opcodes::OP_FORLOOP, {operand_encoding::A, operand_encoding::sBx}}},                      /* 27 */
    {opcodes::OP_FORPREP, {opcodes::OP_FORPREP, {operand_encoding::A, operand_encoding::sBx}}},                      /* 28 */
    {opcodes::OP_TFORCALL, {opcodes::OP_TFORCALL, {operand_encoding::A, operand_encoding::C}}},                      /* 29 */
    {opcodes::OP_TFORLOOP, {opcodes::OP_TFORLOOP, {operand_encoding::A, operand_encoding::sBx}}},                    /* 2a */
    {opcodes::OP_SETLIST, {opcodes::OP_SETLIST, {operand_encoding::A, operand_encoding::B, operand_encoding::C}}},   /* 2b */
    {opcodes::OP_CLOSURE, {opcodes::OP_CLOSURE, {operand_encoding::A, operand_encoding::Bx}}},                       /* 2c */
    {opcodes::OP_VARARG, {opcodes::OP_VARARG, {operand_encoding::A, operand_encoding::B}}},                          /* 2d */
    {opcodes::OP_EXTRAARG, {opcodes::OP_EXTRAARG, {operand_encoding::Ax}}}                                           /* 2e */
};

struct optable_kind {
      opcodes op;
      std::vector<operand_kind> kinds;
};
static std::map<opcodes, optable_kind> opkinds = {
    {opcodes::OP_MOVE, {opcodes::OP_MOVE, {operand_kind::dest, operand_kind::reg}}},                                           /* 0 */
    {opcodes::OP_LOADK, {opcodes::OP_LOADK, {operand_kind::dest, operand_kind::k_idx}}},                                       /* 1 */
    {opcodes::OP_LOADKX, {opcodes::OP_LOADKX, {operand_kind::dest}}},                                                          /* 2 */
    {opcodes::OP_LOADBOOL, {opcodes::OP_LOADBOOL, {operand_kind::dest, operand_kind::val, operand_kind::jmp}}},                /* 3 */
    {opcodes::OP_LOADNIL, {opcodes::OP_LOADNIL, {operand_kind::dest, operand_kind::val}}},                                     /* 4 */
    {opcodes::OP_GETUPVAL, {opcodes::OP_GETUPVAL, {operand_kind::dest, operand_kind::upvalue}}},                               /* 5 */
    {opcodes::OP_GETTABUP, {opcodes::OP_GETTABUP, {operand_kind::dest, operand_kind::upvalue, operand_kind::val}}},            /* 6 */
    {opcodes::OP_GETTABLE, {opcodes::OP_GETTABLE, {operand_kind::dest, operand_kind::val, operand_kind::val}}},                /* 7 */
    {opcodes::OP_SETTABUP, {opcodes::OP_SETTABUP, {operand_kind::upvalue, operand_kind::val, operand_kind::val}}},             /* 8 */
    {opcodes::OP_SETUPVAL, {opcodes::OP_SETUPVAL, {operand_kind::upvalue, operand_kind::val}}},                                /* 9 */
    {opcodes::OP_SETTABLE, {opcodes::OP_SETTABLE, {operand_kind::reg, operand_kind::val, operand_kind::val}}},                 /* a */
    {opcodes::OP_NEWTABLE, {opcodes::OP_NEWTABLE, {operand_kind::dest, operand_kind::table_size, operand_kind::table_size}}},  /* b */
    {opcodes::OP_SELF, {opcodes::OP_SELF, {operand_kind::dest, operand_kind::val, operand_kind::val}}},                        /* c */
    {opcodes::OP_ADD, {opcodes::OP_ADD, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* d */
    {opcodes::OP_SUB, {opcodes::OP_SUB, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* e */
    {opcodes::OP_MUL, {opcodes::OP_MUL, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* f */
    {opcodes::OP_MOD, {opcodes::OP_MOD, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 10 */
    {opcodes::OP_POW, {opcodes::OP_POW, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 11 */
    {opcodes::OP_DIV, {opcodes::OP_DIV, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 12 */
    {opcodes::OP_IDIV, {opcodes::OP_IDIV, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                        /* 13 */
    {opcodes::OP_BAND, {opcodes::OP_BAND, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                        /* 14 */
    {opcodes::OP_BOR, {opcodes::OP_BOR, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 15 */
    {opcodes::OP_BXOR, {opcodes::OP_BXOR, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                        /* 16 */
    {opcodes::OP_SHL, {opcodes::OP_SHL, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 17 */
    {opcodes::OP_SHR, {opcodes::OP_SHR, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                          /* 18 */
    {opcodes::OP_UNM, {opcodes::OP_UNM, {operand_kind::dest, operand_kind::reg}}},                                             /* 19 */
    {opcodes::OP_BNOT, {opcodes::OP_BNOT, {operand_kind::dest, operand_kind::reg}}},                                           /* 1a */
    {opcodes::OP_NOT, {opcodes::OP_NOT, {operand_kind::dest, operand_kind::reg}}},                                             /* 1b */
    {opcodes::OP_LEN, {opcodes::OP_LEN, {operand_kind::dest, operand_kind::reg}}},                                             /* 1c */
    {opcodes::OP_CONCAT, {opcodes::OP_CONCAT, {operand_kind::dest, operand_kind::reg, operand_kind::reg}}},                    /* 1d */
    {opcodes::OP_JMP, {opcodes::OP_JMP, {operand_kind::val, operand_kind::jmp}}},                                              /* 1e */
    {opcodes::OP_EQ, {opcodes::OP_EQ, {operand_kind::val, operand_kind::reg, operand_kind::reg}}},                             /* 1f */
    {opcodes::OP_LT, {opcodes::OP_LT, {operand_kind::val, operand_kind::reg, operand_kind::reg}}},                             /* 20 */
    {opcodes::OP_LE, {opcodes::OP_LE, {operand_kind::val, operand_kind::reg, operand_kind::reg}}},                             /* 21 */
    {opcodes::OP_TEST, {opcodes::OP_TEST, {operand_kind::reg, operand_kind::val}}},                                            /* 22 */
    {opcodes::OP_TESTSET, {opcodes::OP_TESTSET, {operand_kind::reg, operand_kind::reg, operand_kind::val}}},                   /* 23 */
    {opcodes::OP_CALL, {opcodes::OP_CALL, {operand_kind::reg, operand_kind::val_multret, operand_kind::val_multret}}},         /* 24 */
    {opcodes::OP_TAILCALL, {opcodes::OP_TAILCALL, {operand_kind::reg, operand_kind::val_multret, operand_kind::val_multret}}}, /* 25 */
    {opcodes::OP_RETURN, {opcodes::OP_RETURN, {operand_kind::reg, operand_kind::val_multret}}},                                /* 26 */
    {opcodes::OP_FORLOOP, {opcodes::OP_FORLOOP, {operand_kind::reg, operand_kind::jmp}}},                                      /* 27 */
    {opcodes::OP_FORPREP, {opcodes::OP_FORPREP, {operand_kind::reg, operand_kind::jmp}}},                                      /* 28 */
    {opcodes::OP_TFORCALL, {opcodes::OP_TFORCALL, {operand_kind::reg, operand_kind::val}}},                                    /* 29 */
    {opcodes::OP_TFORLOOP, {opcodes::OP_TFORLOOP, {operand_kind::reg, operand_kind::jmp}}},                                    /* 2a */
    {opcodes::OP_SETLIST, {opcodes::OP_SETLIST, {operand_kind::reg, operand_kind::val_multret, operand_kind::val_multret}}},   /* 2b */
    {opcodes::OP_CLOSURE, {opcodes::OP_CLOSURE, {operand_kind::reg, operand_kind::k_idx_p}}},                                  /* 2c */
    {opcodes::OP_VARARG, {opcodes::OP_VARARG, {operand_kind::reg, operand_kind::val_multret}}},                                /* 2d */
    {opcodes::OP_EXTRAARG, {opcodes::OP_EXTRAARG, {operand_kind::reg}}}                                                        /* 2e */
};

struct optable_descriptor {
      const char *const opname;
      const char *const mnemonic;
      const char *const hint;
      std::vector<const char *> operand_encodings;
};
static std::map<opcodes, optable_descriptor> opdescriptor = {
    {opcodes::OP_MOVE, {"OP_MOVE", "move", "Move source register to dest register.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                           /* 0 */
    {opcodes::OP_LOADK, {"OP_LOADK", "loadk", "Load kvalue to destination register.", {"dest(Register)", "kidx(Kvalue Index)"}}},                                                                                                                                                     /* 1 */
    {opcodes::OP_LOADKX, {"OP_LOADKX", "loadkx", "Load kvalue extended.", {"dest(Register)"}}},                                                                                                                                                                                       /* 2 */
    {opcodes::OP_LOADBOOL, {"OP_LOADBOOL", "loadbool", "Load boolean to register and take jump.", {"dest(Register)", "val(Value)", "jmp(Jump)"}}},                                                                                                                                    /* 3 */
    {opcodes::OP_LOADNIL, {"OP_LOADNIL", "loadnil", "Iteration start at first target register then increments above the stack and fills with NIL set by source value.", {"dest(Register)", "val(Value)"}}},                                                                           /* 4 */
    {opcodes::OP_GETUPVAL, {"OP_GETUPVAL", "getupval", "Load upvalue to destination register.", {"dest(Register)", "upv(Upvalue)"}}},                                                                                                                                                 /* 5 */
    {opcodes::OP_GETTABUP, {"OP_GETTABUP", "gettabup", "Gets table upvalue as B and index element as C which gets load to A.", {"dest(Register)", "upv(Upvalue)", "val(Value)"}}},                                                                                                    /* 6 */
    {opcodes::OP_GETTABLE, {"OP_GETTABLE", "gettable", "Gets table as B and index element as C which gets load to A.", {"dest(Register)", "val(Value)", "val(Value)"}}},                                                                                                              /* 7 */
    {opcodes::OP_SETTABUP, {"OP_SETTABUP", "settabup", "Gets table upvalue as A and index element as B and sets A to the index.", {"upv(Upvalue)", "val(Value)", "val(Value)"}}},                                                                                                     /* 8 */
    {opcodes::OP_SETUPVAL, {"OP_SETUPVAL", "setupval", "", {"upv(Upvalue)", "val(Value)"}}},                                                                                                                                                                                          /* 9 */
    {opcodes::OP_SETTABLE, {"OP_SETTABLE", "settable", "", {"src(Register)", "val(Value)", "val(Value)"}}},                                                                                                                                                                           /* a */
    {opcodes::OP_NEWTABLE, {"OP_NEWTABLE", "newtable", "Creates new table with B being array size and C being hash size.", {"dest(Register)", "tsize(Table Size)", "tsize(Table Size)"}}},                                                                                            /* b */
    {opcodes::OP_SELF, {"OP_SELF", "self", "Call to self.", {"dest(Register)", "val(Value)", "val(Value)"}}},                                                                                                                                                                         /* c */
    {opcodes::OP_ADD, {"OP_ADD", "add", "Add B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                                  /* d */
    {opcodes::OP_SUB, {"OP_SUB", "sub", "Sub B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                                  /* e */
    {opcodes::OP_MUL, {"OP_MUL", "mul", "Multiply B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                             /* f */
    {opcodes::OP_MOD, {"OP_MOD", "mod", "Modulus B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                              /* 10 */
    {opcodes::OP_POW, {"OP_POW", "pow", "Power B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                                /* 11 */
    {opcodes::OP_DIV, {"OP_DIV", "div", "Divide B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                               /* 12 */
    {opcodes::OP_IDIV, {"OP_IDIV", "idiv", "Floor division B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                    /* 13 */
    {opcodes::OP_BAND, {"OP_BAND", "band", "Bitwise and B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                       /* 14 */
    {opcodes::OP_BOR, {"OP_BOR", "bor", "Bitwise or B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                           /* 15 */
    {opcodes::OP_BXOR, {"OP_BXOR", "bxor", "Bitwise xor division B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                              /* 16 */
    {opcodes::OP_SHL, {"OP_SHL", "shl", "Shift left B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                           /* 17 */
    {opcodes::OP_SHR, {"OP_SHR", "shr", "Shift right B to C and load results to A.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                          /* 18 */
    {opcodes::OP_UNM, {"OP_UNM", "unm", "Unary minus A to B and load results to A.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                           /* 19 */
    {opcodes::OP_BNOT, {"OP_BNOT", "bnot", "Binary not A to B and load results to A.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                         /* 1a */
    {opcodes::OP_NOT, {"OP_NOT", "not", "Unary not A to B and load results to A.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                             /* 1b */
    {opcodes::OP_LEN, {"OP_LEN", "len", "Unary length of table B and load results to A.", {"dest(Register)", "src(Register)"}}},                                                                                                                                                      /* 1c */
    {opcodes::OP_CONCAT, {"OP_CONCAT", "concat", "Concat string where start of stack B to C.", {"dest(Register)", "src(Register)", "src(Register)"}}},                                                                                                                                /* 1d */
    {opcodes::OP_JMP, {"OP_JMP", "jmp", "Jump to sBx if A is not 0 then all upvalues >= A - 1 will be closed.", {"va;(Value)", "jmp(Jump)"}}},                                                                                                                                        /* 1e */
    {opcodes::OP_EQ, {"OP_EQ", "eq", "Compare equal B to C and if comparision is not A skip next instruction.", {"va;(Value)", "src(Register)", "src(Register)"}}},                                                                                                                   /* 1f */
    {opcodes::OP_LT, {"OP_LT", "lt", "Compare less than B to C and if comparision is not A skip next instruction.", {"va;(Value)", "src(Register)", "src(Register)"}}},                                                                                                               /* 20 */
    {opcodes::OP_LE, {"OP_LE", "le", "Compare less than equal B to C and if comparision is not A skip next instruction.", {"va;(Value)", "src(Register)", "src(Register)"}}},                                                                                                         /* 21 */
    {opcodes::OP_TEST, {"OP_TEST", "test", "Compare A to C and if false skip next instruction", {"src(Register)", "val(Value)"}}},                                                                                                                                                    /* 22 */
    {opcodes::OP_TESTSET, {"OP_TESTSET", "testset", "Compare B to C and if false skip next instruction else set A to B.", {"src(Register)", "src(Register)", "val(Value)"}}},                                                                                                         /* 23 */
    {opcodes::OP_CALL, {"OP_CALL", "call", "Call A with B args and C return.", {"src(Register)", "multret(Multret Value)", "multret(Multret Value)"}}},                                                                                                                               /* 24 */
    {opcodes::OP_TAILCALL, {"OP_TAILCALL", "tailcall", "Return call A with B args and C return.", {"src(Register)", "multret(Multret Value)", "multret(Multret Value)"}}},                                                                                                            /* 25 */
    {opcodes::OP_RETURN, {"OP_RETURN", "return", "Return from start A to A + B - 2.", {"src(Register)", "multret(Multret Value)"}}},                                                                                                                                                  /* 26 */
    {opcodes::OP_FORLOOP, {"OP_FORLOOP", "forloop", "For loop follows for format starting A with sBx jump.", {"src(Register)", "jmp(Jump)"}}},                                                                                                                                        /* 27 */
    {opcodes::OP_FORPREP, {"OP_FORPREP", "forprep", "For loop follows for format starting A with sBx jump.", {"src(Register)", "jmp(Jump)"}}},                                                                                                                                        /* 28 */
    {opcodes::OP_TFORCALL, {"OP_TFORCALL", "tforcall", "For prep calls iterator function.", {"src(Register)", "val(Value)"}}},                                                                                                                                                        /* 29 */
    {opcodes::OP_TFORLOOP, {"OP_TFORLOOP", "tforloop", "For loop follows T for format starting A with sBx jump.", {"src(Register)", "jmp(Jump)"}}},                                                                                                                                   /* 2a */
    {opcodes::OP_SETLIST, {"OP_SETLIST", "setlist", "Sets the values for a range of array elements in a table referenced by A, B is the number of elements to set, C encodes the block number initialized.", {"src(Register)", "multret(Multret Value)", "multret(Multret Value)"}}}, /* 2b */
    {opcodes::OP_CLOSURE, {"OP_CLOSURE", "closure", "Set to kvalue proto.", {"src(Register)", "kidxp(Kvalue Proto Index)"}}},                                                                                                                                                         /* 2c */
    {opcodes::OP_VARARG, {"OP_VARARG", "vararg", "Set range A + 1 to A + B - e1 to vararg.", {"src(Register)", "multret(Multret Value)"}}},                                                                                                                                           /* 2d */
    {opcodes::OP_EXTRAARG, {"OP_EXTRAARG", "extraarg", "Extra arg Ax for previous opcode.", {"src(Register)"}}}                                                                                                                                                                       /* 2e */
};