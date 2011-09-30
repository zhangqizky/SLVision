////#include "StdAfx.h"
#include "Globals.h"

IplImage*	Globals::screen						= NULL;
IplImage*	Globals::captured_image				= NULL;
CvCapture*	Globals::cv_camera_capture			= NULL;
IplImage*	Globals::main_image					= NULL;	
IplImage*	Globals::thresholded_image_marker	= NULL;
IplImage*	Globals::fiducial_image_marker		= NULL;
bool		Globals::is_view_enabled			= false;

float		Globals::Font::hscale				= 0.5f;
float		Globals::Font::vscale				= 0.5f;
float		Globals::Font::italicscale			= 0.0f;
int 		Globals::Font::thickness			= 1;
float		Globals::Font::axis_hscale			= 0.8f;
float		Globals::Font::axis_vscale			= 0.8f;
CvFont		Globals::Font::font_info;
CvFont		Globals::Font::font_axis;

int			Globals::width						= 0;
int			Globals::height						= 0;
char		Globals::dim[100];

char*		Globals::address					= "127.0.0.1";//"10.80.7.19";//
int			Globals::port						= 3333;

CvMat* 		Globals::intrinsic					= NULL;
CvMat*		Globals::distortion					= NULL;


int			Globals::screen_to_show				= 0;
void Globals::SetView(int view)
{
	if(view < 0 || view >= VIEW_NONE)
	{
		screen_to_show = VIEW_NONE;
		is_view_enabled = false;
	}
	else
	{
		screen_to_show = view;
		is_view_enabled = true;
		if(screen_to_show == VIEW_RAW)
			screen = main_image;
		else if(thresholded_image_marker != NULL && screen_to_show == VIEW_THRESHOLD)
			Globals::screen = thresholded_image_marker;
	}
}

void Globals::SwitchScreen()
{
	screen_to_show ++;
	if(screen_to_show > VIEW_NONE) screen_to_show = 0;
		SetView(screen_to_show);
}

void Globals::Font::InitFont()
{
	hscale      = 0.5f;
	vscale      = 0.5f;
	italicscale = 0.0f;
	thickness   = 1;
	axis_hscale = 0.8f;
	axis_vscale = 0.8f;
	cvInitFont (&font_info, CV_FONT_HERSHEY_SIMPLEX , hscale, vscale, italicscale, thickness, CV_AA);
	cvInitFont (&font_axis, CV_FONT_HERSHEY_SIMPLEX , axis_hscale, axis_vscale, italicscale, thickness, CV_AA);
}

void Globals::Font::Write(IplImage* dest, char* text, const CvPoint &position, int font_type, short r, short g, short b)
{
	if(dest != NULL && text != NULL)
	{
		switch(font_type)
		{
			case FONT_AXIS:
				cvPutText(dest, text, position, &font_axis,CV_RGB(r,g,b));
			break;
			default:
			case FONT_HELP:
				cvPutText(dest, text, position, &font_info,CV_RGB(r,g,b));
			break;
		}
	}
}