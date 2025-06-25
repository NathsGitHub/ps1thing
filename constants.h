#pragma once

#include <STDLIB.H>
#include <STDIO.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBGS.H>
#include <LIBETC.H>
#include <stdbool.h>

#include <LIBSPU.H>
#include <SYS/TYPES.H>
#include "controller.h"
#include "imagekit/images.h"


#define OT_LENGTH 1
#define PACKETMAX 300
#define TYPE_LINE 0
#define TYPE_BOX 1
#define SCREEN_MODE_PAL 0
#define SCREEN_MODE_NTSC 1
#define DEBUG 1
#define SOUND_MALLOC_MAX 10

typedef struct {
	int r;
	int g;
	int b;
} Color;

typedef struct {
	LINE_F2 line;
	int type;
} Line;

typedef struct {
	Line line[4];
	int type;
} Box;

typedef struct {
	RECT rect;
	RECT crect;
	RECT ture;
	GsIMAGE tim_data;
	GsSPRITE sprite;
} Image;

typedef struct {
	RECT rect;
	RECT crect;
	RECT ture;
	GsIMAGE tim_data;
	GsSPRITE sprite;
	int objectid;
} Object;

int 		  SCREEN_WIDTH, SCREEN_HEIGHT;
GsOT 		  orderingTable[2];
GsOT_TAG  	  minorOrderingTable[2][1<<OT_LENGTH];
PACKET 		  GPUOutputPacket[2][PACKETMAX];
short 		  currentBuffer;
Color 		  systemBackgroundColor;
SpuCommonAttr l_c_attr;
SpuVoiceAttr  g_s_attr;
unsigned long l_vag1_spu_addr;