# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\contardii\Desktop\EBAZ4205_ZYNQ\Projects\MCU_BLINKY\PS\EBAZ4205_App_system\_ide\scripts\debugger_ebaz4205_app-default_4.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\contardii\Desktop\EBAZ4205_ZYNQ\Projects\MCU_BLINKY\PS\EBAZ4205_App_system\_ide\scripts\debugger_ebaz4205_app-default_4.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-HS3 210299A57401" && level==0 && jtag_device_ctx=="jsn-JTAG-HS3-210299A57401-13722093-0"}
fpga -file C:/Users/contardii/Desktop/EBAZ4205_ZYNQ/Projects/MCU_BLINKY/PS/EBAZ4205_App/_ide/bitstream/EBAZ4205_TOP_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/contardii/Desktop/EBAZ4205_ZYNQ/Projects/MCU_BLINKY/PS/EBAZ4205_Platform/export/EBAZ4205_Platform/hw/EBAZ4205_TOP_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/contardii/Desktop/EBAZ4205_ZYNQ/Projects/MCU_BLINKY/PS/EBAZ4205_App/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/contardii/Desktop/EBAZ4205_ZYNQ/Projects/MCU_BLINKY/PS/EBAZ4205_App/Debug/EBAZ4205_App.elf
configparams force-mem-access 0
bpadd -addr &main
