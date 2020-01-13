#include "color.h"
#include <math.h>


float min (float a, float b) {
	if (a > b)
		return b;
	return a;
}

float max (float a, float b) {
	if (a > b)
			return a;
	return b;
}

/*
 * Algorithm adapted from https://gist.github.com/hdznrrd/656996. Uses a little libmath.
 * */
void color_HSV2RGB(struct color_ColorHSV const *hsv, struct color_ColorRGB *rgb) {
   int i;
   float f,p,q,t;
   float h, s, v;

   //expand the u8 hue in range 0->255 to 0->359* (there are problems at exactly 360)
   h = 359.0 * ((float)hsv->h / 255.0);

   h = max(0.0, min(360.0, h));
   s = max(0.0, min(100.0, hsv->s));
   v = max(0.0, min(100.0, hsv->v));

   s /= 100;
   v /= 100;

   if(s == 0) {
      // Achromatic (grey)
      rgb->r = rgb->g = rgb->b = round(v*255);
      return;
   }

   h /= 60; // sector 0 to 5
   i = floor(h);
   f = h - i; // factorial part of h
   p = v * (1 - s);
   q = v * (1 - s * f);
   t = v * (1 - s * (1 - f));
   switch(i) {
      case 0:
         rgb->r = round(255*v);
         rgb->g = round(255*t);
         rgb->b = round(255*p);
         break;
      case 1:
         rgb->r = round(255*q);
         rgb->g = round(255*v);
         rgb->b = round(255*p);
         break;
      case 2:
         rgb->r = round(255*p);
         rgb->g = round(255*v);
         rgb->b = round(255*t);
         break;
      case 3:
         rgb->r = round(255*p);
         rgb->g = round(255*q);
         rgb->b = round(255*v);
         break;
      case 4:
         rgb->r = round(255*t);
         rgb->g = round(255*p);
         rgb->b = round(255*v);
         break;
      default: // case 5:
         rgb->r = round(255*v);
         rgb->g = round(255*p);
         rgb->b = round(255*q);
   }
}
