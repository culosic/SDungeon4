#ifndef _DRAW_H_
#define _DRAW_H_

#include "base.h"
#include "c/map.h"
#include "exb.h"
#include "graphics.h"

void mapDraw(Map*map,int x,int y){
  int c = 100;
  int d = 20;
  int doorw = 10;
  int cd = c+d;
  int x0 = 0,y0 = 0;
  int top = 0,right = 0,bottom = 0,left = 0;
  int w = 0,h = 0;
  for(int i = 0;i<map->roomCount;i++){
    Room*room = map->roomList[i];
    int x = room->x;
    int y = room->y;
    if(i==0){
      top = y0 = y;
      right = x;
      bottom = y;
      left = x0 = x;
    }else{
      if(top>y)
      	top = y0 = y;
      if(right<x)
      	right = x;
      if(bottom<y)
      	bottom = y;
      if(left>x)
      	left = x0 = x;
    }
  }
  //printf("%d,%d,  %d, %dvvv%d,%d\n",left,top,right,bottom,x0,y0);
  w = (right+1-left)*cd-d;
  h = (bottom+1-top)*cd-d;
  x0 = (SCRW-w)/2-x0*cd;
  y0 = (SCRH-h)/2-y0*cd;
  for(int i = 0;i<map->roomCount;i++){
    Room*room = map->roomList[i];
    int x = x0+room->x*cd;
    int y = y0+room->y*cd;
    int32 bcolor = 0xffaa9933;
    drawRect(x,y,c,3,bcolor);
    drawRect(x+c-3,y,3,c,bcolor);
    drawRect(x,y+c-3,c,3,bcolor);
    drawRect(x,y,3,c,bcolor);
    drawRect(x+3,y+3,c-6,c-6,0xaa336699);
    switch(room->type){
      case Room_Init:
      drawTextC(room->caption,x,y,100,100,245,245,60,50);
      break;
      case Room_Boss:
      drawTextC(room->caption,x,y,100,100,245,60,60,50);
      break;
      default:
      drawTextC(room->caption,x,y,100,100,245,245,60,30);
      break;
    }
    //dline(SCRW/2,0,SCRW/2,SCRH,255,0,0);
    //dline(0,SCRH/2,SCRW,SCRH/2,255,0,0);
    
    Room*linkRoom = room->prevRoom;
    if(linkRoom == NULL){
    linkRoom = room->superRoom;
    }
    if(linkRoom!=NULL){
      //printf("(%d %d  ->  %d %d\n", room->x, room->y, linkRoom->x, linkRoom->y);
      if(room->x==linkRoom->x){
        if(room->y>linkRoom->y){
          drawRect(x+(c-doorw)/2,y-d,doorw,d,0xffaa9933);
        }else{
          drawRect(x+(c-doorw)/2,y+c,doorw,d,0xffaa9933);
        }
      }
      else if(room->y==linkRoom->y){
        if(room->x>linkRoom->x){
          drawRect(x-d,y+(c-doorw)/2,d,doorw,0xffaa9933);
        }else{
          drawRect(x+c,y+(c-doorw)/2,d,doorw,0xffaa9933);
        }
      }
    }
  }
}


#endif