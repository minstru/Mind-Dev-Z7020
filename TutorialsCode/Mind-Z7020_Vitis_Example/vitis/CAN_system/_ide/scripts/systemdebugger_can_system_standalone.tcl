# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Mind-Z7020_Vitis_Example\vitis\CAN_system\_ide\scripts\systemdebugger_can_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\Mind-Z7020_Vitis_Example\vitis\CAN_system\_ide\scripts\systemdebugger_can_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Mind Mind7020 7E97A0002" && level==0 && jtag_device_ctx=="jsn-Mind7020-7E97A0002-23727093-0"}
fpga -file D:/Mind-Z7020_Vitis_Example/vitis/CAN/_ide/bitstream/system_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Mind-Z7020_Vitis_Example/vitis/Mind-Z7020/export/Mind-Z7020/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/Mind-Z7020_Vitis_Example/vitis/CAN/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/Mind-Z7020_Vitis_Example/vitis/CAN/Debug/CAN.elf
configparams force-mem-access 0
bpadd -addr &main
