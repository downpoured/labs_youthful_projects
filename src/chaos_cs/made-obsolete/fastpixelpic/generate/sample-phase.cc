
[code]
#define MAPEXPRESSION x_ = c1*x - y*y; y_ = c2*y + x*y;
#define DRAWING 4000
void OnSetup(int width)
{
	int height=width;
	if (!g_arr || width!=g_arr_size) { if(g_arr)free(g_arr); g_arr=(int*)malloc(sizeof(int)*width*height); }
	double c1= g_settings->pc1,c2= g_settings->pc2;
	memset(g_arr, 0, sizeof(int)*width*height); 
	int SETTLE = 10; 
	int nXpoints=30, nYpoints=30;
	//~ int nXpoints=4, nYpoints=4;
	
	double sx0i= -0.1, sx1i=0.1, sy0i=-0.1, sy1i=0.1; //TMP
	//keep higher one.
	double sx0=MIN(sx0i,sx1i), sx1=MAX(sx0i,sx1i),sy0=MIN(sy0i,sy1i), sy1=MAX(sy0i,sy1i);
	double sxinc = (nXpoints==1 || sx1-sx0==0) ? 1e6 : (sx1-sx0)/(nXpoints-1);
	double syinc = (nYpoints==1 || sy1-sy0==0) ? 1e6 : (sy1-sy0)/(nYpoints-1);
	double x_,y_,x,y;
	double X0=g_settings->x0, X1=g_settings->x1, Y0=g_settings->y0, Y1=g_settings->y1;

	// if basin of attraction is smaller, will be fainter, but that's ok.
	for (double sx=sx0; sx<=sx1; sx+=sxinc)
	{
	for (double sy=sy0; sy<=sy1; sy+=syinc)
	{
		x = sx; y=sy;

		for (int ii=0; ii<SETTLE/4; ii++)
		{
			MAPEXPRESSION;x=x_;y=y_; MAPEXPRESSION;x=x_;y=y_;
			MAPEXPRESSION; x=x_;y=y_;MAPEXPRESSION;x=x_;y=y_;
			if (ISTOOBIG(x)||ISTOOBIG(y)) break;
		}
		for (int ii=0; ii<DRAWING; ii++)
		{
			MAPEXPRESSION;x=x_;y=y_;
			if (ISTOOBIG(x)||ISTOOBIG(y)) break;

			int px = (int)(width * ((x - X0) / (X1 - X0)));
			int py = (int)(height * ((y - Y0) / (Y1 - Y0)));
			if (py >= 0 && py < height && px>=0 && px<width)
				g_arr[py*width+px]++;
		}
	}
	}
}


//$$standardloop


double X0=g_settings->x0, X1=g_settings->x1, Y0=g_settings->y0, Y1=g_settings->y1;
	int px = (int)(width * ((fx - X0) / (X1 - X0)));
	int py = (int)(height * ((fy - Y0) / (Y1 - Y0)));
	if (py >= 0 && py < height && px>=0 && px<width)
	{
		/*double val = ((double)g_arr[py*width+px]);
		if (val>DRAWING) val=DRAWING;
		int v= 255-(int)(255*((val)/((double)DRAWING)));*/
		double val = (sqrt((double)g_arr[py*width+px])) / (sqrt((double)DRAWING)); 
		//each could have been hit many times
		//	actually, drawing * nseeds * nseeds would be factor
		
		if (val>1.0) val=1.0; 
		int v = 255-(int)(val*255);
		return SDL_MapRGB(pSurface->format, v,v,v);
		//~ if (g_arr[py*width+px] > 1)
			//~ return SDL_MapRGB(pSurface->format, 80,0,0); //
		//~ else
			//~ return SDL_MapRGB(pSurface->format, 255,255,255); //
	}
	return SDL_MapRGB(pSurface->format, 80,0,0); //unreached

//$$endstandardloop

[params]



latest=dict(pc1=0.130000, pc2=0.090000, 
	
	x0=-2.000000, x1=2.000000, y0=-2.000000, y1=2.000000, diagram_a_x0=-2.000000, diagram_a_x1=2.000000, diagram_a_y0=-2.000000, diagram_a_y1=2.000000, diagram_b_x0=-2.000000, diagram_b_x1=2.000000, diagram_b_y0=-2.000000, diagram_b_y1=2.000000, diagram_c_x0=-2.000000, diagram_c_x1=2.000000, diagram_c_y0=-2.000000, diagram_c_y1=2.000000, 
	colorMode=0, colorWrapping=0, maxValueAddition=0.000000, hueShift=0.000000, 
	settling=10, drawing=10, breatheRadius_c1c2=1.000000, )