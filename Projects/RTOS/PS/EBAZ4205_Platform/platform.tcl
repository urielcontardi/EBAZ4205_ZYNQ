# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Projetos\EBAZ4205_ZYNQ\Projects\RTOS\PS\EBAZ4205_Platform\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Projetos\EBAZ4205_ZYNQ\Projects\RTOS\PS\EBAZ4205_Platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {EBAZ4205_Platform}\
-hw {D:\Projetos\EBAZ4205_ZYNQ\Projects\RTOS\PL\EBAZ4205_Top_wrapper.xsa}\
-out {D:/Projetos/EBAZ4205_ZYNQ/Projects/RTOS/PS}

platform write
domain create -name {EBAZ4205_App} -display-name {EBAZ4205_App} -os {freertos10_xilinx} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {freertos_hello_world}
platform generate -domains 
platform active {EBAZ4205_Platform}
domain active {zynq_fsbl}
domain active {EBAZ4205_App}
platform generate -quick
domain active {zynq_fsbl}
bsp reload
domain active {EBAZ4205_App}
bsp reload
domain active {zynq_fsbl}
bsp reload
domain active {EBAZ4205_App}
bsp reload
domain active {zynq_fsbl}
bsp reload
domain active {EBAZ4205_App}
bsp write
platform generate
platform config -updatehw {D:/Projetos/EBAZ4205_ZYNQ/Projects/RTOS/PL/EBAZ4205_Top_wrapper.xsa}
platform generate -domains 
