# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\contardii\Desktop\EBAZ4205_ZYNQ\Projects\Interrupt\PS\EBAZ4205_Platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\contardii\Desktop\EBAZ4205_ZYNQ\Projects\Interrupt\PS\EBAZ4205_Platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {EBAZ4205_Platform}\
-hw {C:\Users\contardii\Desktop\EBAZ4205_ZYNQ\Projects\Interrupt\PL\EBAZ4205_Top_wrapper.xsa}\
-out {C:/Users/contardii/Desktop/EBAZ4205_ZYNQ/Projects/Interrupt/PS}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {EBAZ4205_Platform}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
