
#include "breathe.h"
#include "common.h"
#include "sdl.h"
#include "phaseportrait.h"
#include <math.h>


void oscillate(double curA,double curB,double *outA, double *outB);

//should return current a and b!
int dofullscreen(SDL_Surface* pSurface, bool breathe, PhasePortraitSettings * settings, double *targetA, double *targetB)
{
	double curA=0.0, curB=0.0;

	SDL_Event event;
	double sliding = 10.0;
	

while (true)
{
	curA += (*targetA-curA)/sliding;
	curB += (*targetB-curB)/sliding;

	if ( SDL_PollEvent ( &event ) )
	{
	//an event was found
	if ( event.type == SDL_QUIT ) return 0;
	else if (event.type==SDL_MOUSEBUTTONDOWN) return 0;
	else if (event.type==SDL_KEYDOWN){
		
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: *targetB += (event.key.keysym.mod & KMOD_SHIFT) ? 0.0005 : 0.005; break;
			case SDLK_DOWN: *targetB -= (event.key.keysym.mod & KMOD_SHIFT) ? 0.0005 : 0.005; break;
			case SDLK_LEFT: *targetA -= (event.key.keysym.mod & KMOD_SHIFT) ? 0.0005 : 0.005; break;
			case SDLK_RIGHT: *targetA += (event.key.keysym.mod & KMOD_SHIFT) ? 0.0005 : 0.005; break;
			default: break;
		}
	  }
	else if (event.type==SDL_KEYUP)
	  {
		  if (event.key.keysym.sym==SDLK_LALT || event.key.keysym.sym==SDLK_RALT) {}
		  else if ((event.key.keysym.mod == 0) && event.key.keysym.sym!=SDLK_f) {return 0; break;}
		  //else ;
		/*switch(event.key.keysym.sym)
		{
			case SDLK_UP: break;
			case SDLK_DOWN: break;
			case SDLK_LEFT: break;
			case SDLK_RIGHT: break;
			case SDLK_f: break;
			case SDLK_RALT: break;
			case SDLK_LALT: break;
			case SDLK_RSHIFT: break;
			case SDLK_LSHIFT: break;
			
			case SDLK_SPACE:
			case SDLK_ESCAPE:
			case SDLK_RETURN: 
			case SDLK_F11: 
			case SDLK_BACKSPACE: 
			case SDLK_DELETE: 
			case SDLK_HOME: 
			case SDLK_q: 
				return 0; //return back to the other screen!
				break;
			 
			default: 
				//return 0; //return back to the other screen!
				break;
		}*/
	}
	}

	if (LockFramesPerSecond()) 
	{
		if (!breathe && VERYCLOSE(curA,*targetA) && VERYCLOSE(curB,*targetB))
		{
			// don't need to compute anything.
		}
		else
		{
			SDL_FillRect ( pSurface , NULL , g_white );  //clear surface quickly
			if (SDL_MUSTLOCK(pSurface)) SDL_LockSurface ( pSurface ) ;
			if (breathe)
			{
				double oa, ob;
				oscillate(curA, curB, &oa, &ob);
				DrawPhasePortrait(pSurface, settings, oa,ob);
			}
			else
			{
				DrawPhasePortrait(pSurface, settings, curA,curB);
			}
			if (SDL_MUSTLOCK(pSurface)) SDL_UnlockSurface ( pSurface ) ;
		}
		


	}

	SDL_UpdateRect ( pSurface , 0 , 0 , 0 , 0 ) ;  //apparently needed every frame, even when not redrawing

}
return 0;
}

void oscillate(double curA,double curB,double *outA, double *outB)
{
	static double statePos=0.0, stateFreq=0.0;
	if (statePos>31.415926) statePos=0.0;
	if (stateFreq>31.415926) stateFreq=0.0;
	stateFreq+=0.01;
	statePos+=stateFreq;

	//the frequency itself oscillates
	double oscilFreq = 0.09 + sin(stateFreq)/70;
	*outA = curA+ sin(statePos*.3702342521232353)/550;
	*outB = curB+ cos(statePos)/400; 
}
int fullscreen(SDL_Surface* pSurface, bool breathe, PhasePortraitSettings * settings, double *ptrtargetA, double *ptrtargetB)
{
	int prev = settings->width;
	settings->width = settings->height = 600;
	int ret = dofullscreen(pSurface, breathe, settings, ptrtargetA, ptrtargetB);
	settings->width = settings->height = prev;
	return ret;
}