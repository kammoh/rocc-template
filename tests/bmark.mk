#=======================================================================
# UCB CS250 Makefile fragment for benchmarks
#-----------------------------------------------------------------------
#
# Each benchmark directory should have its own fragment which
# essentially lists what the source files are and how to link them
# into an riscv and/or host executable. All variables should include
# the benchmark name as a prefix so that they are unique.
#

sha3_c_src = \
	sha3-rocc-bm.c \
	syscalls.c \

sha3_riscv_src = \
	crt.S \

sha3_c_objs     = $(patsubst %.c, %.o, $(sha3_c_src))
sha3_riscv_objs = $(patsubst %.S, %.o, $(sha3_riscv_src))

sha3_host_bin = sha3.host
$(sha3_host_bin): $(sha3_c_src)
	$(HOST_COMP) $^ -o $(sha3_host_bin)

sha3_riscv_bin = sha3.riscv
$(sha3_riscv_bin): $(sha3_c_objs) $(sha3_riscv_objs)
	$(RISCV_LINK) $(sha3_c_objs) $(sha3_riscv_objs) -o $(sha3_riscv_bin) $(RISCV_LINK_OPTS)

junk += $(sha3_c_objs) $(sha3_riscv_objs) \
        $(sha3_host_bin) $(sha3_riscv_bin)
