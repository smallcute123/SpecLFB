import m5
from m5.objects import *

riscv_suffix = '_base.x86-m64'
#500.perlbench_r 
perlbench_r = Process(pid = 500) 
perlbench_r.executable = 'perlbench_r'+ riscv_suffix
data = 'checkspam.pl'
perlbench_r.cmd = [perlbench_r.executable] + ['-I./lib',data,'2500','5','25','11','150','1','1','1','1']

#600.perlbench_s 
perlbench_s = Process(pid = 600)
perlbench_s.executable = 'perlbench_s'+ riscv_suffix
data = 'checkspam.pl'
perlbench_s.cmd = [perlbench_s.executable] + ['-I./lib',data,'2500','5','25','11','150','1','1','1','1']

#502.gcc_r 
gcc_r = Process(pid = 502)
gcc_r.executable =  'cpugcc_r'+ riscv_suffix
gcc_r.cmd = [gcc_r.executable] + ['gcc-pp.c','-O3','-finline-limit=0','-fif-conversion','-fif-conversion2','-o','gcc-pp.opts-O3_-finline-limit_0_-fif-conversion_-fif-conversion2.s']

#602.gcc_s 
gcc_s = Process(pid = 602)
gcc_s.executable =  'sgcc'+ riscv_suffix
gcc_s.cmd = [gcc_s.executable] + ['gcc-pp.c','-O5','-fipa-pta','-o','gcc-pp.opts-O5_-fipa-pta.s']

#505.mcf_r
mcf_r = Process(pid = 505) 
mcf_r.executable = 'mcf_r' + riscv_suffix
data = 'inp.in'
mcf_r.cmd = [mcf_r.executable] + [data]

#605.mcf_s 
mcf_s = Process(pid = 605) 
mcf_s.executable = 'mcf_s' + riscv_suffix
data = 'inp.in'
mcf_s.cmd = [mcf_s.executable] + [data]

#520.omnetpp_r 
omnetpp_r = Process(pid = 520) 
omnetpp_r.executable = 'omnetpp_r' + riscv_suffix
# omnetpp_r.cmd = [omnetpp_r.executable]+['-c General','-r 0']
omnetpp_r.cmd = [omnetpp_r.executable]+['-c', 'General', '-r', '0']

#620.omnetpp_s 
omnetpp_s = Process(pid = 620) 
omnetpp_s.executable = 'omnetpp_s' + riscv_suffix
# omnetpp_s.cmd = [omnetpp_s.executable]+['-c General','-r 0']
omnetpp_s.cmd = [omnetpp_s.executable]+['-c', 'General', '-r', '0']

#523.xalancbmk_r  
xalancbmk_r = Process(pid = 523) 
xalancbmk_r.executable =  'cpuxalan_r' + riscv_suffix
xalancbmk_r.cmd = [xalancbmk_r.executable] + ['-v','t5.xml','xalanc.xsl']

#623.xalancbmk_s  
xalancbmk_s = Process(pid = 623) 
xalancbmk_s.executable = 'xalancbmk_s' + riscv_suffix
xalancbmk_s.cmd = [xalancbmk_s.executable] + ['-v','t5.xml','xalanc.xsl']

#525.x264_r   
x264_r = Process(pid = 525) 
x264_r.executable = 'x264_r' + riscv_suffix
x264_r.cmd = [x264_r.executable] + ['--pass','1','--stats','x264_stats.log','--bitrate','1000','--frames','1000','-o','BuckBunny_New.264','BuckBunny.yuv','1280x720']

#625.x264_s   
x264_s = Process(pid = 625) 
x264_s.executable = 'x264_s' + riscv_suffix
x264_s.cmd = [x264_s.executable] + ['--pass','1','--stats','x264_stats.log','--bitrate','1000','--frames','1000','-o','BuckBunny_New.264','BuckBunny.yuv','1280x720']

#531.deepsjeng_r 
deepsjeng_r = Process(pid = 531) 
deepsjeng_r.executable = 'deepsjeng_r' + riscv_suffix
deepsjeng_r.cmd = [deepsjeng_r.executable] + ['ref.txt']

#631.deepsjeng_s  
deepsjeng_s = Process(pid = 631) 
deepsjeng_s.executable = 'deepsjeng_s' + riscv_suffix
deepsjeng_s.cmd = [deepsjeng_s.executable] + ['ref.txt']

#541.leela_r  
leela_r = Process(pid = 541) 
leela_r.executable = 'leela_r' + riscv_suffix
data = 'ref.sgf'
leela_r.cmd = [leela_r.executable] + [data]

#641.leela_s  
leela_s = Process(pid = 641) 
leela_s.executable = 'leela_s' + riscv_suffix
data = 'ref.sgf'
leela_s.cmd = [leela_s.executable] + [data]

#548.exchange2_r    
exchange2_r = Process(pid = 548) 
exchange2_r.executable = 'exchange2_r' + riscv_suffix
exchange2_r.cmd = [exchange2_r.executable] + ['6']

#648.exchange2_s   
exchange2_s = Process(pid = 648) 
exchange2_s.executable = 'exchange2_s' + riscv_suffix
exchange2_s.cmd = [exchange2_s.executable] + ['6']

#557.xz_r   
xz_r = Process(pid = 557) 
xz_r.executable = 'xz_r' + riscv_suffix
xz_r.cmd = [xz_r.executable] + ['cld.tar.xz','160','19cf30ae51eddcbefda78dd06014b4b96281456e078ca7c13e1c0c9e6aaea8dff3efb4ad6b0456697718cede6bd5454852652806a657bb56e07d61128434b474','59796407','61004416','6']

#657.xz_s   
xz_s = Process(pid = 657) 
xz_s.executable = 'xz_s' + riscv_suffix
xz_s.cmd = [xz_s.executable] + ['cpu2006docs.tar.xz','6643','055ce243071129412e9dd0b3b69a21654033a9b723d874b2015c774fac1553d9713be561ca86f74e4f16f22e664fc17a79f30caa5ad2c04fbc447549c2810fae','1036078272','1111795472','4']

#998.specrand_is    
specrand_is = Process(pid = 998) 
specrand_is.executable = 'specrand_is' + riscv_suffix
specrand_is.cmd = [specrand_is.executable] + ['324342', '24239']

#999.specrand_ir    
specrand_ir = Process(pid = 999) 
specrand_ir.executable = 'specrand_ir' + riscv_suffix
specrand_ir.cmd = [specrand_ir.executable] + ['324342', '24239']

#503.bwaves_r    
bwaves_r = Process(pid = 503) 
bwaves_r.executable = 'bwaves_r' + riscv_suffix
bwaves_r.cmd = [bwaves_r.executable] + ['bwaves_3']
bwaves_r.input = 'bwaves_3.in'

#603.bwaves_s    
bwaves_s = Process(pid = 603) 
bwaves_s.executable = 'speed_bwaves' + riscv_suffix
bwaves_s.cmd = [bwaves_s.executable] + ['bwaves_1']
bwaves_s.input = 'bwaves_1.in'

#507.cactuBSSN_r   
cactuBSSN_r = Process(pid = 507) 
cactuBSSN_r.executable = 'cactusBSSN_r' + riscv_suffix
data = 'spec_ref.par'
cactuBSSN_r.cmd = [cactuBSSN_r.executable] + [data]

#607.cactuBSSN_s   
cactuBSSN_s = Process(pid = 607) 
cactuBSSN_s.executable = 'cactuBSSN_s' + riscv_suffix
data = 'spec_ref.par'
cactuBSSN_s.cmd = [cactuBSSN_s.executable] + [data]

#508.namd_r    
namd_r = Process(pid = 508) 
namd_r.executable = 'namd_r' + riscv_suffix
namd_r.cmd = [namd_r.executable] + ['--input','apoa1.input','--output','apoa1.ref.output','--iterations','65'] 

#510.parest_r    
parest_r = Process(pid = 510) 
parest_r.executable = 'parest_r' + riscv_suffix
data = 'ref.prm'
parest_r.cmd = [parest_r.executable] + [data]

#511.povray_r    
povray_r = Process(pid = 511) 
povray_r.executable = 'povray_r' + riscv_suffix
data = 'SPEC-benchmark-ref.ini'
povray_r.cmd = [povray_r.executable] + [data]

#519.lbm_r   
lbm_r = Process(pid = 519) 
lbm_r.executable = 'lbm_r' + riscv_suffix
lbm_r.cmd = [lbm_r.executable] + ['3000','reference.dat','0','0','100_100_130_ldc.of']

#619.lbm_s     
lbm_s = Process(pid = 619) 
lbm_s.executable = 'lbm_s' + riscv_suffix
lbm_s.cmd = [lbm_s.executable] + ['2000','reference.dat','0','0','200_200_260_ldc.of']

#521.wrf_r     
wrf_r = Process(pid = 521) 
wrf_r.executable = 'wrf_r' + riscv_suffix
wrf_r.cmd = [wrf_r.executable]

#621.wrf_s      
wrf_s = Process(pid = 621) 
wrf_s.executable = 'wrf_s' + riscv_suffix
wrf_s.cmd = [wrf_s.executable]

#526.blender_r   
blender_r = Process(pid = 526) 
blender_r.executable = 'blender_r' + riscv_suffix
blender_r.cmd = [blender_r.executable] + ['sh3_no_char.blend','--render-output','sh3_no_char_','--threads','1','-b','-F','RAWTGA','-s','849','-e','849','-a']

#527.cam4_r      
cam4_r = Process(pid = 527) 
cam4_r.executable = 'cam4_r' + riscv_suffix
cam4_r.cmd = [cam4_r.executable]

#627.cam4_s     
cam4_s = Process(pid = 627) 
cam4_s.executable = 'cam4_s' + riscv_suffix
cam4_s.cmd = [cam4_s.executable]

#628.pop2_s       
pop2_s = Process(pid = 628) 
pop2_s.executable = 'speed_pop2' + riscv_suffix
pop2_s.cmd = [pop2_s.executable]

#538.imagick_r    
imagick_r = Process(pid = 538) 
imagick_r.executable = 'imagick_r' + riscv_suffix
imagick_r.cmd = [imagick_r.executable] + ['-limit','disk','0','refrate_input.tga','-edge','41','-resample','181%','-emboss','31','-colorspace','YUV','-mean-shift','19x19+15%','-resize','30%','refrate_output.tga']

#638.imagick_s    
imagick_s = Process(pid = 638) 
imagick_s.executable = 'imagick_s' + riscv_suffix
imagick_s.cmd = [imagick_s.executable] + ['-limit','disk','0','refspeed_input.tga','-resize','817%','-rotate','-2.76','-shave','540x375','-alpha','remove','-auto-level','-contrast-stretch','1x1%','-colorspace','Lab','-channel','R','-equalize','+channel','-colorspace','sRGB','-define','histogram:unique-colors=false','-adaptiveblur','0x5','-despeckle','-auto-gamma','-adaptive-sharpen','55','-enhance','-brightness-contrast','10x10','-resize','30%','refspeed_output.tga']

#544.nab_r     
nab_r = Process(pid = 544) 
nab_r.executable = 'nab_r' + riscv_suffix
nab_r.cmd = [nab_r.executable] + ['1am0','1122214447','122']

#644.nab_s     
nab_s = Process(pid = 644) 
nab_s.executable = 'nab_s' + riscv_suffix
nab_s.cmd = [nab_s.executable] + ['3j1n','20140317','220']

#549.fotonik3d_r       
fotonik3d_r = Process(pid = 549) 
fotonik3d_r.executable = 'fotonik3d_r' + riscv_suffix
fotonik3d_r.cmd = [fotonik3d_r.executable]

#649.fotonik3d_s       
fotonik3d_s = Process(pid = 649) 
fotonik3d_s.executable = 'fotonik3d_s' + riscv_suffix
fotonik3d_s.cmd = [fotonik3d_s.executable]

#554.roms_r     
roms_r = Process(pid = 554) 
roms_r.executable = 'roms_r' + riscv_suffix
roms_r.cmd = [roms_r.executable]
roms_r.input = 'ocean_benchmark2.in.x'

#654.roms_s     
roms_s = Process(pid = 654) 
roms_s.executable = 'sroms' + riscv_suffix
roms_s.cmd = [roms_s.executable]
roms_s.input = 'ocean_benchmark3.in.x'

#996.specrand_fs      
specrand_fs = Process(pid = 996) 
specrand_fs.executable = 'specrand_fs' + riscv_suffix
# specrand_fs.cmd = [specrand_fs.executable] + ['324342 24239']
specrand_fs.cmd = [specrand_fs.executable] + ['324342', '24239']

#997.specrand_fr       
specrand_fr = Process(pid = 997) 
specrand_fr.executable = 'specrand_fr' + riscv_suffix
# specrand_fr.cmd = [specrand_fr.executable] + ['324342 24239']
specrand_fr.cmd = [specrand_fr.executable] + ['324342', '24239']