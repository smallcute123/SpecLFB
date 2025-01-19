#!/bin/bash
GEM5_DIR=/home/chengxiaoyu/SpecLFB/SpecLFB-gem5
# int_rate=(perlbench_r gcc_r  omnetpp_r xalancbmk_r x264_r deepsjeng_r leela_r exchange2_r xz_r)
# frate=(bwaves_r cactuBSSN_r namd_r parest_r povray_r lbm_r wrf_r blender_r cam4_r imagick_r nab_r fotonik3d_r roms_r)
int_rate100=( gcc_r omnetpp_r xalancbmk_r xz_r)
frate1000=(bwaves_r cactuBSSN_r namd_r povray_r wrf_r blender_r imagick_r nab_r fotonik3d_r)
int_rate1000=(perlbench_r mcf_r x264_r deepsjeng_r leela_r exchange2_r)
frate100=(parest_r cam4_r)
for i in "${!int_rate100[@]}"  
do 
cd $GEM5_DIR
source ./run_spec17.sh "${int_rate100[$i]}" m5out 
done

for i in "${!frate1000[@]}"  
do 
cd $GEM5_DIR 
source ./run_spec17_mcf.sh "${frate1000[$i]}" m5out 
done

for i in "${!int_rate1000[@]}"  
do 
cd $GEM5_DIR 
source ./run_spec17_mcf.sh "${int_rate1000[$i]}" m5out 
done

for i in "${!frate100[@]}"  
do 
cd $GEM5_DIR 
source ./run_spec17.sh "${frate100[$i]}" m5out 
done

# perlbench_r  mcf_r  x264_r deepsjeng_r leela_r exchange2_r gcc_r omnetpp_r xalancbmk_r xz_r parest_r lbm_r cam4_r roms_r
#  gcc_r omnetpp_r xalancbmk_r xz_r parest_r lbm_r cam4_r roms_r