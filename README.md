# SpecLFB

This is the source code for our USENIX Security paper "SpecLFB: Eliminating Cache Side Channels in Speculative Executions".


SpecLFB is a defense scheme against speculative cache side-channel attacks, implemented in the [SonicBOOM](https://github.com/riscv-boom/riscv-boom)and [gem5 simulator](https://github.com/gem5/gem5). It introduces a simple yet effective security check mechanism to the Line-Fill-Buffer(LFB), delaying the execution of unsafe speculative loads andpreventing sensitive data leakage through cache side channels. To minimize the overhead of both processor performanceand hardware resources, SpecLFB limits the scope of unsafespeculative loads that need to be delayed to MUSLs, which denotes unsafe speculative loads that cause cache misses. In addition, SpecLFB transforms them into safe loads and continues their execution as early as possible through the LFB unsafe security check mechanism based on the ROB unsafe mask we designed.

Please refer to the `readme.md` in the `SpecLFB-boom` or `SpecLFB-gem5` folder for specific operation steps.

In addition:

- The `attack_example_riscv` folder contains example attacks for testing on Chipyard.

- The `Spectre-Attacks-in-SonicBOOM` folder contains example attacks specifically designed to run on FPGA hardware using the SonicBOOM core.


