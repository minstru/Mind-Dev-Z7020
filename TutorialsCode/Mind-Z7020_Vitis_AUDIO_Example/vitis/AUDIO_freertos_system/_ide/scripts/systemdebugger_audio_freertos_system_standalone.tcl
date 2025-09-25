# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\SVN\int_chenhy\Mind-Example\Mind-Z7020_Vitis_AUDIO_Example\AUDIO_TEST\vitis\AUDIO_freertos_system\_ide\scripts\systemdebugger_audio_freertos_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\SVN\int_chenhy\Mind-Example\Mind-Z7020_Vitis_AUDIO_Example\AUDIO_TEST\vitis\AUDIO_freertos_system\_ide\scripts\systemdebugger_audio_freertos_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Mind Mind7020 7E97A0002" && level==0 && jtag_device_ctx=="jsn-Mind7020-7E97A0002-23727093-0"}
fpga -file D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/vitis/AUDIO_freertos/_ide/bitstream/audio_wrapper_2.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/vitis/AUDIO_TEST/export/AUDIO_TEST/hw/audio_wrapper_2.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/vitis/AUDIO_freertos/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/vitis/AUDIO_freertos/Debug/AUDIO_freertos.elf
configparams force-mem-access 0
bpadd -addr &main
