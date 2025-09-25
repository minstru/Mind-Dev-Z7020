# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\SVN\int_chenhy\Mind-Example\Mind-Z7020_Vitis_AUDIO_Example\AUDIO_TEST\vitis\AUDIO_TEST\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\SVN\int_chenhy\Mind-Example\Mind-Z7020_Vitis_AUDIO_Example\AUDIO_TEST\vitis\AUDIO_TEST\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {AUDIO_TEST}\
-hw {D:\SVN\int_chenhy\Mind-Example\Mind-Z7020_Vitis_AUDIO_Example\AUDIO_TEST\audio_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/vitis}

platform write
platform generate -domains 
platform active {AUDIO_TEST}
platform generate
platform active {AUDIO_TEST}
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper_2.xsa}
platform generate -domains 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper_2.xsa}
platform generate -domains 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper_2.xsa}
platform generate -domains 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper_2.xsa}
platform generate -domains 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper2_1.xsa}
platform generate -domains 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper2_1.xsa}
platform generate -domains 
platform active {AUDIO_TEST}
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper2_1.xsa}
platform generate -domains 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper3.xsa}
platform generate -domains 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper3.xsa}
platform generate -domains 
platform clean
platform generate
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper_2.xsa}
platform generate -domains 
platform active {AUDIO_TEST}
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper_2.xsa}
platform generate -domains standalone_domain,zynq_fsbl 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper_2.xsa}
platform generate -domains 
domain create -name {freertos_xilinx_ps7} -os {freertos} -proc {ps7_cortexa9_0} -arch {32-bit} -display-name {freertos_xilinx_ps7} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_AUDIO_Example/AUDIO_TEST/audio_wrapper_2.xsa}
platform generate -domains freertos_xilinx_ps7 
domain active {standalone_domain}
domain active {freertos_xilinx_ps7}
domain active {zynq_fsbl}
domain active {standalone_domain}
platform active {AUDIO_TEST}
platform generate -domains 
platform generate -domains 
platform generate
platform generate
platform active {AUDIO_TEST}
platform config -updatehw {K:/Mind-Z7020_Vitis_AUDIO_Example/vitis/audio_wrapper.xsa}
bsp reload
domain config -qemu-data {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu}
platform write
domain config -qemu-args {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu\qemu_args.txt}
platform write
domain active {standalone_domain}
domain config -qemu-data {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu}
platform write
domain config -qemu-args {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu\qemu_args.txt}
platform write
domain active {zynq_fsbl}
bsp reload
bsp removelib -name xilrsa
bsp write
bsp reload
catch {bsp regenerate}
domain active {freertos_xilinx_ps7}
bsp reload
domain active {standalone_domain}
bsp reload
bsp reload
domain active {zynq_fsbl}
bsp setlib -name xilrsa -ver 1.6
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform clean
platform generate
platform clean
