# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/mind/Mind-Z7020_linux_Example/Mind-Z7020/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/mind/Mind-Z7020_linux_Example/Mind-Z7020/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Mind-Z7020}\
-hw {/home/mind/petalinux_projects/petalinux-mind/system_wrapper.xsa}\
-proc {ps7_cortexa9} -os {linux} -out {/home/mind/Mind-Z7020_linux_Example}

platform write
platform active {Mind-Z7020}
platform generate
platform active {Mind-Z7020}
platform generate -domains 
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {Mind-Z7020}
platform config -updatehw {/home/mind/petalinux_projects/petalinux-mind/system_wrapper1.xsa}
platform generate
platform generate -domains 
platform clean
platform generate
platform clean
platform clean
platform generate
platform clean
platform generate
platform generate -domains 
platform generate
platform active {Mind-Z7020}
platform config -updatehw {/home/mind/petalinux_projects/petalinux-mind/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {/home/mind/petalinux_projects/petalinux-mind/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {K:/Mind-Z7020_linux_Example/vitis/system_wrapper.xsa}
platform clean
platform config -updatehw {K:/Mind-Z7020_linux_Example/vitis/system_wrapper.xsa}
domain config -qemu-data {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_linux\qemu}
platform write
domain config -qemu-args {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_linux\qemu\qemu_args.txt}
platform write
platform generate
domain active {zynq_fsbl}
bsp reload
bsp removelib -name xilrsa
bsp write
bsp reload
catch {bsp regenerate}
bsp setlib -name xilrsa -ver 1.6
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains zynq_fsbl 
platform clean
platform active {Mind-Z7020}
platform clean
platform clean
platform clean
platform clean
platform clean
platform active {Mind-Z7020}
platform config -updatehw {K:/Mind-Z7020_linux_Example/vitis/system_wrapper.xsa}
platform generate
platform generate -domains zynq_fsbl 
platform clean
platform clean
platform generate
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform generate
platform clean
platform clean
platform clean
