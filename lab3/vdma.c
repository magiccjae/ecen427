#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"
#include "time.h"
#include "unistd.h"

#include "global.h"
#include <xuartlite_l.h>




#define DEBUG


#define FRAME_BUFFER_0_ADDR 0xC1000000  // Starting location in DDR where we will store the images that we display.

int main()
{
	init_platform();                   // Necessary for all programs.
	int Status;                        // Keep track of success/failure of system function calls.
	XAxiVdma videoDMAController;
	// There are 3 steps to initializing the vdma driver and IP.
	// Step 1: lookup the memory structure that is used to access the vdma driver.
    XAxiVdma_Config * VideoDMAConfig = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
    // Step 2: Initialize the memory structure and the hardware.
    if(XST_FAILURE == XAxiVdma_CfgInitialize(&videoDMAController, VideoDMAConfig,	XPAR_AXI_VDMA_0_BASEADDR)) {
    	xil_printf("VideoDMA Did not initialize.\r\n");
    }
    // Step 3: (optional) set the frame store number.
    if(XST_FAILURE ==  XAxiVdma_SetFrmStore(&videoDMAController, 2, XAXIVDMA_READ)) {
    	xil_printf("Set Frame Store Failed.");
    }
    // Initialization is complete at this point.

    // Setup the frame counter. We want two read frames. We don't need any write frames but the
    // function generates an error if you set the write frame count to 0. We set it to 2
    // but ignore it because we don't need a write channel at all.
    XAxiVdma_FrameCounter myFrameConfig;
    myFrameConfig.ReadFrameCount = 2;
    myFrameConfig.ReadDelayTimerCount = 10;
    myFrameConfig.WriteFrameCount =2;
    myFrameConfig.WriteDelayTimerCount = 10;
    Status = XAxiVdma_SetFrameCounter(&videoDMAController, &myFrameConfig);
    if (Status != XST_SUCCESS) {
	   xil_printf("Set frame counter failed %d\r\n", Status);
	   if(Status == XST_VDMA_MISMATCH_ERROR)
		   xil_printf("DMA Mismatch Error\r\n");
    }
    // Now we tell the driver about the geometry of our frame buffer and a few other things.
    // Our image is 480 x 640.
    XAxiVdma_DmaSetup myFrameBuffer;
    myFrameBuffer.VertSizeInput = 480;    // 480 vertical pixels.
    myFrameBuffer.HoriSizeInput = 640*4;  // 640 horizontal (32-bit pixels).
    myFrameBuffer.Stride = 640*4;         // Dont' worry about the rest of the values.
    myFrameBuffer.FrameDelay = 0;
    myFrameBuffer.EnableCircularBuf=1;
    myFrameBuffer.EnableSync = 0;
    myFrameBuffer.PointNum = 0;
    myFrameBuffer.EnableFrameCounter = 0;
    myFrameBuffer.FixedFrameStoreAddr = 0;
    if(XST_FAILURE == XAxiVdma_DmaConfig(&videoDMAController, XAXIVDMA_READ, &myFrameBuffer)) {
    	xil_printf("DMA Config Failed\r\n");
     }
    // We need to give the frame buffer pointers to the memory that it will use. This memory
    // is where you will write your video data. The vdma IP/driver then streams it to the HDMI
    // IP.
     myFrameBuffer.FrameStoreStartAddr[0] = FRAME_BUFFER_0_ADDR;

     if(XST_FAILURE == XAxiVdma_DmaSetBufferAddr(&videoDMAController, XAXIVDMA_READ,
    		               myFrameBuffer.FrameStoreStartAddr)) {
    	 xil_printf("DMA Set Address Failed Failed\r\n");
     }
     // Print a sanity message if you get this far.
     xil_printf("Woohoo! I made it through initialization.\n\r");
     // Now, let's get ready to start displaying some stuff on the screen.
     // The variables framePointer and framePointer1 are just pointers to the base address
     // of frame 0 and frame 1.
     unsigned int * framePointer = (unsigned int *) FRAME_BUFFER_0_ADDR;
     int row = 0;
     int col = 0;
     for(row=0; row<480; row++) {
    	 for(col=0; col<640; col++) {
    		 framePointer[row*640 + col] = 0x00000000;

    	 }
     }

     // This tells the HDMI controller the resolution of your display (there must be a better way to do this).
     XIo_Out32(XPAR_AXI_HDMI_0_BASEADDR, 640*480);

     // Start the DMA for the read channel only.
     if(XST_FAILURE == XAxiVdma_DmaStart(&videoDMAController, XAXIVDMA_READ)){
    	 xil_printf("DMA START FAILED\r\n");
     }
     int frameIndex = 0;
     // We have two frames, let's park on frame 0. Use frameIndex to index them.
     // Note that you have to start the DMA process before parking on a frame.
     if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, frameIndex,  XAXIVDMA_READ)) {
    	 xil_printf("vdma parking failed\n\r");
     }

     setAlienBlockPosition(0, 100);
	 setTankPosition(300, 420);
	 renderTank(framePointer);
	 renderAlien(framePointer);
	 renderBunker(framePointer);
	 while (1) {
		 Xuint8 s = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
		 if(s == 50) {	//key 2
			 Xuint8 s1 = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			 Xuint8 s2 = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			 short x = ((s1-48)*10 + (s2-48));
			 setAliens(0, x);
			 if(x < 55) {
				 renderAlien(framePointer);
			 }
		 }
		 if(s == 51) {	//key 3
			 int i = 0;
			 int j = rand() % 4;
			 int k[4] = {getAlien1BulletState(), getAlien2BulletState(), getAlien3BulletState(), getAlien4BulletState()};
			 for(i = 0; i < 16; i ++) {
				 if(k[j] == 0) {
					 break;
				 }
				 else {
					 j = rand()%4;
				 }
			 }
			 switch(j){
			 case 0:
				 if(getAlien1BulletState() == 0) {
					 setAlien1BulletState(1);
					 int x = rand()%11;
					 setAlien1BulletPosition(((getAlienBlockPositionX()+10) + 32 * x), (getAlienBlockPositionY()+120));
					 renderBullet(framePointer);
				 }
				 break;
			 case 1:
				 if(getAlien2BulletState() == 0) {
					 setAlien2BulletState(1);
					 int x = rand()%11;
					 setAlien2BulletPosition(((getAlienBlockPositionX()+10) + 32 * x), getAlienBlockPositionY()+120);
					 renderBullet(framePointer);
				 }
				 break;
			 case 2:
				 if(getAlien3BulletState() == 0) {
					 setAlien3BulletState(1);
					 int x = rand()%11;
					 setAlien3BulletPosition(((getAlienBlockPositionX()+10) + 32 * x), getAlienBlockPositionY()+120);
					 renderBullet(framePointer);
				 }
				 break;
			 case 3:
				 if(getAlien4BulletState() == 0) {
					 setAlien4BulletState(1);
					 int x = rand()%11;
					 setAlien4BulletPosition(((getAlienBlockPositionX()+10) + 32 * x), getAlienBlockPositionY()+120);
					 renderBullet(framePointer);
				 }
				 break;
			 default :
				 break;
			 }
		 }
		 if(s == 52) {	//key 4
			 moveTankL(framePointer);
			 renderTank(framePointer);
		 }
		 if(s == 53) {	//key 5
			 if(getTankBulletState() == 1) {
				 continue;
			 }
			 else {
				 setTankBulletState(1);
				 initialTankBulletPosition();
				 renderBullet(framePointer);
			 }
		 }
		 if(s == 54) {	//key 6
			 moveTankR(framePointer);
			 renderTank(framePointer);
		 }
		 if(s == 55) {	//key 7
			 Xuint8 s1 = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			 short x = s1-48;
			 if(x > 3) {
				 continue;
			 }
			 else {
				 erodeBunker(framePointer, x);
			 }
		 }
		 if(s == 56) {	//key 8
			 moveAlien(framePointer);
			 renderAlien(framePointer);
		 }
		 if(s == 57) {	//key 9
			 if(getTankBulletState() == 1 || getAlien1BulletState() == 1 || getAlien2BulletState() == 1 || \
					 getAlien3BulletState() == 1 || getAlien4BulletState() == 1) {
				 moveBullets();
				 renderBullet(framePointer);
			 }
		 }




	 }
	 cleanup_platform();

	 return 0;
}
