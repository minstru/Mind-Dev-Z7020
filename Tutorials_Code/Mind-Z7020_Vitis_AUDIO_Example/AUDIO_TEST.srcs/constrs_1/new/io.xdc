create_clock -period 20.000 -name sys_clksys_clk

set_property -dict {PACKAGE_PIN L19 IOSTANDARD LVCMOS33} [get_ports aud_iic_scl_io]
set_property -dict {PACKAGE_PIN L20 IOSTANDARD LVCMOS33} [get_ports aud_iic_sda_io]
set_property -dict {PACKAGE_PIN K19 IOSTANDARD LVCMOS33} [get_ports aud_adc_data]
set_property -dict {PACKAGE_PIN G17 IOSTANDARD LVCMOS33} [get_ports aud_dac_data]
set_property -dict {PACKAGE_PIN H18 IOSTANDARD LVCMOS33} [get_ports aud_bclk]
set_property -dict {PACKAGE_PIN J18 IOSTANDARD LVCMOS33} [get_ports aud_mclk]
#set_property -dict {PACKAGE_PIN K17 IOSTANDARD LVCMOS33} [get_ports sys_clk]

set_property PACKAGE_PIN J19 [get_ports aud_adc_lrc]
set_property IOSTANDARD LVCMOS33 [get_ports aud_adc_lrc]
set_property PACKAGE_PIN G18 [get_ports aud_dac_lrc]
set_property IOSTANDARD LVCMOS33 [get_ports aud_dac_lrc]

set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[1]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[0]}]
#set_property PACKAGE_PIN J18 [get_ports {GPIO_0_0_tri_io[0]}]

set_property PACKAGE_PIN D19 [get_ports {GPIO_0_0_tri_io[0]}]

#set_property IOSTANDARD LVCMOS33 [get_ports aud_mclk]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[0]}]
#set_property PACKAGE_PIN J18 [get_ports aud_mclk]

set_property PACKAGE_PIN J19 [get_ports {GPIO_0_0_tri_io[1]}]

