
/*
 * constants.h
 *
 *  Created on: Oct 8, 2016
 *      Author: Wituz
 */


//typedef enum {false, true} BOOL;
#include "constants.h"

void audioInit() {
	SpuInit();
	SpuInitMalloc (SOUND_MALLOC_MAX, SPU_MALLOC_RECSIZ * (SOUND_MALLOC_MAX + 1));
	l_c_attr.mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR);
	l_c_attr.mvol.left  = 0x3fff; // set master left volume
	l_c_attr.mvol.right = 0x3fff; // set master right volume
	SpuSetCommonAttr (&l_c_attr);
}

void audioTransferVagToSPU(char* sound, int sound_size, int voice_channel) {
	SpuSetTransferMode (SpuTransByDMA); // set transfer mode to DMA
	l_vag1_spu_addr = SpuMalloc(sound_size); // allocate SPU memory for sound 1
	SpuSetTransferStartAddr(l_vag1_spu_addr); // set transfer starting address to malloced area
	SpuWrite (sound + 0x30, sound_size); // perform actual transfer
	SpuIsTransferCompleted (SPU_TRANSFER_WAIT); // wait for DMA to complete
	// mask which specific voice attributes are to be set
	g_s_attr.mask =
			(
					SPU_VOICE_VOLL |
					SPU_VOICE_VOLR |
					SPU_VOICE_PITCH |
					SPU_VOICE_WDSA |
					SPU_VOICE_ADSR_AMODE |
					SPU_VOICE_ADSR_SMODE |
					SPU_VOICE_ADSR_RMODE |
					SPU_VOICE_ADSR_AR |
					SPU_VOICE_ADSR_DR |
					SPU_VOICE_ADSR_SR |
					SPU_VOICE_ADSR_RR |
					SPU_VOICE_ADSR_SL
			);

	g_s_attr.voice = (voice_channel);

	g_s_attr.volume.left  = 0x1fff;
	g_s_attr.volume.right = 0x1fff;

	g_s_attr.pitch        = 0x1000;
	g_s_attr.addr         = l_vag1_spu_addr;
	g_s_attr.a_mode       = SPU_VOICE_LINEARIncN;
	g_s_attr.s_mode       = SPU_VOICE_LINEARIncN;
	g_s_attr.r_mode       = SPU_VOICE_LINEARDecN;
	g_s_attr.ar           = 0x0;
	g_s_attr.dr           = 0x0;
	g_s_attr.sr           = 0x0;
	g_s_attr.rr           = 0x0;
	g_s_attr.sl           = 0xf;

	SpuSetVoiceAttr (&g_s_attr);
}

void audioPlay(int voice_channel) {
	SpuSetKey(SpuOn, voice_channel);
}

void audioChannelConfigure() {
	// mask which specific voice attributes are to be set

}

void audioFree(unsigned long sound_address) {
	SpuFree(sound_address);
}

Image createImage(unsigned char imageData[], int x, int y, int scalex, int scaley, int rotation) {

	// Initialize image
	Image image;
	GsGetTimInfo ((u_long *)(imageData+4),&image.tim_data);

	// Load the image into the frame buffer
	image.rect.x = image.tim_data.px;            	// tim start X coord to put image data in frame buffer
	image.rect.y = image.tim_data.py;            	// tim start Y coord to put image data in frame buffer
	image.rect.w = image.tim_data.pw;            	// data width
	image.rect.h = image.tim_data.ph;            	// data height
	LoadImage(&image.rect, image.tim_data.pixel);

	// Load the CLUT into the frame buffer
	image.crect.x = image.tim_data.cx;            	// x pos to put CLUT in frame buffer
	image.crect.y = image.tim_data.cy;           	// y pos to put CLUT in frame buffer
	image.crect.w = image.tim_data.cw;            	// width of CLUT
	image.crect.h = image.tim_data.ch;            	// height of CLUT
	LoadImage(&image.crect, image.tim_data.clut);

	// Initialize sprite
	image.sprite.attribute = 0x1000000; 			// (0x1 = 8-bit, 0x2 = 16-bit)
	image.sprite.x = x;                         	// draw at x coord
	image.sprite.y = y;                          	// draw at y coord
	image.sprite.w = image.tim_data.pw * 2;         // width of sprite
	image.sprite.h = image.tim_data.ph;             // height of sprite

	image.ture.x = x;
	image.ture.y = y;
	image.ture.w = image.sprite.w * scalex;
	image.ture.h = image.sprite.h * scaley;

	image.sprite.tpage = GetTPage(
			1,   								// 0=4-bit, 1=8-bit, 2=16-bit
			1,   								// semitransparency rate
			image.tim_data.px, 						// framebuffer pixel x
			image.tim_data.py  						// framebuffer pixel y
	);

	image.sprite.r = 128;							// color red blend
	image.sprite.g = 128;							// color green blend
	image.sprite.b = 128;							// color blue blend
	image.sprite.u=(image.tim_data.px - 320) * 2;   // position within timfile for sprite
	image.sprite.v=image.tim_data.py;				// position within timfile for sprite
	image.sprite.cx = image.tim_data.cx;            // CLUT location x
	image.sprite.cy = image.tim_data.cy;            // CLUT location y
	image.sprite.mx = 0;                            // rotation x coord
	image.sprite.my = 0;                            // rotation y coord
	image.sprite.scalex = scalex*ONE;                      // scale x (ONE = 100%)
	image.sprite.scaley = scaley*ONE;                      // scale y (ONE = 100%)
	image.sprite.rotate = rotation;                        // rotation

	return image;
}

Image createCharacter(unsigned char imageData[], int x, int y, int scale) {

	// Initialize image
	Image image;
	GsGetTimInfo ((u_long *)(imageData+4),&image.tim_data);

	// Load the image into the frame buffer
	image.rect.x = image.tim_data.px;            	// tim start X coord to put image data in frame buffer
	image.rect.y = image.tim_data.py;            	// tim start Y coord to put image data in frame buffer
	image.rect.w = image.tim_data.pw;            	// data width
	image.rect.h = image.tim_data.ph;            	// data height
	LoadImage(&image.rect, image.tim_data.pixel);

	// Load the CLUT into the frame buffer
	image.crect.x = image.tim_data.cx;            	// x pos to put CLUT in frame buffer
	image.crect.y = image.tim_data.cy;           	// y pos to put CLUT in frame buffer
	image.crect.w = image.tim_data.cw;            	// width of CLUT
	image.crect.h = image.tim_data.ch;            	// height of CLUT
	LoadImage(&image.crect, image.tim_data.clut);

	// Initialize sprite
	image.sprite.attribute = 0x1000000; 			// (0x1 = 8-bit, 0x2 = 16-bit)
	image.sprite.x = x;                         	// draw at x coord
	image.sprite.y = y;                          	// draw at y coord
	image.sprite.w = scale;         // width of sprite
	image.sprite.h = scale;             // height of sprite

	image.ture.x = x;
	image.ture.y = y;
	image.ture.w = image.sprite.w;
	image.ture.h = image.sprite.h;

	image.sprite.tpage = GetTPage(
			1,   								// 0=4-bit, 1=8-bit, 2=16-bit
			1,   								// semitransparency rate
			image.tim_data.px, 						// framebuffer pixel x
			image.tim_data.py  						// framebuffer pixel y
	);

	image.sprite.r = 128;							// color red blend
	image.sprite.g = 128;							// color green blend
	image.sprite.b = 128;							// color blue blend
	image.sprite.cx = image.tim_data.cx;            // CLUT location x
	image.sprite.cy = image.tim_data.cy;            // CLUT location y
	image.sprite.mx = 0;                            // rotation x coord
	image.sprite.my = 0;                            // rotation y coord
	image.sprite.scalex = ONE;                      // scale x (ONE = 100%)
	image.sprite.scaley = ONE;                      // scale y (ONE = 100%)
	image.sprite.rotate = 0;                        // rotation

	return image;
}

Object createObject(unsigned char imageData[], int x, int y, int scalex, int scaley, int id) {

	// Initialize image
	Object object;
	GsGetTimInfo ((u_long *)(imageData+4),&object.tim_data);

	// Load the image into the frame buffer
	object.rect.x = object.tim_data.px;            	// tim start X coord to put object data in frame buffer
	object.rect.y = object.tim_data.py;            	// tim start Y coord to put object data in frame buffer
	object.rect.w = object.tim_data.pw;            	// data width
	object.rect.h = object.tim_data.ph;            	// data height
	LoadImage(&object.rect, object.tim_data.pixel);

	// Load the CLUT into the frame buffer
	object.crect.x = object.tim_data.cx;            	// x pos to put CLUT in frame buffer
	object.crect.y = object.tim_data.cy;           	// y pos to put CLUT in frame buffer
	object.crect.w = object.tim_data.cw;            	// width of CLUT
	object.crect.h = object.tim_data.ch;            	// height of CLUT
	LoadImage(&object.crect, object.tim_data.clut);

	// Initialize sprite
	object.sprite.attribute = 0x1000000; 			// (0x1 = 8-bit, 0x2 = 16-bit)
	object.sprite.x = x;                         	// draw at x coord
	object.sprite.y = y;                          	// draw at y coord
	object.sprite.w = object.tim_data.pw * 2;         // width of sprite
	object.sprite.h = object.tim_data.ph;             // height of sprite

	object.ture.x = x;
	object.ture.y = y;
	object.ture.w = object.sprite.w * scalex;
	object.ture.h = object.sprite.h * scaley;

	object.sprite.tpage = GetTPage(
			1,   								// 0=4-bit, 1=8-bit, 2=16-bit
			1,   								// semitransparency rate
			object.tim_data.px, 						// framebuffer pixel x
			object.tim_data.py  						// framebuffer pixel y
	);

	object.sprite.r = 128;							// color red blend
	object.sprite.g = 128;							// color green blend
	object.sprite.b = 128;							// color blue blend
	object.sprite.u=(object.tim_data.px - 320) * 2;   // position within timfile for sprite
	object.sprite.v=object.tim_data.py;				// position within timfile for sprite
	object.sprite.cx = object.tim_data.cx;            // CLUT location x
	object.sprite.cy = object.tim_data.cy;            // CLUT location y
	object.sprite.mx = 0;                            // rotation x coord
	object.sprite.my = 0;                            // rotation y coord
	object.sprite.scalex = scalex*ONE;                      // scale x (ONE = 100%)
	object.sprite.scaley = scaley*ONE;                      // scale y (ONE = 100%)
	object.objectid = id;                        // rotation

	return object;
}

Image moveImage(Image image, int x, int y) {
	image.sprite.x = x;
	image.sprite.y = y;
	image.ture.x = x;
	image.ture.y = y;
	return image;
}

Object moveObject(Object object, int x, int y) {
	object.sprite.x = x;
	object.sprite.y = y;
	object.ture.x = x;
	object.ture.y = y;
	return object;
}

Image changeImage(Image image, int u, int v) {
	image.sprite.u = u+96;
	image.sprite.v = v;
	//FntPrint(" U: %d V: %d", u+64, v, "\n");
	return image;
}

Color createColor(int r, int g, int b) {
	Color color = {.r = r, .g = g, .b = b};
	return color;
}

Line createLine(Color color, int x1, int y1, int x2, int y2) {
	Line line;
	line.type = TYPE_LINE;
	SetLineF2(&line.line);
	setRGB0(&line.line, color.r, color.g, color.b);
	setXY2(&line.line, x1, y1, x2, y2);
	return line;
}

Box createBox(Color color, int x1, int y1, int x2, int y2) {
	Line top    = createLine(color, x1, y1, x2, y1);
	Line bottom = createLine(color, x1, y2, x2, y2);
	Line left   = createLine(color, x1, y1, x1, y2);
	Line right  = createLine(color, x2, y1, x2, y2);
	Box box;
	box.type = TYPE_BOX;
	box.line[0] = top;
	box.line[1] = bottom;
	box.line[2] = left;
	box.line[3] = right;
	return box;
}

Line moveLine(Line line, int x1, int y1, int x2, int y2) {
	line.line.x0 = x1;
	line.line.y0 = y1;
	line.line.x1 = x2;
	line.line.y1 = y2;
	return line;
}

Box moveBox(Box box, int x1, int y1) {
	int currentWidth = box.line[0].line.x1 - box.line[0].line.x0;
	int currentHeight = box.line[2].line.y1 - box.line[2].line.y1;
	int x2 = x1 + currentWidth;
	int y2 = y1 + currentWidth;
	box.line[0] = moveLine(box.line[0], x1, y1, x2, y1);
	box.line[1] = moveLine(box.line[1], x1, y2, x2, y2);
	box.line[2] = moveLine(box.line[2], x1, y1, x1, y2);
	box.line[3] = moveLine(box.line[3], x2, y1, x2, y2);
	return box;
}


void drawLine(Line line) {
	DrawPrim(&line.line);
}

void drawBox(Box box) {
	int i;
	for(i = 0; i < 4; i++) {
		DrawPrim(&box.line[i].line);
	}
}

void drawImage(Image image) {
	currentBuffer = GsGetActiveBuff();
	GsSortSprite(&image.sprite, &orderingTable[currentBuffer], 0);
}

void drawObject(Object object) {
	currentBuffer = GsGetActiveBuff();
	GsSortSprite(&object.sprite, &orderingTable[currentBuffer], 0);
}

struct Point {
	int x, y;
};

int doOverlap(struct Point l1, struct Point r1, struct Point l2, struct Point r2)
{
   if ((l1.x < l2.x) && (r1.x < l2.x) || (l1.x > r2.x) && (r1.x > r2.x))
        return 0;

    // If one rectangle is above the other
    if ((l1.y < l2.y) && (r1.y < l2.y) || (l1.y > r2.y) && (r1.y > r2.y))
        return 0;

    return 1;
}

//Set the screen mode to either SCREEN_MODE_PAL or SCREEN_MODE_NTSC
void setScreenMode(int mode) {
	if (mode == SCREEN_MODE_PAL) { // SCEE string address
    	// PAL MODE
    	SCREEN_WIDTH = 320;
    	SCREEN_HEIGHT = 256;
    	if (DEBUG) printf("Setting the PlayStation Video Mode to (PAL %dx%d)\n",SCREEN_WIDTH,SCREEN_HEIGHT,")");
    	SetVideoMode(1);
    	if (DEBUG) printf("Video Mode is (%d)\n",GetVideoMode());
   	} else {
     	// NTSC MODE
     	SCREEN_WIDTH = 320;
     	SCREEN_HEIGHT = 240;
     	if (DEBUG) printf("Setting the PlayStation Video Mode to (NTSC %dx%d)\n",SCREEN_WIDTH,SCREEN_HEIGHT,")");
     	SetVideoMode(0);
     	if (DEBUG) printf("Video Mode is (%d)\n",GetVideoMode());
   }
	GsInitGraph(SCREEN_WIDTH, SCREEN_HEIGHT, GsINTER|GsOFSGPU, 1, 0);
	GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT);
}

void setBackgroundColor(Color color) {
	systemBackgroundColor = color;
}

void initializeOrderingTable(){
    GsClearOt(0,0,&orderingTable[GsGetActiveBuff()]);

    // initialise the ordering tables
    orderingTable[0].length = OT_LENGTH;
    orderingTable[1].length = OT_LENGTH;
    orderingTable[0].org = minorOrderingTable[0];
    orderingTable[1].org = minorOrderingTable[1];

    GsClearOt(0,0,&orderingTable[0]);
    GsClearOt(0,0,&orderingTable[1]);
}

void clearVRAM() {
    RECT rectTL;
    setRECT(&rectTL, 0, 0, 1024, 512);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
    return;
}

void initializeScreen() {
	if (*(char *)0xbfc7ff52=='E') setScreenMode(SCREEN_MODE_PAL);
   	else setScreenMode(SCREEN_MODE_NTSC);

	SetDispMask(1);
	ResetGraph(0);
	clearVRAM();
	GsInitGraph(SCREEN_WIDTH, SCREEN_HEIGHT, GsINTER|GsOFSGPU, 1, 0); //Set up interlation..
	GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT);	//..and double buffering.
	systemBackgroundColor = createColor(0, 0, 255);
	initializeOrderingTable();
}

void initializeDebugFont() {
	FntLoad(960, 256);
	SetDumpFnt(FntOpen(5, 20, 320, 240, 0, 512)); //Sets the dumped font for use with FntPrint();
}

void clearDisplay() {
	currentBuffer = GsGetActiveBuff();
	FntFlush(-1);
	GsSetWorkBase((PACKET*)GPUOutputPacket[currentBuffer]);
	GsClearOt(0, 0, &orderingTable[currentBuffer]);
}

void display() {
	currentBuffer = GsGetActiveBuff();
	DrawSync(0);
	VSync(0);
	GsSwapDispBuff();
	GsSortClear(systemBackgroundColor.r, systemBackgroundColor.g, systemBackgroundColor.b, &orderingTable[currentBuffer]);
	GsDrawOt(&orderingTable[currentBuffer]);
}
SVECTOR modelCube_mesh[] = {
    { -128,128,128 },
    { 128,128,128 },
    { 128,128,-128 },
    { -128,128,-128 },
    { -128,-128,128 },
    { 128,-128,128 },
    { 128,-128,-128 },
    { -128,-128,-128 }
};

SVECTOR modelCube_normal[] = {
    2365,-2365,-2365, 0,
    -2365,-2365,-2365, 0,
    -2365,-2365,2365, 0,
    2365,-2365,2365, 0,
    2365,2365,-2365, 0,
    -2365,2365,-2365, 0,
    -2365,2365,2365, 0,
    2365,2365,2365, 0
};

CVECTOR modelCube_color[] = {
    255,237,0, 0,
    255,235,0, 0,
    255,236,0, 0,
    255,2,0, 0,
    254,3,0, 0,
    255,8,0, 0,
    229,0,255, 0,
    229,0,255, 0,
    229,0,255, 0,
    5,16,250, 0,
    0,12,255, 0,
    0,12,255, 0,
    4,251,25, 0,
    0,255,26, 0,
    0,255,26, 0,
    0,248,255, 0,
    0,248,255, 0,
    0,248,255, 0,
    255,237,0, 0,
    255,237,0, 0,
    255,235,0, 0,
    255,2,0, 0,
    255,6,2, 0,
    254,3,0, 0,
    229,0,255, 0,
    232,21,232, 0,
    229,0,255, 0,
    5,16,250, 0,
    2,13,253, 0,
    0,12,255, 0,
    4,251,25, 0,
    0,255,26, 0,
    0,255,26, 0,
    0,248,255, 0,
    0,248,255, 0,
    0,248,255, 0
};

int modelCube_index[] = {
    0,2,3,
    7,5,4,
    4,1,0,
    5,2,1,
    2,7,3,
    0,7,4,
    0,1,2,
    7,6,5,
    4,5,1,
    5,6,2,
    2,6,7,
    0,3,7
};

TMESH modelCube = {
    modelCube_mesh,
    modelCube_normal,
    0,
    modelCube_color,
    12
};

SVECTOR modelCube1_mesh[] = {
    { -128,128,128 },
    { 128,128,128 },
    { 128,128,-128 },
    { -128,128,-128 },
    { -128,-128,128 },
    { 128,-128,128 },
    { 128,-128,-128 },
    { -128,-128,-128 }
};

SVECTOR modelCube1_normal[] = {
    2365,-2365,-2365, 0,
    -2365,-2365,-2365, 0,
    -2365,-2365,2365, 0,
    2365,-2365,2365, 0,
    2365,2365,-2365, 0,
    -2365,2365,-2365, 0,
    -2365,2365,2365, 0,
    2365,2365,2365, 0
};

CVECTOR modelCube1_color[] = {
    255,237,0, 0,
    255,235,0, 0,
    255,236,0, 0,
    255,2,0, 0,
    254,3,0, 0,
    255,8,0, 0,
    229,0,255, 0,
    229,0,255, 0,
    229,0,255, 0,
    5,16,250, 0,
    0,12,255, 0,
    0,12,255, 0,
    4,251,25, 0,
    0,255,26, 0,
    0,255,26, 0,
    0,248,255, 0,
    0,248,255, 0,
    0,248,255, 0,
    255,237,0, 0,
    255,237,0, 0,
    255,235,0, 0,
    255,2,0, 0,
    255,6,2, 0,
    254,3,0, 0,
    229,0,255, 0,
    232,21,232, 0,
    229,0,255, 0,
    5,16,250, 0,
    2,13,253, 0,
    0,12,255, 0,
    4,251,25, 0,
    0,255,26, 0,
    0,255,26, 0,
    0,248,255, 0,
    0,248,255, 0,
    0,248,255, 0
};

int modelCube1_index[] = {
    0,2,3,
    7,5,4,
    4,1,0,
    5,2,1,
    2,7,3,
    0,7,4,
    0,1,2,
    7,6,5,
    4,5,1,
    5,6,2,
    2,6,7,
    0,3,7
};

TMESH modelCube1 = {
    modelCube1_mesh,
    modelCube1_normal,
    0,
    modelCube1_color,
    12
};

struct {
	VECTOR	position;
	SVECTOR rotation;
	GsCOORDINATE2 coord2;
} Camera;
