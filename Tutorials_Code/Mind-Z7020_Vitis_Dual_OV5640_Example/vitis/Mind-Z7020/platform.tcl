# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct F:\temp\int_chenhy\ZynqCoreTest\10_PS_EMIO_NET_TEST\NET_TEST\vitis_ov5460\Mind-Z7020\platform.tcl
# 
# OR launch xsct and run below command.
# source F:\temp\int_chenhy\ZynqCoreTest\10_PS_EMIO_NET_TEST\NET_TEST\vitis_ov5460\Mind-Z7020\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Mind-Z7020}\
-hw {F:\temp\int_chenhy\ZynqCoreTest\10_PS_EMIO_NET_TEST\NET_TEST\vitis_ov5460\system_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460}

platform write
platform generate -domains 
platform active {Mind-Z7020}
platform generate
platform config -updatehw {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
bsp reload
platform active {Mind-Z7020}
platform active {Mind-Z7020}
platform config -updatehw {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460_hdmi/system_wrapper.xsa}
platform generate
platform clean
platform generate
platform generate
platform clean
platform generate
platform generate
platform config -updatehw {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460_hdmi/system_wrapper.xsa}
platform clean
platform generate
platform active {Mind-Z7020}
platform config -updatehw {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460_hdmi/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460_hdmi/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
bsp reload
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460_hdmi/system_wrapper.xsa}
platform generate
platform config -updatehw {F:/temp/int_chenhy/ZynqCoreTest/10_PS_EMIO_NET_TEST/NET_TEST/vitis_ov5460_hdmi/system_wrapper.xsa}
platform generate -domains 
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_Dual_OV5640_Example/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
bsp reload
platform generate -domains 
platform active {Mind-Z7020}
platform active {Mind-Z7020}
platform generate
platform generate
platform active {Mind-Z7020}
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_Dual_OV5640_Example/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_Dual_OV5640_Example/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_Dual_OV5640_Example/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_Dual_OV5640_Example/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {K:/Mind-Z7020_Vitis_Dual_OV5640_Example/vitis/system_wrapper.xsa}
platform clean
platform clean
domain config -qemu-data {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu}
platform write
domain config -qemu-args {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu\qemu_args.txt}
platform write
platform clean
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
domain active {standalone_domain}
bsp reload
bsp reload
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
