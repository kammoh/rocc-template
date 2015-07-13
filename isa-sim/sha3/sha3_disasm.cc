#include "sha3.h"
#include "disasm.h"

static const char* funct_str(int func){
  switch (func){
    case(0): return "init";
    case (1): return "do";
    default: return "unknown";
  }
}

struct : public arg_t {
  std::string to_string(insn_t insn) const {
    return xpr_name[insn.rs1()];
  }
} xrs1;

struct : public arg_t {
  std::string to_string(insn_t insn) const {
    return xpr_name[insn.rs2()];
  }
} xrs2;

struct : public arg_t {
  std::string to_string(insn_t insn) const {
    return xpr_name[insn.rd()];
  }
} xrd;

struct : public arg_t {
   std::string to_string(insn_t insn) const {
    return funct_str(insn.bits() >> 25 & ((insn_bits_t(1) << 7)-1));
  }
} funct;

std::vector<disasm_insn_t*> sha3_t::get_disasms()
{
  std::vector<disasm_insn_t*> insns;

  #define DECLARE_INSN(code, match, mask) \
   const uint32_t match_##code = match; \
   const uint32_t mask_##code = mask;
  //#include "opcodes_sha3.h"
  DECLARE_INSN(sha3init, 0x300b, 0x707f) 
  DECLARE_INSN(sha3do, 0x200b, 0x707f) 
  //DECLARE_INSN(sha3do, 0x0b, 0x7f) 
  #undef DECLARE_INSN

  #define DISASM_INSN(name, code, ...) \
    insns.push_back(new disasm_insn_t(name, match_##code, mask_##code, __VA_ARGS__));

  DISASM_INSN("sha3init", sha3init, {&xrs1, &xrs2, &funct});
  DISASM_INSN("sha3do", sha3do, {&xrs1 , &funct});
  //DISASM_INSN("sha3do", sha3do, 1, {&xrd, &xrs1, &xrs2});

  return insns;
}
