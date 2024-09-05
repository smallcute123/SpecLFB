GEM5_SIMULATOR_RISCV 	 = 	./build/RISCV/gem5.opt
GEM5_SIMULATOR_X86 	 = 	./build/X86/gem5.opt

DEBUGFLAGS 		+= 	--debug-flags=Speclfb\
			 		--debug-file=trace.out \

BOOMFLAGS 		+=   configs/example/se.py \
					--num-cpus=1 \
					--bp-type=BiModeBP \
			 		--caches \
					--l2cache \
					--cacheline=64 \
					--num-l2cache=1 \
			 		--l1i_size=64kB \
			 		--l1i_assoc=4 \
					--l1d_size=16kB \
			 		--l1d_assoc=4 \
					--l2_size=256kB \
					--l2_assoc=4 \
					--mem-size=8192MB \
					--cpu-type=DerivO3CPU\
					--scheme=Speclfb\

# --scheme=unsafebaseline



BIN 	   		=   --cmd=./mycode/attack_src/spectre-attack-riscv/bin/dcacheTest.riscv



# run dcachetest
run: 
	$(GEM5_SIMULATOR_RISCV) $(BOOMFLAGS) $(BIN)

# run spectre-v1 on riscv
s1riscv:
	$(GEM5_SIMULATOR_RISCV) $(BOOMFLAGS) --cmd=./mycode/attack_src/spectre-attack-riscv/bin/spectre-v1.riscv

# run spectre-v1 on x86
s1x86:
	$(GEM5_SIMULATOR_X86) $(BOOMFLAGS) --cmd=./mycode/attack_src/spectre-attack-intel/bin/spectre-v1.x86

s4x86:
	$(GEM5_SIMULATOR_X86) $(BOOMFLAGS) --cmd=./mycode/attack_src/spectre-attack-intel/bin/spectre-v4.x86
#debug exemple，see the debug output in m5out/trace.out
debugv1:
	$(GEM5_SIMULATOR) $(DEBUGFLAGS) $(BOOMFLAGS) --cmd=./mycode/attack_src/spectre-attack-riscv/bin/spectre-v1.riscv 


# build pipeview file
pipeview:
	./util/o3-pipeview.py -c 500 -o pipeview.out --color m5out/trace.out
	less -r pipeview.out

# build gem5.opt
riscv64:
	scons build/RISCV/gem5.opt

x86-64:
	scons build/X86/gem5.opt
