# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Mind-Z7020_Vitis_Example\vitis\Mind-Z7020\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Mind-Z7020_Vitis_Example\vitis\Mind-Z7020\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Mind-Z7020}\
-hw {D:\Mind-Z7020_Vitis_Example\system_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {D:/Mind-Z7020_Vitis_Example/vitis}

platform write
platform generate -domains 
platform active {Mind-Z7020}
platform generate
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
bsp reload
bsp reload
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp setlib -name xilffs -ver 4.5
bsp setlib -name xilrsa -ver 1.6
bsp removelib -name xilrsa
bsp write
bsp reload
catch {bsp regenerate}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp reload
platform active {Mind-Z7020}
bsp reload
bsp removelib -name lwip211
bsp removelib -name xilffs
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
bsp removelib -name lwip211
bsp write
bsp reload
catch {bsp regenerate}
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
domain active {zynq_fsbl}
bsp reload
bsp reload
domain active {standalone_domain}
bsp reload
bsp removelib -name lwip211
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
domain active {zynq_fsbl}
bsp write
domain active {standalone_domain}
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
domain active {zynq_fsbl}
bsp reload
bsp write
domain active {standalone_domain}
bsp reload
bsp setlib -name xilrsa -ver 1.6
bsp removelib -name xilrsa
bsp write
domain active {zynq_fsbl}
bsp config stdin "ps7_uart_0"
bsp reload
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
domain active {standalone_domain}
bsp reload
bsp write
domain active {zynq_fsbl}
bsp reload
bsp write
domain active {standalone_domain}
bsp removelib -name lwip211
bsp write
bsp reload
catch {bsp regenerate}
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
bsp write
domain active {zynq_fsbl}
bsp write
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
domain active {standalone_domain}
bsp reload
bsp write
domain active {zynq_fsbl}
bsp reload
bsp write
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
domain active {standalone_domain}
bsp reload
bsp removelib -name lwip211
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
bsp write
platform generate -domains standalone_domain 
domain active {standalone_domain}
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains standalone_domain 
bsp reload
bsp reload
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
platform generate -domains 
domain active {zynq_fsbl}
bsp reload
platform active {Mind-Z7020}
bsp reload
bsp reload
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp reload
platform generate -domains 
domain active {zynq_fsbl}
bsp reload
bsp reload
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
domain active {standalone_domain}
bsp reload
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp config stdin "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains zynq_fsbl 
domain active {standalone_domain}
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp config stdin "ps7_uart_0"
bsp config stdout "ps7_uart_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain,zynq_fsbl 
domain active {standalone_domain}
bsp config stdin "ps7_uart_0"
bsp config stdout "ps7_uart_0"
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain,zynq_fsbl 
bsp config stdin "ps7_uart_0"
bsp config stdout "ps7_uart_0"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains standalone_domain,zynq_fsbl 
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp reload
platform generate -domains 
bsp setlib -name xilffs -ver 4.5
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
platform active {Mind-Z7020}
platform generate -domains 
platform active {Mind-Z7020}
platform generate -domains 
bsp reload
bsp config lwip_dhcp "true"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
platform active {Mind-Z7020}
bsp reload
bsp config lwip_dhcp "false"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/7020test/design_1_wrapper.xsa}
bsp reload
bsp reload
platform active {Mind-Z7020}
bsp reload
bsp setlib -name xilrsa -ver 1.6
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
bsp reload
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate
platform active {Mind-Z7020}
bsp reload
bsp reload
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
bsp reload
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/vitis/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/vitis/system_wrapper.xsa}
platform generate -domains 
bsp reload
bsp config stdin "ps7_uart_0"
bsp config stdout "ps7_uart_0"
bsp write
bsp reload
catch {bsp regenerate}
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/vitis/system_wrapper.xsa}
bsp reload
bsp reload
platform generate -domains standalone_domain 
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp removelib -name lwip211
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp removelib -name lwip211
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp reload
bsp removelib -name xilffs
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp removelib -name xilffs
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp write
bsp setlib -name xilffs -ver 4.5
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp setlib -name xilffs -ver 4.5
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform clean
platform generate
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
bsp reload
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform generate
platform active {Mind-Z7020}
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
bsp reload
bsp config stdin "ps7_uart_0"
bsp config ttc_select_cntr "2"
bsp config stdout "ps7_uart_0"
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
platform generate -domains standalone_domain 
platform active {Mind-Z7020}
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp reload
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
bsp reload
bsp config api_mode "RAW_API"
bsp config lwip_tcp_keepalive "false"
bsp config lwip_dhcp "false"
bsp reload
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp reload
platform generate -domains 
bsp reload
bsp reload
bsp reload
bsp config use_emaclite_on_zynq "1"
bsp reload
bsp reload
platform active {Mind-Z7020}
platform generate -domains 
bsp reload
bsp config lwip_dhcp "true"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
bsp reload
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
bsp reload
bsp reload
platform active {Mind-Z7020}
platform generate -domains 
platform generate
platform active {Mind-Z7020}
platform generate -domains 
bsp reload
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
bsp reload
platform active {Mind-Z7020}
bsp reload
bsp reload
platform generate -domains 
bsp reload
bsp reload
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp config stdin "ps7_uart_0"
bsp config stdout "ps7_uart_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
bsp reload
bsp reload
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp reload
platform active {Mind-Z7020}
bsp reload
bsp reload
platform active {Mind-Z7020}
bsp reload
bsp removelib -name lwip211
bsp write
bsp reload
catch {bsp regenerate}
bsp setlib -name lwip211 -ver 1.5
bsp reload
bsp reload
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
platform active {Mind-Z7020}
bsp reload
bsp config gmii2rgmii_core_address_on_eth1 "1"
bsp config use_gmii2rgmii_core_on_eth1 "false"
bsp config gmii2rgmii_core_address_on_eth1 "8"
bsp config use_gmii2rgmii_core_on_eth1 "true"
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
bsp setlib -name lwip211 -ver 1.5
bsp reload
platform generate
platform active {Mind-Z7020}
domain active {standalone_domain}
bsp reload
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp setlib -name lwip211 -ver 1.5
bsp reload
platform generate -domains 
domain active {standalone_domain}
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
bsp config stdin "ps7_uart_0"
bsp config stdout "ps7_uart_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
platform clean
platform generate
platform active {Mind-Z7020}
platform generate -domains 
platform clean
platform generate
bsp reload
bsp reload
platform active {Mind-Z7020}
platform active {Mind-Z7020}
domain create -name {freertos10_xilinx_ps7_cortexa9_0} -os {freertos} -proc {ps7_cortexa9_0} -arch {32-bit} -display-name {freertos10_xilinx_ps7_cortexa9_0} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
catch {platform remove system_wrapper}
platform active {Mind-Z7020}
platform active {Mind-Z7020}
domain active {standalone_domain}
bsp reload
bsp reload
bsp reload
platform generate
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate
bsp reload
bsp reload
bsp reload
platform generate
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
bsp reload
bsp reload
platform generate -domains 
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform generate -domains freertos10_xilinx_ps7_cortexa9_0,standalone_domain 
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform generate -domains 
platform generate
platform generate
platform active {Mind-Z7020}
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
platform generate -domains 
platform clean
domain remove freertos10_xilinx_ps7_cortexa9_0
platform generate -domains 
platform write
domain create -name {freertos10_xilinx_ps7_cortexa9_0} -os {freertos} -proc {ps7_cortexa9_0} -arch {32-bit} -display-name {freertos10_xilinx_ps7_cortexa9_0} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
domain active {standalone_domain}
bsp reload
domain active {freertos10_xilinx_ps7_cortexa9_0}
bsp reload
bsp reload
platform clean
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
domain remove standalone_domain
platform generate -domains 
platform write
domain create -name {standalone_domain} -os {standalone} -proc {ps7_cortexa9_0} -arch {32-bit} -display-name {standalone on ps7_cortexa9_0} -desc {} -runtime {cpp}
platform generate -domains 
domain -report -json
platform write
platform config -updatehw {D:/Mind-Z7020_Vitis_Example/system_wrapper.xsa}
bsp reload
bsp setlib -name xilffs -ver 4.5
bsp setlib -name lwip211 -ver 1.5
bsp write
bsp reload
catch {bsp regenerate}
domain active {freertos10_xilinx_ps7_cortexa9_0}
bsp reload
domain active {standalone_domain}
bsp config gmii2rgmii_core_address_on_eth1 "8"
bsp config use_gmii2rgmii_core_on_eth1 "true"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
catch {platform remove HDMI_Standalone}
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
platform active {Mind-Z7020}
platform config -updatehw {K:/Mind-Z7020_Vitis_Example/vitis/system_wrapper.xsa}
platform clean
platform config -updatehw {K:/Mind-Z7020_Vitis_Example/vitis/system_wrapper.xsa}
domain active {zynq_fsbl}
bsp reload
domain active {freertos10_xilinx_ps7_cortexa9_0}
bsp reload
domain active {standalone_domain}
domain config -qemu-data {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu}
platform write
domain config -qemu-args {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu\qemu_args.txt}
platform write
domain active {freertos10_xilinx_ps7_cortexa9_0}
domain config -qemu-data {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu}
platform write
domain config -qemu-args {C:\Xilinx2021\Vitis\2021.1\data\emulation\platforms\zynq\sw\a9_standalone\qemu\qemu_args.txt}
platform write
platform config -updatehw {K:/Mind-Z7020_Vitis_Example/vitis/system_wrapper.xsa}
domain active {standalone_domain}
bsp reload
bsp setlib -name xilrsa -ver 1.6
bsp write
bsp reload
catch {bsp regenerate}
domain active {freertos10_xilinx_ps7_cortexa9_0}
bsp reload
bsp reload
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp reload
bsp reload
domain active {freertos10_xilinx_ps7_cortexa9_0}
bsp setlib -name xilrsa -ver 1.6
bsp setlib -name xilffs -ver 4.5
bsp reload
domain active {standalone_domain}
bsp reload
platform clean
bsp reload
bsp write
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp removelib -name xilrsa
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp removelib -name xilrsa
bsp write
bsp reload
catch {bsp regenerate}
domain active {freertos10_xilinx_ps7_cortexa9_0}
bsp reload
platform clean
domain active {standalone_domain}
bsp setlib -name xilrsa -ver 1.6
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp setlib -name xilrsa -ver 1.6
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform active {Mind-Z7020}
platform generate -domains 
platform clean
platform generate
platform clean
platform generate
platform active {Mind-Z7020}
platform clean
platform clean
platform clean
domain active {standalone_domain}
bsp reload
bsp reload
platform active {Mind-Z7020}
domain active {standalone_domain}
bsp reload
bsp write
platform generate
bsp config gmii2rgmii_core_address_on_eth1 "7"
bsp write
bsp reload
catch {bsp regenerate}
bsp config gmii2rgmii_core_address_on_eth1 "8"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain 
platform clean
platform generate
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform clean
platform generate
platform clean
