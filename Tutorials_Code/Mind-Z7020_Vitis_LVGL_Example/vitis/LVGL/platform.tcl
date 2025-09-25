# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\SVN\int_chenhy\Mind-Example\Mind-Z7020_Vitis_LVGL_Example\vitis\LVGL\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\SVN\int_chenhy\Mind-Example\Mind-Z7020_Vitis_LVGL_Example\vitis\LVGL\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {LVGL}\
-hw {D:\SVN\int_chenhy\Mind-Example\Mind-Z7020_Vitis_LVGL_Example\system_wrapper_lvgl.xsa}\
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -out {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_LVGL_Example/vitis}

platform write
platform generate -domains 
platform active {LVGL}
platform generate
platform active {LVGL}
bsp reload
platform active {LVGL}
platform generate -domains 
platform generate -domains 
platform active {LVGL}
bsp reload
bsp reload
bsp config use_tick_hook "true"
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
domain active {freertos10_xilinx_domain}
bsp config tick_rate "1000"
bsp config minimal_stack_size "200"
bsp config minimal_stack_size "200"
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
bsp reload
platform generate -domains freertos10_xilinx_domain 
bsp reload
bsp config total_heap_size "655360"
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
platform generate -domains freertos10_xilinx_domain 
bsp reload
platform active {LVGL}
bsp reload
bsp write
platform clean
platform generate
platform active {LVGL}
platform generate -domains 
platform config -updatehw {D:/SVN/int_chenhy/Mind-Example/Mind-Z7020_Vitis_LVGL_Example/system_wrapper_lvgl.xsa}
platform generate -domains 
platform clean
domain remove freertos10_xilinx_domain
platform generate -domains 
platform write
platform clean
domain create -name {freertos10_xilinx_domain} -os {freertos} -proc {ps7_cortexa9_0} -arch {32-bit} -display-name {freertos10_xilinx_domain} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
bsp reload
bsp config use_tick_hook "false"
bsp config use_malloc_failed_hook "true"
bsp config use_tick_hook "true"
bsp config minimal_stack_size "200"
bsp config tick_rate "1000"
bsp config total_heap_size "655360"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform clean
platform clean
platform generate
platform clean
platform generate
platform clean
platform clean
platform generate
platform clean
platform generate
platform clean
platform active {LVGL}
platform generate
bsp reload
platform clean
platform generate
platform clean
platform generate
bsp reload
bsp config total_heap_size "65536"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_domain 
platform clean
platform generate
platform clean
platform clean
platform generate
platform clean
platform clean
platform generate
platform clean
platform generate
platform clean
platform clean
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform active {LVGL}
domain remove freertos10_xilinx_domain
platform generate -domains 
platform write
platform clean
domain create -name {freertos10_xilinx_domain} -os {freertos} -proc {ps7_cortexa9_0} -arch {32-bit} -display-name {freertos10_xilinx_domain} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
platform generate
platform active {LVGL}
platform generate -domains 
platform clean
platform generate
platform clean
platform active {LVGL}
platform generate
platform active {LVGL}
platform generate -domains 
bsp reload
platform clean
platform clean
platform generate
platform active {LVGL}
bsp reload
bsp config use_tick_hook "true"
bsp config tick_rate "1000"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_domain 
platform active {LVGL}
bsp reload
platform generate -domains 
platform clean
platform generate
platform generate
platform generate
platform active {LVGL}
bsp reload
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp reload
platform config -updatehw {K:/Mind-Z7020_Vitis_LVGL_Example/vitis/system_wrapper_lvgl.xsa}
domain active {freertos10_xilinx_domain}
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
bsp setlib -name xilrsa -ver 1.6
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform clean
platform generate
platform clean
platform config -updatehw {K:/Mind-Z7020_Vitis_LVGL_Example/vitis/system_wrapper.xsa}
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform clean
