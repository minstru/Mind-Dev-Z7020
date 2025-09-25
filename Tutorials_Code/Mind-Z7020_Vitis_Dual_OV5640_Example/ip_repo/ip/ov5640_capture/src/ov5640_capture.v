
module  ov5640_capture(
    input                 rst_n           , 

	//camera interface
    input                 camera_pclk        ,  // pixel clk
    input                 camera_vsync       ,  // vsync
    input                 camera_href        ,  // hsync
    input        [7:0]    camera_data        ,  // data
    output                camera_rstn       ,   // cam reset
    output                camera_pwdn        ,  // cam power down

	//rgb interface
    output                rgb_frame_clk,    // cmos frame clock
    output                rgb_frame_ce,     // cmos frame clock enable

	output                rgb_frame_vsync,  // cmos frame valid
    output                rgb_active_video ,// cmos active video
    output       [23:0]   rgb_frame_data    // cmos frame data
);

// after config register, wait for 10 frame
localparam  FRAME_WAIT_NUM = 4'd10;

//reg define
reg          rst_n_d0 =1;
reg          rst_n_syn =1;
reg          camera_vsync_d0 ;
reg          camera_vsync_d1 ;
reg          camera_href_d0 ;
reg          camera_href_d1 ;
reg   [3:0]  cmos_ps_cnt ;                  // the count of wait frame
reg          wait_done ;
reg          byte_flag ;
reg   [7:0]  camera_data_d0 ;
reg  [15:0]  rgb_data_16b ;                // temporary register for 8-bit to 16-bit conversion
reg          byte_flag_d0 ;

//wire define
wire  pos_vsync ;


assign  camera_rstn = 1'b1;

//the rising edge of vsync
assign  pos_vsync  = (~camera_vsync_d1) & camera_vsync_d0 ;

//power down mode selection 0: normal mode 1: power down mode
assign  camera_pwdn  = 1'b0;

assign  rgb_frame_clk   = camera_pclk;

// Since the two clock cycles of the camera input interface correspond to one valid clock cycle of the RGB888 output interface
// So we need to give the data valid flag, that is, the clock enable signal of the RGB888 output interface
assign  rgb_frame_ce     = wait_done  ?  (byte_flag_d0 & rgb_active_video) || (!rgb_active_video) : 1'b0;
assign  rgb_frame_vsync  = wait_done  ?  camera_vsync_d1  :  1'b0;
assign  rgb_active_video = wait_done  ?  camera_href_d1   :  1'b0;
assign  rgb_frame_data   = wait_done  ?  { rgb_data_16b[15:11],3'd0 , rgb_data_16b[10:5],2'd0 , rgb_data_16b[4:0],3'd0 } : 24'd0;

// Asynchronous reset and synchronous release processing of reset signal
always @(posedge camera_pclk or negedge rst_n) begin
    if(!rst_n) begin
        rst_n_d0 <= 1'b0;
        rst_n_d0 <= 1'b0;
    end
    else begin
        rst_n_d0  <= 1'b1;
        rst_n_syn <= rst_n_d0;
    end
end

always @(posedge camera_pclk or negedge rst_n_syn) begin
    if(!rst_n_syn) begin
        camera_vsync_d0 <= 1'b0;
        camera_vsync_d1 <= 1'b0;

        camera_href_d0 <= 1'b0;
        camera_href_d1 <= 1'b0;
    end
    else begin
        camera_vsync_d0 <= camera_vsync;
        camera_vsync_d1 <= camera_vsync_d0;

        camera_href_d0 <= camera_href;
        camera_href_d1 <= camera_href_d0;
    end
end

// After all registers are configured, wait for 10 frames of data
// Wait until the register configuration takes effect before starting to collect images
always @(posedge camera_pclk or negedge rst_n_syn) begin
    if(!rst_n_syn)
        cmos_ps_cnt <= 4'd0;
    else if(pos_vsync && (cmos_ps_cnt < FRAME_WAIT_NUM))
        cmos_ps_cnt <= cmos_ps_cnt + 4'd1;  // Count the number of frames
end

// After waiting is complete, give the waiting done signal
always @(posedge camera_pclk or negedge rst_n_syn) begin
    if(!rst_n_syn)
        wait_done <= 1'b0;
    else if((cmos_ps_cnt == FRAME_WAIT_NUM) && pos_vsync)
        wait_done <= 1'b1;
end


// Convert 8-bit data to 16-bit RGB565 data
always @(posedge camera_pclk or negedge rst_n_syn) begin
    if(!rst_n_syn) begin
        rgb_data_16b <= 16'd0;
        camera_data_d0 <= 8'd0;
        byte_flag <= 1'b0;
    end
    else if( camera_href ) begin
        byte_flag   <= ~byte_flag;
        camera_data_d0 <= camera_data;
        if(byte_flag)
            rgb_data_16b <= {camera_data_d0,camera_data};
    end
    else begin
        byte_flag <= 1'b0;
        camera_data_d0 <= 8'b0;
    end
end

always @(posedge camera_pclk or negedge rst_n_syn) begin
    if(!rst_n_syn)
        byte_flag_d0 <= 1'b0;
    else
        byte_flag_d0 <= byte_flag;
end

endmodule
