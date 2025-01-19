#!/bin/bash

############ DIRECTORY VARIABLES: MODIFY ACCORDINGLY #############
GEM5_DIR=/home/chengxiaoyu/SpecLFB/SpecLFB-gem5                         # Install location of gem5
SPEC_DIR=/home/chengxiaoyu/spec2017new        # Install location of your SPEC2006 benchmarks


# Get command line input. We will need to check these.
BENCHMARK=$1                    # Benchmark name, e.g. bzip2
OUTPUT_DIR=$2                   # Directory to place run output. Make sure this exists!
######################### BENCHMARK CODENAMES ####################
PERLBENCH_R_CODE=500.perlbench_r
GCC_R_CODE=502.gcc_r
BWAVES_R_CODE=503.bwaves_r
MCF_R_CODE=505.mcf_r
CACTUBSSN_R_CODE=507.cactuBSSN_r
NAMD_R_CODE=508.namd_r
PAREST_R_CODE=510.parest_r
POVRAY_R_CODE=511.povray_r
LBM_R_CODE=519.lbm_r
OMNETPP_R_CODE=520.omnetpp_r
WRF_R_CODE=521.wrf_r
XALANCBMK_R_CODE=523.xalancbmk_r
X264_R_CODE=525.x264_r
BLENDER_R_CODE=526.blender_r
CAM4_R_CODE=527.cam4_r
DEEPSJENG_R_CODE=531.deepsjeng_r
IMAGICK_R_CODE=538.imagick_r
LEELA_R_CODE=541.leela_r
NAB_R_CODE=544.nab_r
EXCHANGE2_R_CODE=548.exchange2_r
FOTONIK3D_R_CODE=549.fotonik3d_r
ROMS_R_CODE=554.roms_r
XZ_R_CODE=557.xz_r
PERLBENCH_S_CODE=600.perlbench_s
GCC_S_CODE=602.gcc_s
BWAVES_S_CODE=603.bwaves_s
MCF_S_CODE=605.mcf_s
CACTUBSSN_S_CODE=607.cactuBSSN_s
LBM_S_CODE=619.lbm_s
OMNETPP_S_CODE=620.omnetpp_s
WRF_S_CODE=621.wrf_s
XALANCBMK_S_CODE=623.xalancbmk_s
X264_S_CODE=625.x264_s
CAM4_S_CODE=627.cam4_s
POP2_S_CODE=628.pop2_s
DEEPSJENG_S_CODE=631.deepsjeng_s
IMAGICK_S_CODE=638.imagick_s
LEELA_S_CODE=641.leela_s
NAB_S_CODE=644.nab_s
EXCHANGE2_S_CODE=648.exchange2_s
FOTONIK3D_S_CODE=649.fotonik3d_s
ROMS_S_CODE=654.roms_s
XZ_S_CODe=657.xz_s
SPECRAND_FS_CODE=996.specrand_fs
SPECRAND_FR_CODE=997.specrand_fr
SPECRAND_IS_CODE=998.specrand_is
SPECRAND_IR_CODE=999.specrand_ir

##################################################################
 
# Check BENCHMARK input
#################### BENCHMARK CODE MAPPING ######################
BENCHMARK_CODE="none"
 
if [[ "$BENCHMARK" == "perlbench_r" ]]; then
    BENCHMARK_CODE=$PERLBENCH_R_CODE
fi
if [[ "$BENCHMARK" == "perlbench_s" ]]; then
    BENCHMARK_CODE=$PERLBENCH_S_CODE
fi
if [[ "$BENCHMARK" == "gcc_r" ]]; then
    BENCHMARK_CODE=$GCC_R_CODE
fi
if [[ "$BENCHMARK" == "gcc_s" ]]; then
    BENCHMARK_CODE=$GCC_S_CODE
fi
if [[ "$BENCHMARK" == "mcf_r" ]]; then
    BENCHMARK_CODE=$MCF_R_CODE
fi
if [[ "$BENCHMARK" == "mcf_s" ]]; then
    BENCHMARK_CODE=$MCF_S_CODE
fi
if [[ "$BENCHMARK" == "omnetpp_r" ]]; then
    BENCHMARK_CODE=$OMNETPP_R_CODE
fi
if [[ "$BENCHMARK" == "omnetpp_s" ]]; then
    BENCHMARK_CODE=$OMNETPP_S_CODE
fi
if [[ "$BENCHMARK" == "xalancbmk_r" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$XALANCBMK_R_CODE
fi
if [[ "$BENCHMARK" == "xalancbmk_s" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$XALANCBMK_S_CODE
fi
if [[ "$BENCHMARK" == "x264_r" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$X264_R_CODE
fi
if [[ "$BENCHMARK" == "x264_s" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$X264_S_CODE
fi
if [[ "$BENCHMARK" == "deepsjeng_r" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$DEEPSJENG_R_CODE
fi
if [[ "$BENCHMARK" == "deepsjeng_s" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$DEEPSJENG_S_CODE
fi
if [[ "$BENCHMARK" == "leela_r" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$LEELA_R_CODE
fi
if [[ "$BENCHMARK" == "leela_s" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$LEELA_S_CODE
fi
if [[ "$BENCHMARK" == "exchange2_r" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$EXCHANGE2_R_CODE
fi
if [[ "$BENCHMARK" == "exchange2_s" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$EXCHANGE2_S_CODE
fi
if [[ "$BENCHMARK" == "xz_r" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$XZ_R_CODE
fi
if [[ "$BENCHMARK" == "xz_s" ]]; then # DOES NOT WORK
    BENCHMARK_CODE=$XZ_S_CODe
fi
if [[ "$BENCHMARK" == "bwaves_r" ]]; then
    BENCHMARK_CODE=$BWAVES_R_CODE
fi
if [[ "$BENCHMARK" == "bwaves_s" ]]; then
    BENCHMARK_CODE=$BWAVES_S_CODE
fi
if [[ "$BENCHMARK" == "cactuBSSN_r" ]]; then
    BENCHMARK_CODE=$CACTUBSSN_R_CODE
fi
if [[ "$BENCHMARK" == "cactuBSSN_s" ]]; then
    BENCHMARK_CODE=$CACTUBSSN_S_CODE
fi
if [[ "$BENCHMARK" == "namd_r" ]]; then
    BENCHMARK_CODE=$NAMD_R_CODE
fi
if [[ "$BENCHMARK" == "parest_r" ]]; then
    BENCHMARK_CODE=$PAREST_R_CODE
fi
if [[ "$BENCHMARK" == "povray_r" ]]; then
    BENCHMARK_CODE=$POVRAY_R_CODE
fi
if [[ "$BENCHMARK" == "lbm_r" ]]; then
    BENCHMARK_CODE=$LBM_R_CODE
fi
if [[ "$BENCHMARK" == "lbm_s" ]]; then
    BENCHMARK_CODE=$LBM_S_CODE
fi
if [[ "$BENCHMARK" == "wrf_r" ]]; then
    BENCHMARK_CODE=$WRF_R_CODE
fi
if [[ "$BENCHMARK" == "wrf_s" ]]; then
    BENCHMARK_CODE=$WRF_S_CODE
fi
if [[ "$BENCHMARK" == "blender_r" ]]; then
    BENCHMARK_CODE=$BLENDER_R_CODE
fi
if [[ "$BENCHMARK" == "cam4_r" ]]; then
    BENCHMARK_CODE=$CAM4_R_CODE
fi
if [[ "$BENCHMARK" == "cam4_s" ]]; then
    BENCHMARK_CODE=$CAM4_S_CODE
fi
if [[ "$BENCHMARK" == "pop2_s" ]]; then
    BENCHMARK_CODE=$POP2_S_CODE
fi
if [[ "$BENCHMARK" == "imagick_r" ]]; then
    BENCHMARK_CODE=$IMAGICK_R_CODE
fi
if [[ "$BENCHMARK" == "imagick_s" ]]; then
    BENCHMARK_CODE=$IMAGICK_S_CODE
fi
if [[ "$BENCHMARK" == "nab_r" ]]; then
    BENCHMARK_CODE=$NAB_R_CODE
fi
if [[ "$BENCHMARK" == "nab_s" ]]; then
    BENCHMARK_CODE=$NAB_S_CODE
fi
if [[ "$BENCHMARK" == "fotonik3d_r" ]]; then
    BENCHMARK_CODE=$FOTONIK3D_R_CODE
fi
if [[ "$BENCHMARK" == "fotonik3d_s" ]]; then
    BENCHMARK_CODE=$FOTONIK3D_S_CODE
fi
if [[ "$BENCHMARK" == "roms_r" ]]; then
    BENCHMARK_CODE=$ROMS_R_CODE
fi
if [[ "$BENCHMARK" == "roms_s" ]]; then
    BENCHMARK_CODE=$ROMS_S_CODE
fi
if [[ "$BENCHMARK" == "specrand_fs" ]]; then
    BENCHMARK_CODE=$SPECRAND_FS_CODE
fi
if [[ "$BENCHMARK" == "specrand_fr" ]]; then
    BENCHMARK_CODE=$SPECRAND_FR_CODE
fi
if [[ "$BENCHMARK" == "specrand_is" ]]; then
    BENCHMARK_CODE=$SPECRAND_IS_CODE
fi
if [[ "$BENCHMARK" == "specrand_ir" ]]; then
    BENCHMARK_CODE=$SPECRAND_IR_CODE
fi

# Sanity check
if [[ "$BENCHMARK_CODE" == "none" ]]; then
    echo "Input benchmark selection $BENCHMARK did not match any known SPEC CPU2017 benchmarks! Exiting."
    exit 1
fi
##################################################################
 
# Check OUTPUT_DIR existence
# if [[ !(-d "$OUTPUT_DIR") ]]; then
#     echo "Output directory $OUTPUT_DIR does not exist! Exiting."
#     exit 1
# fi


if [[ "${BENCHMARK:0-1:1}" == "r" ]]; then
    RUN_DIR=$SPEC_DIR/benchspec/CPU/$BENCHMARK_CODE/run/run_base_refrate\_x86-m64.0000     # Run directory for the selected SPEC benchmark
fi
if [[ "${BENCHMARK:0-1:1}" == "s" ]]; then
    RUN_DIR=$SPEC_DIR/benchspec/CPU/$BENCHMARK_CODE/run/run_base_refspeed\x86-m64.0000     # Run directory for the selected SPEC benchmark
fi
# RUN_DIR=$SPEC_DIR/benchspec/CPU/$BENCHMARK_CODE/build/build_base\_my-riscv-64.0000     # Run directory for the selected SPEC benchmark

SCRIPT_OUT=$GEM5_DIR/$OUTPUT_DIR/runscript.log                                                                    # File log for this script's stdout henceforth
 
################## REPORT SCRIPT CONFIGURATION ###################
 
echo "Command line:"                                | tee $SCRIPT_OUT
echo "$0 $*"                                        | tee -a $SCRIPT_OUT
echo "================= Hardcoded directories ==================" | tee -a $SCRIPT_OUT
echo "GEM5_DIR:                                     $GEM5_DIR" | tee -a $SCRIPT_OUT
echo "SPEC_DIR:                                     $SPEC_DIR" | tee -a $SCRIPT_OUT
echo "==================== Script inputs =======================" | tee -a $SCRIPT_OUT
echo "BENCHMARK:                                    $BENCHMARK" | tee -a $SCRIPT_OUT
echo "OUTPUT_DIR:                                   $OUTPUT_DIR" | tee -a $SCRIPT_OUT
echo "==========================================================" | tee -a $SCRIPT_OUT
##################################################################
 
 
#################### LAUNCH GEM5 SIMULATION ######################
echo ""
echo "Changing to SPEC benchmark runtime directory: $RUN_DIR" | tee -a $SCRIPT_OUT
cd $RUN_DIR
rm -rf m5out
rm -rf baseout
 
echo "" | tee -a $SCRIPT_OUT
echo "" | tee -a $SCRIPT_OUT
echo "--------- Starting gem5! ------------" | tee -a $SCRIPT_OUT
echo "" | tee -a $SCRIPT_OUT
echo "" | tee -a $SCRIPT_OUT
 

BOOM_FLAGS="--num-cpus=1 \
--bp-type=BiModeBP \
--caches \
--l2cache \
--num-l2cache=1 \
--l1i_size=32kB \
--l1i_assoc=8 \
--l1d_size=32kB \
--l1d_assoc=8 \
--l2_size=256kB \
--l2_assoc=16 \
--mem-size=8192MB \
--cpu-type=DerivO3CPU \
--scheme=unsafebaseline \
--fast-forward=10000000 \
--maxinsts=10000000"

# Actually launch gem5!
$GEM5_DIR/build/X86/gem5.opt \
--outdir=$OUTPUT_DIR \
$GEM5_DIR/configs/spec2017/se_spec2017.py \
$BOOM_FLAGS \
--benchmark=$BENCHMARK \
--benchmark_stdout=$BENCHMARK.out \
--benchmark_stderr=$BENCHMARK.err  | tee -a $SCRIPT_OUT