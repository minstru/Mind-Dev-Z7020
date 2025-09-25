# PL_KEY0
set_property PACKAGE_PIN M14 [get_ports {GPIO_0_0_tri_io[0]}]
# PL_KEY1
set_property PACKAGE_PIN M15 [get_ports {GPIO_0_0_tri_io[1]}]
# PL_LED0
set_property PACKAGE_PIN N15 [get_ports {GPIO_0_0_tri_io[2]}]
# PL_LED1
set_property PACKAGE_PIN N16 [get_ports {GPIO_0_0_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[0]}]



set_property PACKAGE_PIN G14 [get_ports CAN_0_0_rx]
set_property PACKAGE_PIN J15 [get_ports CAN_0_0_tx]
set_property IOSTANDARD LVCMOS33 [get_ports CAN_0_0_rx]
set_property IOSTANDARD LVCMOS33 [get_ports CAN_0_0_tx]



#set_property IOSTANDARD LVCMOS33 [get_ports reset_rtl_0]
set_property PACKAGE_PIN M19 [get_ports {TMDS_0_tmds_data_p[2]}]
set_property PACKAGE_PIN G19 [get_ports {TMDS_0_tmds_data_p[1]}]
set_property PACKAGE_PIN J20 [get_ports {TMDS_0_tmds_data_p[0]}]
set_property PACKAGE_PIN L16 [get_ports TMDS_0_tmds_clk_p]
#set_property PACKAGE_PIN F16 [get_ports reset_rtl_0]


set_property IOSTANDARD LVCMOS33 [get_ports IIC_0_0_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports IIC_0_0_sda_io]
set_property PACKAGE_PIN L14 [get_ports IIC_0_0_sda_io]
set_property PACKAGE_PIN L15 [get_ports IIC_0_0_scl_io]

set_property PACKAGE_PIN F19 [get_ports MDIO_PHY_0_mdc]
set_property PACKAGE_PIN F20 [get_ports MDIO_PHY_0_mdio_io]
set_property IOSTANDARD LVCMOS33 [get_ports MDIO_PHY_0_mdc]
set_property IOSTANDARD LVCMOS33 [get_ports MDIO_PHY_0_mdio_io]
set_property PACKAGE_PIN E18 [get_ports {RGMII_0_rd[0]}]
set_property PACKAGE_PIN E19 [get_ports {RGMII_0_rd[1]}]
set_property PACKAGE_PIN D18 [get_ports {RGMII_0_rd[2]}]
set_property PACKAGE_PIN E17 [get_ports {RGMII_0_rd[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGMII_0_rd[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGMII_0_rd[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGMII_0_rd[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGMII_0_rd[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGMII_0_td[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGMII_0_td[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGMII_0_td[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGMII_0_td[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports RGMII_0_rx_ctl]
set_property IOSTANDARD LVCMOS33 [get_ports RGMII_0_rxc]
set_property IOSTANDARD LVCMOS33 [get_ports RGMII_0_tx_ctl]
set_property IOSTANDARD LVCMOS33 [get_ports RGMII_0_txc]
set_property PACKAGE_PIN A20 [get_ports {RGMII_0_td[0]}]
set_property PACKAGE_PIN B20 [get_ports {RGMII_0_td[1]}]
set_property PACKAGE_PIN C20 [get_ports {RGMII_0_td[2]}]
set_property PACKAGE_PIN D19 [get_ports {RGMII_0_td[3]}]
set_property PACKAGE_PIN H17 [get_ports RGMII_0_rx_ctl]
set_property PACKAGE_PIN H16 [get_ports RGMII_0_rxc]
set_property PACKAGE_PIN D20 [get_ports RGMII_0_tx_ctl]
set_property PACKAGE_PIN B19 [get_ports RGMII_0_txc]

set_property SLEW FAST [get_ports {RGMII_0_td[0]}]
set_property SLEW FAST [get_ports {RGMII_0_td[1]}]
set_property SLEW FAST [get_ports {RGMII_0_td[2]}]
set_property SLEW FAST [get_ports {RGMII_0_td[3]}]
set_property SLEW FAST [get_ports RGMII_0_tx_ctl]
set_property SLEW FAST [get_ports RGMII_0_txc]

create_clock -period 8.000 -name RGMII_0_rxc -waveform {0.000 4.000} [get_ports RGMII_0_rxc]
#set_clock_groups -logically_exclusive -group [get_clocks -include_generated_clocks {gmii_clk_25m_out gmii_clk_2_5m_out}] -group [get_clocks -include_generated_clocks gmii_clk_125m_out]




set_property PACKAGE_PIN K14 [get_ports UART_1_0_txd]
set_property PACKAGE_PIN J14 [get_ports UART_1_0_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports UART_1_0_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports UART_1_0_txd]

set_property IOSTANDARD LVCMOS33 [get_ports IIC_1_0_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports IIC_1_0_sda_io]
set_property PACKAGE_PIN U13 [get_ports IIC_1_0_sda_io]
set_property PACKAGE_PIN V16 [get_ports IIC_1_0_scl_io]

set_property PACKAGE_PIN V18 [get_ports lcd_de]
set_property PACKAGE_PIN W18 [get_ports lcd_hsync]
set_property PACKAGE_PIN W19 [get_ports lcd_vsync]
set_property IOSTANDARD LVCMOS33 [get_ports lcd_de]
set_property IOSTANDARD LVCMOS33 [get_ports lcd_hsync]
set_property IOSTANDARD LVCMOS33 [get_ports lcd_vsync]

set_property -dict {PACKAGE_PIN T16 IOSTANDARD LVCMOS33} [get_ports {lcd_data[0]}]
set_property -dict {PACKAGE_PIN U17 IOSTANDARD LVCMOS33} [get_ports {lcd_data[1]}]
set_property -dict {PACKAGE_PIN T15 IOSTANDARD LVCMOS33} [get_ports {lcd_data[2]}]
set_property -dict {PACKAGE_PIN T14 IOSTANDARD LVCMOS33} [get_ports {lcd_data[3]}]
set_property -dict {PACKAGE_PIN Y17 IOSTANDARD LVCMOS33} [get_ports {lcd_data[4]}]
set_property -dict {PACKAGE_PIN Y18 IOSTANDARD LVCMOS33} [get_ports {lcd_data[5]}]
set_property -dict {PACKAGE_PIN Y16 IOSTANDARD LVCMOS33} [get_ports {lcd_data[6]}]
set_property -dict {PACKAGE_PIN Y14 IOSTANDARD LVCMOS33} [get_ports {lcd_data[7]}]
set_property -dict {PACKAGE_PIN N18 IOSTANDARD LVCMOS33} [get_ports {lcd_data[8]}]
set_property -dict {PACKAGE_PIN P19 IOSTANDARD LVCMOS33} [get_ports {lcd_data[9]}]
set_property -dict {PACKAGE_PIN W15 IOSTANDARD LVCMOS33} [get_ports {lcd_data[10]}]
set_property -dict {PACKAGE_PIN V15 IOSTANDARD LVCMOS33} [get_ports {lcd_data[11]}]
set_property -dict {PACKAGE_PIN R17 IOSTANDARD LVCMOS33} [get_ports {lcd_data[12]}]
set_property -dict {PACKAGE_PIN R16 IOSTANDARD LVCMOS33} [get_ports {lcd_data[13]}]
set_property -dict {PACKAGE_PIN R14 IOSTANDARD LVCMOS33} [get_ports {lcd_data[14]}]
set_property -dict {PACKAGE_PIN P14 IOSTANDARD LVCMOS33} [get_ports {lcd_data[15]}]
set_property -dict {PACKAGE_PIN N17 IOSTANDARD LVCMOS33} [get_ports {lcd_data[16]}]
set_property -dict {PACKAGE_PIN P18 IOSTANDARD LVCMOS33} [get_ports {lcd_data[17]}]
set_property -dict {PACKAGE_PIN R18 IOSTANDARD LVCMOS33} [get_ports {lcd_data[18]}]
set_property -dict {PACKAGE_PIN T17 IOSTANDARD LVCMOS33} [get_ports {lcd_data[19]}]
set_property -dict {PACKAGE_PIN P15 IOSTANDARD LVCMOS33} [get_ports {lcd_data[20]}]
set_property -dict {PACKAGE_PIN P16 IOSTANDARD LVCMOS33} [get_ports {lcd_data[21]}]
set_property -dict {PACKAGE_PIN U18  IOSTANDARD LVCMOS33} [get_ports {lcd_data[22]}]
set_property -dict {PACKAGE_PIN U19  IOSTANDARD LVCMOS33} [get_ports {lcd_data[23]}]


set_property IOSTANDARD LVCMOS33 [get_ports {lcd_reset[0]}]
set_property PACKAGE_PIN P20 [get_ports {lcd_reset[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports lcd_clk]
set_property PACKAGE_PIN W14 [get_ports lcd_clk]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[4]}]
# lcd_bl
set_property PACKAGE_PIN V17 [get_ports {GPIO_0_0_tri_io[4]}]
# lcd_tp_reset
set_property PACKAGE_PIN V13 [get_ports {GPIO_0_0_tri_io[5]}]
# lcd_tp_int
set_property PACKAGE_PIN N20 [get_ports {GPIO_0_0_tri_io[6]}]
