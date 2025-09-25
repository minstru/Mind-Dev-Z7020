
`timescale 1ns / 1ps

module serializer_10_to_1(
    input           reset,              // reset
    input           paralell_clk,       // parallel clk
    input           serial_clk_5x,      // serial clk
    input   [9:0]   paralell_data,      // data in
    output 			serial_data_out     // data out
    );
    
//wire define
wire		cascade1;
wire		cascade2;
  
    
// Instantiate the OSERDESE2 primitive to implement parallel-to-serial conversion and Master mode
OSERDESE2 #(
    .DATA_RATE_OQ   ("DDR"),       //
    .DATA_RATE_TQ   ("SDR"),       // DDR, BUF, SDR
    .DATA_WIDTH     (10),          // data width to 10 bits
    .SERDES_MODE    ("MASTER"),    // master mode
    .TBYTE_CTL      ("FALSE"),     // Enable tristate byte operation (FALSE, TRUE)
    .TBYTE_SRC      ("FALSE"),     // Tristate byte source (FALSE, TRUE)
    .TRISTATE_WIDTH (1)            // 3-state converter width (1,4)
)
OSERDESE2_Master (
    .CLK        (serial_clk_5x),    // Serial data clock, 5 times the clock frequency
    .CLKDIV     (paralell_clk),     // Parallel Data Clock
    .RST        (reset),            // 1-bit input: Reset
    .OCE        (1'b1),             // 1-bit input: Output data clock enable
    
    .OQ         (serial_data_out),  // Serial output data
    
    .D1         (paralell_data[0]), // D1 - D8: Parallel input Data
    .D2         (paralell_data[1]),
    .D3         (paralell_data[2]),
    .D4         (paralell_data[3]),
    .D5         (paralell_data[4]),
    .D6         (paralell_data[5]),
    .D7         (paralell_data[6]),
    .D8         (paralell_data[7]),
   
    .SHIFTIN1   (cascade1),         // SHIFTIN1 For bit width expansion
    .SHIFTIN2   (cascade2),         // SHIFTIN2
    .SHIFTOUT1  (),                 // SHIFTOUT1: For bit width expansion
    .SHIFTOUT2  (),                 // SHIFTOUT2
        
    .OFB        (),                 // 以下是未使用信号
    .T1         (1'b0),             
    .T2         (1'b0),
    .T3         (1'b0),
    .T4         (1'b0),
    .TBYTEIN    (1'b0),             
    .TCE        (1'b0),             
    .TBYTEOUT   (),                 
    .TFB        (),                 
    .TQ         ()                  
);
   
// Instantiate the OSERDESE2 primitive to implement parallel-to-serial conversion, Slave mode
OSERDESE2 #(
    .DATA_RATE_OQ   ("DDR"),       //
    .DATA_RATE_TQ   ("SDR"),       // DDR, BUF, SDR
    .DATA_WIDTH     (10),           // data width to 10 bits
    .SERDES_MODE    ("SLAVE"),     // slave mode
    .TBYTE_CTL      ("FALSE"),     // Enable tristate byte operation (FALSE, TRUE)
    .TBYTE_SRC      ("FALSE"),     // Tristate byte source (FALSE, TRUE)
    .TRISTATE_WIDTH (1)             // 3-state converter width (1,4)
)
OSERDESE2_Slave (
    .CLK        (serial_clk_5x),    // Serial data clock, 5 times the clock frequency
    .CLKDIV     (paralell_clk),     // Parallel Data Clock
    .RST        (reset),            // 1-bit input: Reset
    .OCE        (1'b1),             // 1-bit input: Output data clock enable
    
    .OQ         (),                 // Serial output data
    
    .D1         (1'b0),             // D1 - D8: Parallel input Data
    .D2         (1'b0),
    .D3         (paralell_data[8]),
    .D4         (paralell_data[9]),
    .D5         (1'b0),
    .D6         (1'b0),
    .D7         (1'b0),
    .D8         (1'b0),
   
    .SHIFTIN1   (),                 // SHIFTIN1 For bit width expansion
    .SHIFTIN2   (),                 // SHIFTIN2
    .SHIFTOUT1  (cascade1),         // SHIFTOUT1: For bit width expansion
    .SHIFTOUT2  (cascade2),         // SHIFTOUT2
        
    .OFB        (),                
    .T1         (1'b0),             
    .T2         (1'b0),
    .T3         (1'b0),
    .T4         (1'b0),
    .TBYTEIN    (1'b0),             
    .TCE        (1'b0),             
    .TBYTEOUT   (),                 
    .TFB        (),                 
    .TQ         ()                  
);  
        
endmodule