
/*
* Really basic hello world
* Thanks to much work from the authors of pcsx-redux 
* and the members of PSXDEV Netowork on discord
*   Author of this setup: NDR008
*/

//#include <stdio.h>
//#include <stdbool.h>
#include "constants.c"
#include "animation.h"
#include "comptext.h"

#include "sounds/ffinchedsond.h"

//#include <sys/types.h>
//#include <libgte.h>
//#include <libgpu.h>
//#include <libetc.h>
//#include <stdio.h>
//#include <stdint.h>

#define BOX_RADIUS 16
#define BUFFER_LENGTH 32768


DISPENV display_env[2];
DRAWENV draw_env[2];
int buffer_id = 0;

// Set up ordering table and packet buffer
// Two of each for dual buffer rendering
uint32_t ordering_table[2][OT_LENGTH];
uint8_t packets[2][BUFFER_LENGTH];
uint8_t* p_nextPacket;

// Buffer for controller input. 2 controller ports, 34 bytes each to support 4 controllers in a multitap
char joypads[2][34] = { 0xFF };

//Line line;
Image wall[7];
Image vcream;
Object object[8];


Image bootup;




void drawd();

void update();
void init();

int vcrspeed = 2;
int mapposx = 1;
int mapposy = 0;
int a;
int b;
int c;
int animframe = 0;
int animframe2 = 0; 
bool newscreen = true;
int posbeforex = 0;
int posbeforey = 0;
int idletype = 1;
bool interact = false;
bool incomputer = false;




void init() {
    initializeScreen();
    initializePad();
    ResetGraph(0);
    audioInit();
    audioTransferVagToSPU(ffinched, ffinched_size, SPU_0CH);
    audioPlay(SPU_0CH);
    walkstart();

    
    FntLoad(960, 0);
    SetDumpFnt(FntOpen(16, 16, 250, 64, 0, 256));
}

void walkstart(){
    b = 1;
    setBackgroundColor(createColor(5, 5, 5));
    //line = createLine(createColor(224, 101, 56), 32, 32, 64, 64);
    vcream = createCharacter(img_vcreamD, 100, 50, 32);
    vcream = changeImage(vcream, 0, 0);
    
}

void computerstart(){
    b = 1;
    setBackgroundColor(createColor(255, 5, 5));
    bootup = createImage(img_Fveggspr, 150, 100, 1, 1, 0);

    
}

void update(void) {
    if(incomputer){

        FntPrint(comp1[1].text, "\n");
        padUpdate();
        if(padCheck(Pad1Up) || padCheck(Pad1Down) || padCheck(Pad1Left) || padCheck(Pad1Right)) {

        }
        if(padCheckPressed(Pad1Down)) {

        }
        if(padCheckPressed(Pad1Down)) {
            
        }
        if(padCheckPressed(Pad1Left)) {
            
        }
        if(padCheckPressed(Pad1Right)) {
            
        }
        
    }
    else{
               //vcream = changeImage(vcream, 0, 0);
        padUpdate();
        if(padCheck(Pad1Up) || padCheck(Pad1Down) || padCheck(Pad1Left) || padCheck(Pad1Right)) {

        }
            //FntPrint(" X: %d Y: %d", vcream.ture.w, posbeforex, "\n");
            //FntPrint(" X: %d Y: %d", vcream.ture.y, posbeforey, "\n");
        FntPrint(" X: %d Y: %d", b, animframe, "\n");
        
        if(b < 300 && vcream.ture.x == posbeforex && vcream.ture.y == posbeforey){
            animframe = 0;
            
            vcream = changeImage(vcream, vcreamspridle[animframe].x, vcreamspridle[animframe].y);
        }

        if(idletype == 0){  
            if(animframe <= sizeof(vcreamspridle2)/4 && vcream.ture.x == posbeforex && vcream.ture.y == posbeforey){
                if(b == 315 || b == 300){    
                    
                    if (vcreamspridle2[animframe].id == 2){
                    
                        vcream = changeImage(vcream, vcreamspridle2[animframe].x, vcreamspridle2[animframe].y);
                        animframe++;
                    }
                    else
                        vcream = changeImage(vcream, 0, 0);
                }
                if(b == 316){
                    b = 300;
                }
                b++;

                if(animframe == 12){
                    animframe = 6;
                }
            }
        }
        else if (idletype == 1){
            if(animframe <= sizeof(vcreamspridle1)/4 && vcream.ture.x == posbeforex && vcream.ture.y == posbeforey){
                if(b == 310 || b == 300){    
                    
                    if (vcreamspridle1[animframe].id == 1){
                        vcream = changeImage(vcream, vcreamspridle1[animframe].x, vcreamspridle1[animframe].y);
                        animframe++;
                    }
                    else
                        vcream = changeImage(vcream, 0, 0);
                }
                if(b == 315){
                    b = 300;
                }
                b++;

                if(animframe == 9)
                animframe = 7;
            }
        }

        posbeforex = vcream.ture.x;
        posbeforey = vcream.ture.y;

        if(padCheck(Pad1Up)) {
            vcream.ture.y -= vcrspeed;
            vcream = moveImage(vcream, vcream.ture.x, vcream.ture.y);
            vcream = changeImage(vcream, 0, 0);
            animframe = 0;
            b = 0;
            idletype = 0;
            
        }
        if(padCheck(Pad1Down)) {
            vcream.ture.y += vcrspeed;
            vcream = moveImage(vcream, vcream.ture.x, vcream.ture.y);
            idletype = 0;
            b = 0;
            if(vcrspeed == 1){
                if(animframe <= sizeof(vcreamsprwalk)/4){
                    if(animframe2 == 15 || animframe2 == 0){    
                        
                        if (vcreamsprwalk[animframe].id == 3){
                        
                            vcream = changeImage(vcream, vcreamsprwalk[animframe].x, vcreamsprwalk[animframe].y);
                            animframe++;
                        }
                        else
                            vcream = changeImage(vcream, 0, 0);
                    }
                    if(animframe2 >= 16){
                        animframe2 = 0;
                    }
                    animframe2++;

                    if(animframe >= 4){
                        animframe = 0;
                    }
                }
            }
            else if (vcrspeed == 2){
                if(animframe <= sizeof(vcreamsprwalk)/4){
                    if(animframe2 == 10 || animframe2 == 0){    
                        
                        if (vcreamsprwalk[animframe].id == 3){
                            
                            vcream = changeImage(vcream, vcreamsprwalk[animframe].x, vcreamsprwalk[animframe].y);
                            
                            animframe++;
                        }
                        else
                            vcream = changeImage(vcream, 0, 0);
                    }
                    if(animframe2 >= 11){
                        animframe2 = 0;
                    }
                    animframe2++;

                    if(animframe >= 4){
                        animframe = 0;
                    }
                }
            }
        }
        if(padCheck(Pad1Left)) {
            vcream.ture.x -= vcrspeed;
            vcream = moveImage(vcream, vcream.ture.x, vcream.ture.y);
            vcream = changeImage(vcream, 0, 0);
            animframe = 0;
            b = 0;
            idletype = 1;
        }
        if(padCheck(Pad1Right)) {
            vcream.ture.x += vcrspeed;
            vcream = moveImage(vcream, vcream.ture.x, vcream.ture.y);
            vcream = changeImage(vcream, 0, 0);
            animframe = 0;
            b = 0;
            idletype = 1;
            
        }

        if(padCheck(Pad1Circle)){
            vcrspeed = 2;
        }
        else{
            vcrspeed = 1;
        }
        if(padCheck(Pad1Cross)){
            struct Point l1 = { vcream.ture.x, vcream.ture.y }, r1 = { vcream.ture.x+vcream.ture.w, vcream.ture.y+vcream.ture.h };
            for(a = 0; a <= 4; a++){
            struct Point l2 = { object[a].ture.x-3, object[a].ture.y-3 }, r2 = { object[a].ture.x+object[a].ture.w+3, object[a].ture.y+object[a].ture.h+3 }; 
                if (doOverlap(l1, r1, l2, r2)){
                    //vcream = moveImage(vcream, posbeforex, posbeforey);
                    
                    if(object[a].objectid == 1)
                        FntPrint("Its Surge");
                    if(object[a].objectid == 2){
                        FntPrint("Computer");
                        incomputer = true;
                        computerstart();
                    }
                }
            }
        }
        if(vcream.ture.x > 320) {
            newscreen = true;
            vcream.ture.x = -32;
            mapposx += 1;
        }

        if(vcream.ture.x < -32) {
            newscreen = true;
            vcream.ture.x = 320;
            mapposx -= 1;
        }
        if(vcream.ture.y > 240) {
            newscreen = true;
            vcream.ture.y = -32;
            mapposy += 1;
            
        }
        if(vcream.ture.y < -32) {
            newscreen = true;
            vcream.ture.y = 240;
            mapposy -= 1;
        }
        
        if(newscreen){
            for(c = 0; c <= 5; c++){
                moveObject(object[c], 400, 0);
                FntPrint(" X: %d Y: %d", mapposx, mapposy, "\n");
            }
            //Hallways
            if(mapposx == 3 && mapposy == 0){
                
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 128, 3, 4, 0);
                wall[1] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[2] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0); 
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 1 && mapposy == 0){
                newscreen = false;
                
                wall[0] = createImage(img_wallhorz, 220, 128, 2, 4, 0);
                wall[1] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[2] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_Fvsurge, 100, 90, 1, 1, 1); 
                object[1] = createObject(img_eggpcU, 200, 100, 1, 1, 2);
                object[2] = createObject(img_eggpcU, 150, 80, 1, 1, 0);
                object[3] = createObject(img_eggpcU, 150, 60, 1, 1, 0);
                object[4] = createObject(img_eggpcU, 200, 50, 1, 1, 2);


            }else if(mapposx == 2 && mapposy == 0){
                newscreen = false;
                FntPrint("newroom");
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[1] = createImage(img_wallhorz, 0, 128, 6, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 200, 50, 1, 1, 2);
            }else if(mapposx == 1 && mapposy == 1){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                // wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_Fveggspr, 100, 100, 1, 1, 3);
                object[1] = createObject(img_eggpcU, 200, 100, 1, 1, 2);
                object[2] = createObject(img_eggpcU, 150, 80, 1, 1, 0);
                object[3] = createObject(img_eggpcU, 150, 60, 1, 1, 0);
                object[4] = createObject(img_eggpcU, 200, 50, 1, 1, 2);

            }else if(mapposx == 1 && mapposy == 2){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                wall[3] = createImage(img_wallhorz, 300, 0, 1, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 1 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                wall[3] = createImage(img_wallhorz, 300, 0, 1, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 1 && mapposy == 4){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                wall[3] = createImage(img_wallhorz, 300, 0, 1, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 1 && mapposy == 5){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                wall[3] = createImage(img_wallhorz, 300, 0, 1, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 1 && mapposy == 6){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 220, 0, 4, 2, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 220, 180, 4, 2, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 3 && mapposy == 1){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 3, 6, 0);
                wall[1] = createImage(img_wallhorz, 0, 128, 6, 6, 0);
                wall[2] = createImage(img_wallhorz, 290, 0, 1, 1, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 4 && mapposy == 1){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[1] = createImage(img_wallhorz, 0, 128, 6, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 1){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[1] = createImage(img_wallhorz, 0, 128, 6, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 6 && mapposy == 1){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[1] = createImage(img_wallhorz, 0, 128, 6, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 7 && mapposy == 1){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[1] = createImage(img_wallhorz, 0, 128, 6, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 8 && mapposy == 1){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 128, 3, 4, 0);
                wall[1] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[2] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 8 && mapposy == 2){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 0, 0, 6, 6, 0);
                wall[1] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 8 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 0, 3, 2, 0);
                wall[2] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 7 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 6 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 8 && mapposy == 5){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[1] = createImage(img_wallhorz, 0, 0, 6, 4, 0);
                wall[2] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 4 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[1] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 220, 180, 4, 2, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 4 && mapposy == 4){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 4 && mapposy == 5){
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 3 && mapposy == 6){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 2 && mapposy == 6){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 4 && mapposy == 6){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 0, 0, 3, 1, 0);
                wall[1] = createImage(img_wallhorz, 220, 0, 4, 2, 0);
                wall[2] = createImage(img_wallvert, 0, 180, 3, 1, 0);
                wall[3] = createImage(img_wallhorz, 220, 180, 4, 2, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 6){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 6 && mapposy == 6){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 7 && mapposy == 6){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallvert, 0, 180, 3, 1, 0);
                wall[2] = createImage(img_wallhorz, 220, 180, 4, 2, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 8 && mapposy == 6){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 0, 0, 3, 1, 0);
                wall[1] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 1 && mapposy == 7){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 7 && mapposy == 7){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 2 && mapposy == 8){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 3 && mapposy == 8){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 4 && mapposy == 8){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 180, 6, 3, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 1, 0);
                wall[2] = createImage(img_wallhorz, 220, 0, 4, 2, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
            }else if(mapposx == 5 && mapposy == 8){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 6 && mapposy == 8){
                newscreen = false;
                wall[0] = createImage(img_wallhorz, 0, 0, 6, 2, 0);
                wall[1] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 7 && mapposy == 8){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 0, 0, 3, 1, 0);
                wall[1] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 1 && mapposy == 8){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 1, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 180, 6, 2, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 4 && mapposy == 7){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 220, 0, 4, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 3, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                //wall[3] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }
            //Rooms
            else if(mapposx == 4 && mapposy == 0){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 0){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 6 && mapposy == 0){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 3 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 0 && mapposy == 7){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 3 && mapposy == 7){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 7){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 8 && mapposy == 8){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 8 && mapposy == 4){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 2){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 0, 0, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 6 && mapposy == 2){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 0, 0, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 300, 0, 1, 1, 0);
            }else if(mapposx == 4 && mapposy == 9){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 0, 0, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 9){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 0, 0, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 300, 0, 1, 1, 0);
            }else if(mapposx == 9 && mapposy == 1){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 9 && mapposy == 2){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 4){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 0, 0, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 6 && mapposy == 4){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 0, 0, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 0, 0, 0);
                object[0] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 300, 0, 1, 1, 0);
            }else if(mapposx == 5 && mapposy == 5){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 0, 0, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 6 && mapposy == 5){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 0, 0, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 0, 0, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 300, 0, 1, 1, 0);
            }else if(mapposx == 2 && mapposy == 9){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 3 && mapposy == 9){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }
            //Cells
            else if(mapposx == 0 && mapposy == 2){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_Fvsurge, 100, 90, 1, 1, 1); 
                object[1] = createObject(img_eggpcU, 200, 100, 1, 1, 2);
                object[2] = createObject(img_eggpcU, 150, 80, 1, 1, 0);
                object[3] = createObject(img_eggpcU, 150, 60, 1, 1, 0);
                object[4] = createObject(img_eggpcU, 200, 50, 1, 1, 2);
            }else if(mapposx == 0 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 0, 0, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 0 && mapposy == 4){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 0, 0, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 0 && mapposy == 5){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 0, 0, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 1, 6, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 0, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 0, 0, 1, 1, 0);
            }else if(mapposx == 2 && mapposy == 2){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 0, 0, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 300, 0, 1, 1, 0);
            }else if(mapposx == 2 && mapposy == 3){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 0, 0, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 300, 0, 1, 1, 0);
            }else if(mapposx == 2 && mapposy == 4){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 0, 0, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 300, 0, 1, 1, 0);
            }else if(mapposx == 2 && mapposy == 5){
                newscreen = false;
                wall[0] = createImage(img_wallvert, 290, 0, 1, 6, 0);
                wall[1] = createImage(img_wallvert, 0, 0, 0, 0, 0);
                wall[2] = createImage(img_wallhorz, 0, 0, 6, 1, 0);
                wall[3] = createImage(img_wallhorz, 0, 210, 6, 1, 0);
                object[0] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[1] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[2] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[3] = createObject(img_eggpcU, 300, 0, 1, 1, 0); 
                object[4] = createObject(img_eggpcU, 300, 0, 1, 1, 0);
            }
        }
        struct Point l1 = { vcream.ture.x, vcream.ture.y }, r1 = { vcream.ture.x+vcream.ture.w, vcream.ture.y+vcream.ture.h };
        for(a = 0; a <= 3; a++){
        struct Point l2 = { wall[a].ture.x, wall[a].ture.y }, r2 = { wall[a].ture.x+wall[a].ture.w, wall[a].ture.y+wall[a].ture.h }; 
            if (doOverlap(l1, r1, l2, r2)){
                //vcream = moveImage(vcream, posbeforex, posbeforey);
                //FntPrint(" overlap");
            }        
            
        }
        for(c = 0; c <= 5; c++){
        struct Point l2 = { object[c].ture.x, object[c].ture.y }, r2 = { object[c].ture.x+object[c].ture.w, object[c].ture.y+object[c].ture.h }; 
            if (doOverlap(l1, r1, l2, r2)){
                vcream = moveImage(vcream, posbeforex, posbeforey);
                //FntPrint(" X: %d Y: %d", object[c].ture.w, object[c].ture.h, "\n");
            }
        }
 
    }

}
    // if(animframe <= sizeof(vcreamsprcomputer)/4 && vcream.ture.x == posbeforex && vcream.ture.y == posbeforey){
    //         if(b == 100 || b == 0){    
                
    //             if (vcreamsprcomputer[animframe].id == 4){
                
    //                 vcream = changeImage(vcream, vcreamsprcomputer[animframe].x, vcreamsprcomputer[animframe].y);
    //                 animframe++;
    //             }
    //             else
    //                 vcream = changeImage(vcream, 0, 0);
    //         }
    //         if(b == 101){
    //             b = 0;
    //         }
    //         b++;

    //     } 

void drawd(void) {
    //drawLine(line);
    if(incomputer){
        drawImage(bootup);
    }
    else{
        for(a = 0; a <= 3; a++){
            drawImage(wall[a]);
        }

        for(c = 0; c <= 5; c++){
            drawObject(object[c]);
        }


        drawImage(vcream);
    }
}

int main() {
    init();
    while(1) {    
        clearDisplay();
        
        
        
        //FntPrint("Hello Cream!\n");   
        //FntPrint(" X: %d Y: %d", b, mapposy, "\n");
        FntFlush(-1);
        update();
        drawd();
        display();
    }
    return 0;
}
