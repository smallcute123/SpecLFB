from gem5.utils.requires import requires
from gem5.components.boards.x86_board import X86Board
from gem5.components.memory.single_channel import SingleChannelDDR3_1600
from gem5.components.cachehierarchies.ruby.mesi_two_level_cache_hierarchy import MESITwoLevelCacheHierarchy
from gem5.components.processors.simple_switchable_processor import SimpleSwitchableProcessor
from gem5.coherence_protocol import CoherenceProtocol
from gem5.isas import ISA
from gem5.components.processors.cpu_types import CPUTypes
from gem5.resources.resource import Resource
from gem5.simulate.simulator import Simulator
from gem5.simulate.exit_event import ExitEvent
from gem5.resources.resource import  CustomDiskImageResource
requires(
    isa_required=ISA.X86,
    coherence_protocol_required=CoherenceProtocol.MESI_TWO_LEVEL,
    kvm_required=True,
)
cache_hierarchy = MESITwoLevelCacheHierarchy(
    l1d_size="32KiB",
    l1d_assoc=8,
    l1i_size="32KiB",
    l1i_assoc=8,
    l2_size="256kB",
    l2_assoc=16,
    num_l2_banks=1,
)
memory = SingleChannelDDR3_1600(size="2GiB")
processor = SimpleSwitchableProcessor(
    starting_core_type=CPUTypes.KVM,
    switch_core_type=CPUTypes.TIMING,
    num_cores=2,
)
board = X86Board(
    clk_freq="3GHz",
    processor=processor,
    memory=memory,
    cache_hierarchy=cache_hierarchy,
)
# command = "m5 exit;" \
#         + "echo 'This is running on Timing CPU cores.';" \
#         +"/home/gem5/spectre/poc;"\
#         +"echo 'spectre v1 run over:';"\
#         + "sleep 1;" \
#         + "m5 exit;"

board.set_kernel_disk_workload(
    kernel=Resource("x86-linux-kernel-5.4.49",),
     disk_image=CustomDiskImageResource("/home/admin1/CXYWORKSPACE/gem5workplace/src/npb/disk-image/npb/spectreprimex86-image/spectreprimex86","1"),
    # readfile_contents=command,
)
simulator = Simulator(
    board=board,
    on_exit_event={
        ExitEvent.EXIT : (func() for func in [processor.switch]),
    },
)
simulator.run()
