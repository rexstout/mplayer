/* This file (C) Mark Zealey <mark@zealos.org> 2002, released under GPL */

#include <stdio.h>
#include <string.h>
#include "geometry.h"
#include "../mp_msg.h"

/* A string of the form [WxH][+X+Y] or xpos[%]:ypos[%] */
char *vo_geometry = NULL;

#define RESET_GEOMETRY width = height = xoff = yoff = xper = yper = -1;

// xpos,ypos: position of the left upper corner
// widw,widh: width and height of the window
// scrw,scrh: width and height of the current screen 
int geometry(int *xpos, int *ypos, int *widw, int *widh, int scrw, int scrh)
{
        int width, height, xoff, yoff, xper, yper;

	width = height = xoff = yoff = xper = yper = -1;

        if(vo_geometry != NULL) {
		if(sscanf(vo_geometry, "%ix%i+%i+%i", &width, &height, &xoff, &yoff) != 4 )
		{
		 RESET_GEOMETRY
		 if(sscanf(vo_geometry, "%ix%i", &width, &height) != 2)
		 {
		  RESET_GEOMETRY
		  if(sscanf(vo_geometry, "+%i+%i", &xoff, &yoff) != 2)
		  {
		   RESET_GEOMETRY
		   if(sscanf(vo_geometry, "%i:%i", &xoff, &yoff) != 2)
		   {
		    RESET_GEOMETRY
		    if(sscanf(vo_geometry, "%i:%i%%", &xper, &yper) != 2)
		    {
		     RESET_GEOMETRY
		     if(sscanf(vo_geometry, "%i%%:%i", &xper, &yper) != 2)
		     {
		     RESET_GEOMETRY
		     if(sscanf(vo_geometry, "%i%%:%i%%", &xper, &yper) != 2)
		     {
		      RESET_GEOMETRY
		      if(sscanf(vo_geometry, "%i%%", &xper) != 1)
		      {
			mp_msg(MSGT_VO, MSGL_ERR,
			    "-geometry must be in [WxH][+X+Y] | [X[%%]:[Y[%%]]] format, incorrect (%s)\n", vo_geometry);
			return 0;
		      }
		     }
		    }
		   }
		  }
		 }
		}
	       }

		mp_msg(MSGT_VO, MSGL_V,"geometry set to width: %i,"
		  "height: %i, xoff: %i, yoff: %i, xper: %i, yper: %i\n",
		  width, height, xoff, yoff, xper, yper);
		  
		if(xper >= 0 && xper <= 100) xoff = (scrw - *widw) * ((float)xper / 100.0);
		if(yper >= 0 && yper <= 100) yoff = (scrh - *widh) * ((float)yper / 100.0);

		mp_msg(MSGT_VO, MSGL_V,"geometry set to width: %i,"
		  "height: %i, xoff: %i, yoff: %i, xper: %i, yper: %i\n",
		  width, height, xoff, yoff, xper, yper);
		mp_msg(MSGT_VO, MSGL_V,"geometry window parameter: widw: %i,"
		  " widh: %i, scrw: %i, scrh: %i\n",*widw, *widh, scrw, scrh);
		  
		/* FIXME: better checking of bounds... */
		if(width < 0 || width > scrw) width = (scrw < *widw) ? scrw : *widw;
		if(height < 0 || height > scrh) height = (scrh < *widh) ? scrh : *widh;
		if(xoff < 0 || xoff + width > scrw) xoff = 0;
		if(yoff < 0 || yoff + height > scrh) yoff = 0;

		if(xpos) *xpos = xoff;
		if(ypos) *ypos = yoff;
		if(widw) *widw = width;
		if(widh) *widh = height;
        }
	return 1;
}

#undef RESET_GEOMETRY
