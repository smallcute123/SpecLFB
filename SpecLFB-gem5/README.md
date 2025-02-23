# SpecLFB-GEM5
This folder contains the source code of SpecLFB implemented in the [gem5 simulator](https://github.com/gem5/gem5).

## Major changes in the simulator.

We made major changes in `src/cpu/o3/` and `src/mem/cache/`, `git grep -il speclfb` should reveal most/all of the files we changed.


## How to run the simulator?
Refer to the makefile.

* Step1: build gem5.opt
  * `make riscv64` or  `make x86-64`
* Step2: run spectre attack on the simulator
  * `make s1riscv` or  `make s1x86`

We added a configuration paramter to the simulator for unsafe and safe modes as follows.
* --scheme:
  * unsafebaseline: the unmodified out-of-order CPU
  * Speclfb: the out-of-order CPU enhanced with SpecLFB.

Please modify the makefile to switch the mode.


The simulator can work using RISCV and X86 ISAs


