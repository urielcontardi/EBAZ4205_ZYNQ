# This file is automatically generated.
# It contains project source information necessary for synthesis and implementation.

# XDC: C:/Users/contardii/Desktop/EBAZ4205_ZYNQ/Projects/Blinky/Vivado/constraints/EBAZ4205_Top.xdc

# Block Designs: bd/EBAZ4205_TOP/EBAZ4205_TOP.bd
set_property KEEP_HIERARCHY SOFT [get_cells -hier -filter {REF_NAME==EBAZ4205_TOP || ORIG_REF_NAME==EBAZ4205_TOP} -quiet] -quiet

# IP: bd/EBAZ4205_TOP/ip/EBAZ4205_TOP_processing_system7_0_0/EBAZ4205_TOP_processing_system7_0_0.xci
set_property KEEP_HIERARCHY SOFT [get_cells -hier -filter {REF_NAME==EBAZ4205_TOP_processing_system7_0_0 || ORIG_REF_NAME==EBAZ4205_TOP_processing_system7_0_0} -quiet] -quiet

# IP: bd/EBAZ4205_TOP/ip/EBAZ4205_TOP_blinky_0_0/EBAZ4205_TOP_blinky_0_0.xci
set_property KEEP_HIERARCHY SOFT [get_cells -hier -filter {REF_NAME==EBAZ4205_TOP_blinky_0_0 || ORIG_REF_NAME==EBAZ4205_TOP_blinky_0_0} -quiet] -quiet

# XDC: c:/Users/contardii/Desktop/EBAZ4205_ZYNQ/Projects/Blinky/Vivado/MCU_BLINKY.gen/sources_1/bd/EBAZ4205_TOP/ip/EBAZ4205_TOP_processing_system7_0_0/EBAZ4205_TOP_processing_system7_0_0.xdc
set_property KEEP_HIERARCHY SOFT [get_cells [split [join [get_cells -hier -filter {REF_NAME==EBAZ4205_TOP_processing_system7_0_0 || ORIG_REF_NAME==EBAZ4205_TOP_processing_system7_0_0} -quiet] {/inst } ]/inst ] -quiet] -quiet

# XDC: c:/Users/contardii/Desktop/EBAZ4205_ZYNQ/Projects/Blinky/Vivado/MCU_BLINKY.gen/sources_1/bd/EBAZ4205_TOP/EBAZ4205_TOP_ooc.xdc