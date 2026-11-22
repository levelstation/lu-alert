#ifndef MESHCORE_LU_ALERT_RENDERER_H
#define MESHCORE_LU_ALERT_RENDERER_H
#pragma once
#include <stdint.h>
#include "LuAlertBitmap.h"
namespace lu_alert {
static constexpr uint16_t bitmapBytes=160;
inline bool pixel(int x,int y){return x>=0 && x<32 && y>=0 && y<40 && (lion[y*4+x/8]&(0x80u>>(x&7)));}
template<class Display> bool render(Display& d,uint16_t elapsed){
  // Completion holds this identity; never display a different branding here.
  const uint16_t t=elapsed>=2500?2100:(elapsed/100)*100;
  if(t<100)return true;
  d.setColor(1);
  for(int y=0;y<40;++y)for(int x=0;x<32;++x){
    if(!pixel(x,y))continue;
    if(y<8 && (t<1100 || (t>=1500 && t<1600)))continue;
    const bool edge=!pixel(x-1,y)||!pixel(x+1,y)||!pixel(x,y-1)||!pixel(x,y+1);
    if(t<500 && (!edge || y>8+(int(t)-100)*32/400))continue;
    if(t>=500 && t<1000 && !edge && y>8+(int(t)-500)*32/500)continue;
    d.fillRect(34+x,7+y,1,1);
  }
  d.setTextSize(2);
  if(t>=700){d.setCursor(0,22);d.print("LU");}
  if(t>=1000){d.setCursor(66,22);d.print("Alert");}
  if(t>=1200){
    const int rings=t>=1800?3:1+(t-1200)/200;
    for(int ring=0;ring<rings && ring<3;++ring){
      const int radius=8+3*ring,base=30-3*ring;
      for(int delta=-radius;delta<=radius;++delta){
        const int a=delta<0?-delta:delta;
        const int bend=a>radius*3/4?2:a>radius/3?1:0;
        d.fillRect(base+bend,27+delta,1,1);
      }
    }
  }
  d.setTextSize(1);
  if(t>=1800)d.drawTextCentered(64,55,"Meshcore Luxembourg");
  return true;
}
}

#endif
