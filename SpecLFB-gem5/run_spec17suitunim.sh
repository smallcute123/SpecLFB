#!/bin/bash
GEM5_DIR=/home/chengxiaoyu/SCSGuardian/gem5 
# int_rate=(perlbench_r gcc_r  omnetpp_r xalancbmk_r x264_r deepsjeng_r leela_r exchange2_r xz_r)
# frate=(bwaves_r cactuBSSN_r namd_r parest_r povray_r lbm_r wrf_r blender_r cam4_r imagick_r nab_r fotonik3d_r roms_r)
int_rate=(perlbench_r gcc_r  omnetpp_r xalancbmk_r x264_r deepsjeng_r leela_r exchange2_r xz_r)
frate=(cam4_r imagick_r nab_r fotonik3d_r)
int_rate1000=(mcf_r)

for i in "${!int_rate1000[@]}"  
do 
cd $GEM5_DIR 
source ./run_spec17_mcf.sh "${int_rate1000[$i]}" m5out 
done


# perlbench_r  mcf_r  x264_r deepsjeng_r leela_r exchange2_r gcc_r omnetpp_r xalancbmk_r xz_r parest_r lbm_r cam4_r roms_r
#  gcc_r omnetpp_r xalancbmk_r xz_r parest_r lbm_r cam4_r roms_r
# lbm_r