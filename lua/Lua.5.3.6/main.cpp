#include "iscreate/iscreate.hpp"
#include <iostream>

#define IS_SIZE_A "8Bits"
#define IS_SIZE_B "9Bits"
#define IS_SIZE_C "9Bits"
#define IS_SIZE_Bx "18Bits"
#define IS_SIZE_Ax "26Bits"
#define IS_SIZE_sBx "Signed 18Bits"

std::int32_t main() {

      iscreate::instruction_set is("Lua_5_3_6");

      /* A */
      const auto A_dest_reg = iscreate::create_operand("dest", "A", IS_SIZE_A, "Register", "dest");     /* Dest register */
      const auto A_src_reg = iscreate::create_operand("src", "A", IS_SIZE_A, "Register", "reg");        /* Source register */
      const auto A_val_val = iscreate::create_operand("va;", "A", IS_SIZE_A, "Value", "val");           /* Value number */
      const auto A_upv_upvalue = iscreate::create_operand("upv", "A", IS_SIZE_A, "Upvalue", "upvalue"); /* Upvalue */
      const auto Ax_dest_reg = iscreate::create_operand("dest", "Ax", IS_SIZE_Ax, "Register", "dest");  /* Dest register */
      const auto Ax_src_reg = iscreate::create_operand("src", "Ax", IS_SIZE_Ax, "Register", "reg");     /* Dest register */

      /* B */
      const auto B_src_reg = iscreate::create_operand("src", "B", IS_SIZE_B, "Register", "reg");                          /* Source register */
      const auto B_val_val = iscreate::create_operand("val", "B", IS_SIZE_B, "Value", "val");                             /* Value number */
      const auto B_multret_mulret = iscreate::create_operand("multret", "B", IS_SIZE_B, "Multret Value", "val_multret");  /* Multret value */
      const auto B_upv_upvalue = iscreate::create_operand("upv", "B", IS_SIZE_B, "Upvalue", "upvalue");                   /* Upvalue */
      const auto B_tsize_table_size = iscreate::create_operand("tsize", "B", IS_SIZE_B, "Table Size", "table_size");      /* Table size */
      const auto Bx_kidx_k_idx = iscreate::create_operand("kidx", "Bx", IS_SIZE_Bx, "Kvalue Index", "k_idx");             /* Kvalue index */
      const auto Bx_kidxp_k_idx_p = iscreate::create_operand("kidxp", "Bx", IS_SIZE_Bx, "Kvalue Proto Index", "k_idx_p"); /* Kvalue index proto */
      const auto sBx_jmp_jmp = iscreate::create_operand("jmp", "sBx", IS_SIZE_sBx, "Jump", "jmp");                        /* Jump */

      /* C */
      const auto C_src_reg = iscreate::create_operand("src", "C", IS_SIZE_C, "Register", "reg");                         /* Source register */
      const auto C_val_val = iscreate::create_operand("val", "C", IS_SIZE_C, "Value", "val");                            /* Value number */
      const auto C_tsize_table_size = iscreate::create_operand("tsize", "C", IS_SIZE_C, "Table Size", "table_size");     /* Table size */
      const auto C_multret_mulret = iscreate::create_operand("multret", "C", IS_SIZE_C, "Multret Value", "val_multret"); /* Multret value */
      const auto C_jmp_jmp = iscreate::create_operand("jmp", "C", IS_SIZE_C, "Jump", "jmp");                             /* Jump */

      is.add("move", "Move source register to dest register.", {A_dest_reg, B_src_reg});

      is.add("loadk", "Load kvalue to destination register.", {A_dest_reg, Bx_kidx_k_idx});
      is.add("loadkx", "Load kvalue extended.", {Ax_dest_reg});
      is.add("loadbool", "Load boolean to register and take jump.", {A_dest_reg, B_val_val, C_jmp_jmp});
      is.add("loadnil", "Iteration start at first target register then increments above the stack and fills with NIL set by source value.", {A_dest_reg, B_val_val});
      is.add("getupval", "Load upvalue to destination register.", {A_dest_reg, B_upv_upvalue});

      is.add("gettabup", "Gets table upvalue as B and index element as C which gets load to A.", {A_dest_reg, B_upv_upvalue, C_val_val});
      is.add("gettable", "Gets table as B and index element as C which gets load to A.", {A_dest_reg, B_val_val, C_val_val});

      is.add("settabup", "Gets table upvalue as A and index element as B and sets A to the index.", {A_upv_upvalue, B_val_val, C_val_val});
      is.add("setupval", "", {A_upv_upvalue, B_val_val});
      is.add("settable", "", {A_src_reg, B_val_val, C_val_val});

      is.add("newtable", "Creates new table with B being array size and C being hash size.", {A_dest_reg, B_tsize_table_size, C_tsize_table_size});
      is.add("self", "Call to self.", {A_dest_reg, B_val_val, C_val_val});

      is.add("add", "Add B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("sub", "Sub B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("mul", "Multiply B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("mod", "Modulus B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("pow", "Power B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("div", "Divide B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("idiv", "Floor division B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("band", "Bitwise and B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("bor", "Bitwise or B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("bxor", "Bitwise xor division B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("shl", "Shift left B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("shr", "Shift right B to C and load results to A.", {A_dest_reg, B_src_reg, C_src_reg});
      is.add("unm", "Unary minus A to B and load results to A.", {A_dest_reg, B_src_reg});
      is.add("bnot", "Binary not A to B and load results to A.", {A_dest_reg, B_src_reg});
      is.add("not", "Unary not A to B and load results to A.", {A_dest_reg, B_src_reg});
      is.add("len", "Unary length of table B and load results to A.", {A_dest_reg, B_src_reg});

      is.add("concat", "Concat string where start of stack B to C.", {A_dest_reg, B_src_reg, C_src_reg});

      is.add("jmp", "Jump to sBx if A is not 0 then all upvalues >= A - 1 will be closed.", {A_val_val, sBx_jmp_jmp});
      is.add("eq", "Compare equal B to C and if comparision is not A skip next instruction.", {A_val_val, B_src_reg, C_src_reg});
      is.add("lt", "Compare less than B to C and if comparision is not A skip next instruction.", {A_val_val, B_src_reg, C_src_reg});
      is.add("le", "Compare less than equal B to C and if comparision is not A skip next instruction.", {A_val_val, B_src_reg, C_src_reg});

      is.add("test", "Compare A to C and if false skip next instruction", {A_src_reg, C_val_val});
      is.add("testset", "Compare B to C and if false skip next instruction else set A to B.", {A_src_reg, B_src_reg, C_val_val});

      is.add("call", "Call A with B args and C return.", {A_src_reg, B_multret_mulret, C_multret_mulret});
      is.add("tailcall", "Return call A with B args and C return.", {A_src_reg, B_multret_mulret, C_multret_mulret});

      is.add("return", "Return from start A to A + B - 2.", {A_src_reg, B_multret_mulret});

      is.add("forloop", "For loop follows for format starting A with sBx jump.", {A_src_reg, sBx_jmp_jmp});
      is.add("forprep", "For loop follows for format starting A with sBx jump.", {A_src_reg, sBx_jmp_jmp});
      is.add("tforcall", "For prep calls iterator function.", {A_src_reg, C_val_val});
      is.add("tforloop", "For loop follows T for format starting A with sBx jump.", {A_src_reg, sBx_jmp_jmp});

      is.add("setlist", "Sets the values for a range of array elements in a table referenced by A, B is the number of elements to set, C encodes the block number initialized.", {A_src_reg, B_multret_mulret, C_multret_mulret});

      is.add("closure", "Set to kvalue proto.", {A_src_reg, Bx_kidxp_k_idx_p});
      is.add("vararg", "Set range A + 1 to A + B - e1 to vararg.", {A_src_reg, B_multret_mulret});
      is.add("extraarg", "Extra arg Ax for previous opcode.", {Ax_src_reg});

      is.save("IS_Lua_5_3_6.json");

      std::cout << "\n"
                << is.represent_enum_opcodes() << std::endl;
      std::cout << "\n"
                << is.represent_enum_opencodings() << std::endl;
      std::cout << "\n"
                << is.represent_enum_opkinds() << std::endl;
      std::cout << "\n\n"
                << is.represent_opencodings() << std::endl;
      std::cout << "\n\n"
                << is.represent_opkinds() << std::endl;
      std::cout << "\n\n"
                << is.represent_opdescriptors() << std::endl;

      std::cin.get();

      return 0;
}