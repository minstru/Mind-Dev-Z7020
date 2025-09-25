//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.1 (win64) Build 3247384 Thu Jun 10 19:36:33 MDT 2021
//Date        : Wed Sep 24 13:47:27 2025
//Host        : DESKTOP-PTM15LR running 64-bit major release  (build 9200)
//Command     : generate_target system_wrapper.bd
//Design      : system_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module system_wrapper
   (CAN_0_0_rx,
    CAN_0_0_tx,
    DDR_addr,
    DDR_ba,
    DDR_cas_n,
    DDR_ck_n,
    DDR_ck_p,
    DDR_cke,
    DDR_cs_n,
    DDR_dm,
    DDR_dq,
    DDR_dqs_n,
    DDR_dqs_p,
    DDR_odt,
    DDR_ras_n,
    DDR_reset_n,
    DDR_we_n,
    FIXED_IO_ddr_vrn,
    FIXED_IO_ddr_vrp,
    FIXED_IO_mio,
    FIXED_IO_ps_clk,
    FIXED_IO_ps_porb,
    FIXED_IO_ps_srstb,
    GPIO_0_0_tri_io,
    IIC_0_0_scl_io,
    IIC_0_0_sda_io,
    IIC_1_0_scl_io,
    IIC_1_0_sda_io,
    MDIO_PHY_0_mdc,
    MDIO_PHY_0_mdio_io,
    RGMII_0_rd,
    RGMII_0_rx_ctl,
    RGMII_0_rxc,
    RGMII_0_td,
    RGMII_0_tx_ctl,
    RGMII_0_txc,
    TMDS_0_tmds_clk_n,
    TMDS_0_tmds_clk_p,
    TMDS_0_tmds_data_n,
    TMDS_0_tmds_data_p,
    UART_1_0_rxd,
    UART_1_0_txd,
    camera_data_0,
    camera_data_1,
    camera_href_0,
    camera_href_1,
    camera_pclk_0,
    camera_pclk_1,
    camera_pwdn_0,
    camera_pwdn_1,
    camera_rstn_0,
    camera_rstn_1,
    camera_vsync_0,
    camera_vsync_1,
    lcd_clk,
    lcd_data,
    lcd_de,
    lcd_hsync,
    lcd_reset,
    lcd_vsync);
  input CAN_0_0_rx;
  output CAN_0_0_tx;
  inout [14:0]DDR_addr;
  inout [2:0]DDR_ba;
  inout DDR_cas_n;
  inout DDR_ck_n;
  inout DDR_ck_p;
  inout DDR_cke;
  inout DDR_cs_n;
  inout [3:0]DDR_dm;
  inout [31:0]DDR_dq;
  inout [3:0]DDR_dqs_n;
  inout [3:0]DDR_dqs_p;
  inout DDR_odt;
  inout DDR_ras_n;
  inout DDR_reset_n;
  inout DDR_we_n;
  inout FIXED_IO_ddr_vrn;
  inout FIXED_IO_ddr_vrp;
  inout [53:0]FIXED_IO_mio;
  inout FIXED_IO_ps_clk;
  inout FIXED_IO_ps_porb;
  inout FIXED_IO_ps_srstb;
  inout [11:0]GPIO_0_0_tri_io;
  inout IIC_0_0_scl_io;
  inout IIC_0_0_sda_io;
  inout IIC_1_0_scl_io;
  inout IIC_1_0_sda_io;
  output MDIO_PHY_0_mdc;
  inout MDIO_PHY_0_mdio_io;
  input [3:0]RGMII_0_rd;
  input RGMII_0_rx_ctl;
  input RGMII_0_rxc;
  output [3:0]RGMII_0_td;
  output RGMII_0_tx_ctl;
  output RGMII_0_txc;
  output TMDS_0_tmds_clk_n;
  output TMDS_0_tmds_clk_p;
  output [2:0]TMDS_0_tmds_data_n;
  output [2:0]TMDS_0_tmds_data_p;
  input UART_1_0_rxd;
  output UART_1_0_txd;
  input [7:0]camera_data_0;
  input [7:0]camera_data_1;
  input camera_href_0;
  input camera_href_1;
  input camera_pclk_0;
  input camera_pclk_1;
  output camera_pwdn_0;
  output camera_pwdn_1;
  output camera_rstn_0;
  output camera_rstn_1;
  input camera_vsync_0;
  input camera_vsync_1;
  output lcd_clk;
  output [23:0]lcd_data;
  output lcd_de;
  output lcd_hsync;
  output [0:0]lcd_reset;
  output lcd_vsync;

  wire CAN_0_0_rx;
  wire CAN_0_0_tx;
  wire [14:0]DDR_addr;
  wire [2:0]DDR_ba;
  wire DDR_cas_n;
  wire DDR_ck_n;
  wire DDR_ck_p;
  wire DDR_cke;
  wire DDR_cs_n;
  wire [3:0]DDR_dm;
  wire [31:0]DDR_dq;
  wire [3:0]DDR_dqs_n;
  wire [3:0]DDR_dqs_p;
  wire DDR_odt;
  wire DDR_ras_n;
  wire DDR_reset_n;
  wire DDR_we_n;
  wire FIXED_IO_ddr_vrn;
  wire FIXED_IO_ddr_vrp;
  wire [53:0]FIXED_IO_mio;
  wire FIXED_IO_ps_clk;
  wire FIXED_IO_ps_porb;
  wire FIXED_IO_ps_srstb;
  wire [0:0]GPIO_0_0_tri_i_0;
  wire [1:1]GPIO_0_0_tri_i_1;
  wire [10:10]GPIO_0_0_tri_i_10;
  wire [11:11]GPIO_0_0_tri_i_11;
  wire [2:2]GPIO_0_0_tri_i_2;
  wire [3:3]GPIO_0_0_tri_i_3;
  wire [4:4]GPIO_0_0_tri_i_4;
  wire [5:5]GPIO_0_0_tri_i_5;
  wire [6:6]GPIO_0_0_tri_i_6;
  wire [7:7]GPIO_0_0_tri_i_7;
  wire [8:8]GPIO_0_0_tri_i_8;
  wire [9:9]GPIO_0_0_tri_i_9;
  wire [0:0]GPIO_0_0_tri_io_0;
  wire [1:1]GPIO_0_0_tri_io_1;
  wire [10:10]GPIO_0_0_tri_io_10;
  wire [11:11]GPIO_0_0_tri_io_11;
  wire [2:2]GPIO_0_0_tri_io_2;
  wire [3:3]GPIO_0_0_tri_io_3;
  wire [4:4]GPIO_0_0_tri_io_4;
  wire [5:5]GPIO_0_0_tri_io_5;
  wire [6:6]GPIO_0_0_tri_io_6;
  wire [7:7]GPIO_0_0_tri_io_7;
  wire [8:8]GPIO_0_0_tri_io_8;
  wire [9:9]GPIO_0_0_tri_io_9;
  wire [0:0]GPIO_0_0_tri_o_0;
  wire [1:1]GPIO_0_0_tri_o_1;
  wire [10:10]GPIO_0_0_tri_o_10;
  wire [11:11]GPIO_0_0_tri_o_11;
  wire [2:2]GPIO_0_0_tri_o_2;
  wire [3:3]GPIO_0_0_tri_o_3;
  wire [4:4]GPIO_0_0_tri_o_4;
  wire [5:5]GPIO_0_0_tri_o_5;
  wire [6:6]GPIO_0_0_tri_o_6;
  wire [7:7]GPIO_0_0_tri_o_7;
  wire [8:8]GPIO_0_0_tri_o_8;
  wire [9:9]GPIO_0_0_tri_o_9;
  wire [0:0]GPIO_0_0_tri_t_0;
  wire [1:1]GPIO_0_0_tri_t_1;
  wire [10:10]GPIO_0_0_tri_t_10;
  wire [11:11]GPIO_0_0_tri_t_11;
  wire [2:2]GPIO_0_0_tri_t_2;
  wire [3:3]GPIO_0_0_tri_t_3;
  wire [4:4]GPIO_0_0_tri_t_4;
  wire [5:5]GPIO_0_0_tri_t_5;
  wire [6:6]GPIO_0_0_tri_t_6;
  wire [7:7]GPIO_0_0_tri_t_7;
  wire [8:8]GPIO_0_0_tri_t_8;
  wire [9:9]GPIO_0_0_tri_t_9;
  wire IIC_0_0_scl_i;
  wire IIC_0_0_scl_io;
  wire IIC_0_0_scl_o;
  wire IIC_0_0_scl_t;
  wire IIC_0_0_sda_i;
  wire IIC_0_0_sda_io;
  wire IIC_0_0_sda_o;
  wire IIC_0_0_sda_t;
  wire IIC_1_0_scl_i;
  wire IIC_1_0_scl_io;
  wire IIC_1_0_scl_o;
  wire IIC_1_0_scl_t;
  wire IIC_1_0_sda_i;
  wire IIC_1_0_sda_io;
  wire IIC_1_0_sda_o;
  wire IIC_1_0_sda_t;
  wire MDIO_PHY_0_mdc;
  wire MDIO_PHY_0_mdio_i;
  wire MDIO_PHY_0_mdio_io;
  wire MDIO_PHY_0_mdio_o;
  wire MDIO_PHY_0_mdio_t;
  wire [3:0]RGMII_0_rd;
  wire RGMII_0_rx_ctl;
  wire RGMII_0_rxc;
  wire [3:0]RGMII_0_td;
  wire RGMII_0_tx_ctl;
  wire RGMII_0_txc;
  wire TMDS_0_tmds_clk_n;
  wire TMDS_0_tmds_clk_p;
  wire [2:0]TMDS_0_tmds_data_n;
  wire [2:0]TMDS_0_tmds_data_p;
  wire UART_1_0_rxd;
  wire UART_1_0_txd;
  wire [7:0]camera_data_0;
  wire [7:0]camera_data_1;
  wire camera_href_0;
  wire camera_href_1;
  wire camera_pclk_0;
  wire camera_pclk_1;
  wire camera_pwdn_0;
  wire camera_pwdn_1;
  wire camera_rstn_0;
  wire camera_rstn_1;
  wire camera_vsync_0;
  wire camera_vsync_1;
  wire lcd_clk;
  wire [23:0]lcd_data;
  wire lcd_de;
  wire lcd_hsync;
  wire [0:0]lcd_reset;
  wire lcd_vsync;

  IOBUF GPIO_0_0_tri_iobuf_0
       (.I(GPIO_0_0_tri_o_0),
        .IO(GPIO_0_0_tri_io[0]),
        .O(GPIO_0_0_tri_i_0),
        .T(GPIO_0_0_tri_t_0));
  IOBUF GPIO_0_0_tri_iobuf_1
       (.I(GPIO_0_0_tri_o_1),
        .IO(GPIO_0_0_tri_io[1]),
        .O(GPIO_0_0_tri_i_1),
        .T(GPIO_0_0_tri_t_1));
  IOBUF GPIO_0_0_tri_iobuf_10
       (.I(GPIO_0_0_tri_o_10),
        .IO(GPIO_0_0_tri_io[10]),
        .O(GPIO_0_0_tri_i_10),
        .T(GPIO_0_0_tri_t_10));
  IOBUF GPIO_0_0_tri_iobuf_11
       (.I(GPIO_0_0_tri_o_11),
        .IO(GPIO_0_0_tri_io[11]),
        .O(GPIO_0_0_tri_i_11),
        .T(GPIO_0_0_tri_t_11));
  IOBUF GPIO_0_0_tri_iobuf_2
       (.I(GPIO_0_0_tri_o_2),
        .IO(GPIO_0_0_tri_io[2]),
        .O(GPIO_0_0_tri_i_2),
        .T(GPIO_0_0_tri_t_2));
  IOBUF GPIO_0_0_tri_iobuf_3
       (.I(GPIO_0_0_tri_o_3),
        .IO(GPIO_0_0_tri_io[3]),
        .O(GPIO_0_0_tri_i_3),
        .T(GPIO_0_0_tri_t_3));
  IOBUF GPIO_0_0_tri_iobuf_4
       (.I(GPIO_0_0_tri_o_4),
        .IO(GPIO_0_0_tri_io[4]),
        .O(GPIO_0_0_tri_i_4),
        .T(GPIO_0_0_tri_t_4));
  IOBUF GPIO_0_0_tri_iobuf_5
       (.I(GPIO_0_0_tri_o_5),
        .IO(GPIO_0_0_tri_io[5]),
        .O(GPIO_0_0_tri_i_5),
        .T(GPIO_0_0_tri_t_5));
  IOBUF GPIO_0_0_tri_iobuf_6
       (.I(GPIO_0_0_tri_o_6),
        .IO(GPIO_0_0_tri_io[6]),
        .O(GPIO_0_0_tri_i_6),
        .T(GPIO_0_0_tri_t_6));
  IOBUF GPIO_0_0_tri_iobuf_7
       (.I(GPIO_0_0_tri_o_7),
        .IO(GPIO_0_0_tri_io[7]),
        .O(GPIO_0_0_tri_i_7),
        .T(GPIO_0_0_tri_t_7));
  IOBUF GPIO_0_0_tri_iobuf_8
       (.I(GPIO_0_0_tri_o_8),
        .IO(GPIO_0_0_tri_io[8]),
        .O(GPIO_0_0_tri_i_8),
        .T(GPIO_0_0_tri_t_8));
  IOBUF GPIO_0_0_tri_iobuf_9
       (.I(GPIO_0_0_tri_o_9),
        .IO(GPIO_0_0_tri_io[9]),
        .O(GPIO_0_0_tri_i_9),
        .T(GPIO_0_0_tri_t_9));
  IOBUF IIC_0_0_scl_iobuf
       (.I(IIC_0_0_scl_o),
        .IO(IIC_0_0_scl_io),
        .O(IIC_0_0_scl_i),
        .T(IIC_0_0_scl_t));
  IOBUF IIC_0_0_sda_iobuf
       (.I(IIC_0_0_sda_o),
        .IO(IIC_0_0_sda_io),
        .O(IIC_0_0_sda_i),
        .T(IIC_0_0_sda_t));
  IOBUF IIC_1_0_scl_iobuf
       (.I(IIC_1_0_scl_o),
        .IO(IIC_1_0_scl_io),
        .O(IIC_1_0_scl_i),
        .T(IIC_1_0_scl_t));
  IOBUF IIC_1_0_sda_iobuf
       (.I(IIC_1_0_sda_o),
        .IO(IIC_1_0_sda_io),
        .O(IIC_1_0_sda_i),
        .T(IIC_1_0_sda_t));
  IOBUF MDIO_PHY_0_mdio_iobuf
       (.I(MDIO_PHY_0_mdio_o),
        .IO(MDIO_PHY_0_mdio_io),
        .O(MDIO_PHY_0_mdio_i),
        .T(MDIO_PHY_0_mdio_t));
  system system_i
       (.CAN_0_0_rx(CAN_0_0_rx),
        .CAN_0_0_tx(CAN_0_0_tx),
        .DDR_addr(DDR_addr),
        .DDR_ba(DDR_ba),
        .DDR_cas_n(DDR_cas_n),
        .DDR_ck_n(DDR_ck_n),
        .DDR_ck_p(DDR_ck_p),
        .DDR_cke(DDR_cke),
        .DDR_cs_n(DDR_cs_n),
        .DDR_dm(DDR_dm),
        .DDR_dq(DDR_dq),
        .DDR_dqs_n(DDR_dqs_n),
        .DDR_dqs_p(DDR_dqs_p),
        .DDR_odt(DDR_odt),
        .DDR_ras_n(DDR_ras_n),
        .DDR_reset_n(DDR_reset_n),
        .DDR_we_n(DDR_we_n),
        .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
        .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
        .FIXED_IO_mio(FIXED_IO_mio),
        .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
        .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
        .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
        .GPIO_0_0_tri_i({GPIO_0_0_tri_i_11,GPIO_0_0_tri_i_10,GPIO_0_0_tri_i_9,GPIO_0_0_tri_i_8,GPIO_0_0_tri_i_7,GPIO_0_0_tri_i_6,GPIO_0_0_tri_i_5,GPIO_0_0_tri_i_4,GPIO_0_0_tri_i_3,GPIO_0_0_tri_i_2,GPIO_0_0_tri_i_1,GPIO_0_0_tri_i_0}),
        .GPIO_0_0_tri_o({GPIO_0_0_tri_o_11,GPIO_0_0_tri_o_10,GPIO_0_0_tri_o_9,GPIO_0_0_tri_o_8,GPIO_0_0_tri_o_7,GPIO_0_0_tri_o_6,GPIO_0_0_tri_o_5,GPIO_0_0_tri_o_4,GPIO_0_0_tri_o_3,GPIO_0_0_tri_o_2,GPIO_0_0_tri_o_1,GPIO_0_0_tri_o_0}),
        .GPIO_0_0_tri_t({GPIO_0_0_tri_t_11,GPIO_0_0_tri_t_10,GPIO_0_0_tri_t_9,GPIO_0_0_tri_t_8,GPIO_0_0_tri_t_7,GPIO_0_0_tri_t_6,GPIO_0_0_tri_t_5,GPIO_0_0_tri_t_4,GPIO_0_0_tri_t_3,GPIO_0_0_tri_t_2,GPIO_0_0_tri_t_1,GPIO_0_0_tri_t_0}),
        .IIC_0_0_scl_i(IIC_0_0_scl_i),
        .IIC_0_0_scl_o(IIC_0_0_scl_o),
        .IIC_0_0_scl_t(IIC_0_0_scl_t),
        .IIC_0_0_sda_i(IIC_0_0_sda_i),
        .IIC_0_0_sda_o(IIC_0_0_sda_o),
        .IIC_0_0_sda_t(IIC_0_0_sda_t),
        .IIC_1_0_scl_i(IIC_1_0_scl_i),
        .IIC_1_0_scl_o(IIC_1_0_scl_o),
        .IIC_1_0_scl_t(IIC_1_0_scl_t),
        .IIC_1_0_sda_i(IIC_1_0_sda_i),
        .IIC_1_0_sda_o(IIC_1_0_sda_o),
        .IIC_1_0_sda_t(IIC_1_0_sda_t),
        .MDIO_PHY_0_mdc(MDIO_PHY_0_mdc),
        .MDIO_PHY_0_mdio_i(MDIO_PHY_0_mdio_i),
        .MDIO_PHY_0_mdio_o(MDIO_PHY_0_mdio_o),
        .MDIO_PHY_0_mdio_t(MDIO_PHY_0_mdio_t),
        .RGMII_0_rd(RGMII_0_rd),
        .RGMII_0_rx_ctl(RGMII_0_rx_ctl),
        .RGMII_0_rxc(RGMII_0_rxc),
        .RGMII_0_td(RGMII_0_td),
        .RGMII_0_tx_ctl(RGMII_0_tx_ctl),
        .RGMII_0_txc(RGMII_0_txc),
        .TMDS_0_tmds_clk_n(TMDS_0_tmds_clk_n),
        .TMDS_0_tmds_clk_p(TMDS_0_tmds_clk_p),
        .TMDS_0_tmds_data_n(TMDS_0_tmds_data_n),
        .TMDS_0_tmds_data_p(TMDS_0_tmds_data_p),
        .UART_1_0_rxd(UART_1_0_rxd),
        .UART_1_0_txd(UART_1_0_txd),
        .camera_data_0(camera_data_0),
        .camera_data_1(camera_data_1),
        .camera_href_0(camera_href_0),
        .camera_href_1(camera_href_1),
        .camera_pclk_0(camera_pclk_0),
        .camera_pclk_1(camera_pclk_1),
        .camera_pwdn_0(camera_pwdn_0),
        .camera_pwdn_1(camera_pwdn_1),
        .camera_rstn_0(camera_rstn_0),
        .camera_rstn_1(camera_rstn_1),
        .camera_vsync_0(camera_vsync_0),
        .camera_vsync_1(camera_vsync_1),
        .lcd_clk(lcd_clk),
        .lcd_data(lcd_data),
        .lcd_de(lcd_de),
        .lcd_hsync(lcd_hsync),
        .lcd_reset(lcd_reset),
        .lcd_vsync(lcd_vsync));
endmodule
