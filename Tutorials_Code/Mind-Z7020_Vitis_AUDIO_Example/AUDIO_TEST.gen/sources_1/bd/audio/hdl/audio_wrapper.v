//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.1 (win64) Build 3247384 Thu Jun 10 19:36:33 MDT 2021
//Date        : Wed Sep 24 11:19:41 2025
//Host        : DESKTOP-PTM15LR running 64-bit major release  (build 9200)
//Command     : generate_target audio_wrapper.bd
//Design      : audio_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module audio_wrapper
   (DDR_addr,
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
    aud_adc_data,
    aud_bclk,
    aud_dac_data,
    aud_dac_lrc,
    aud_iic_scl_io,
    aud_iic_sda_io,
    aud_mclk);
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
  input aud_adc_data;
  output aud_bclk;
  output aud_dac_data;
  output aud_dac_lrc;
  inout aud_iic_scl_io;
  inout aud_iic_sda_io;
  input aud_mclk;

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
  wire aud_adc_data;
  wire aud_bclk;
  wire aud_dac_data;
  wire aud_dac_lrc;
  wire aud_iic_scl_i;
  wire aud_iic_scl_io;
  wire aud_iic_scl_o;
  wire aud_iic_scl_t;
  wire aud_iic_sda_i;
  wire aud_iic_sda_io;
  wire aud_iic_sda_o;
  wire aud_iic_sda_t;
  wire aud_mclk;

  IOBUF aud_iic_scl_iobuf
       (.I(aud_iic_scl_o),
        .IO(aud_iic_scl_io),
        .O(aud_iic_scl_i),
        .T(aud_iic_scl_t));
  IOBUF aud_iic_sda_iobuf
       (.I(aud_iic_sda_o),
        .IO(aud_iic_sda_io),
        .O(aud_iic_sda_i),
        .T(aud_iic_sda_t));
  audio audio_i
       (.DDR_addr(DDR_addr),
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
        .aud_adc_data(aud_adc_data),
        .aud_bclk(aud_bclk),
        .aud_dac_data(aud_dac_data),
        .aud_dac_lrc(aud_dac_lrc),
        .aud_iic_scl_i(aud_iic_scl_i),
        .aud_iic_scl_o(aud_iic_scl_o),
        .aud_iic_scl_t(aud_iic_scl_t),
        .aud_iic_sda_i(aud_iic_sda_i),
        .aud_iic_sda_o(aud_iic_sda_o),
        .aud_iic_sda_t(aud_iic_sda_t),
        .aud_mclk(aud_mclk));
endmodule
