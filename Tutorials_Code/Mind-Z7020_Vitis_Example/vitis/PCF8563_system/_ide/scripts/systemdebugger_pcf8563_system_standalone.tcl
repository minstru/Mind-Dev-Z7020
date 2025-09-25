# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Mind-Z7020_Vitis_Example\vitis\PCF8563_system\_ide\scripts\systemdebugger_pcf8563_system_standalone.tcl
# 
# 
# Usage with xsct:
# In an external shell use the below command and launch symbol server.
# symbol_server.bat -S -s tcp::1534
# To debug using xsct, launch xsct and run below command
# source D:\Mind-Z7020_Vitis_Example\vitis\PCF8563_system\_ide\scripts\systemdebugger_pcf8563_system_standalone.tcl
# 
connect -path [list tcp::1534 tcp:127.0.0.1:3121]
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Mind Mind7020 7E97A0002" && level==0 && jtag_device_ctx=="jsn-Mind7020-7E97A0002-23727093-0"}
fpga -file D:/Mind-Z7020_Vitis_Example/vitis/PCF8563/_ide/bitstream/system_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Mind-Z7020_Vitis_Example/vitis/Mind-Z7020/export/Mind-Z7020/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/Mind-Z7020_Vitis_Example/vitis/PCF8563/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/Mind-Z7020_Vitis_Example/vitis/PCF8563/Debug/PCF8563.elf
configparams force-mem-access 0
bpadd -addr &main
