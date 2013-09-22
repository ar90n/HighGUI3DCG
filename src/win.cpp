#include <iostream>
#include <math.h>

#include "win.h";
#include "win_highgui.h"
#include "cv.h"

int Win::num_win = 0;

Color::Color(float ir,float ig,float ib)
{
	r = ir;
	g = ig;
	b = ib;
}

Color::Color()
{
	r = g = b = 0.0f;
}

Color operator*( float a, Color c )
{
	Color tmp = Color( a * c.r, a * c.g, a * c.b );
	return tmp;
}

Color operator*( Color c, float a)
{
	return operator*( a, c );
}

Color operator*( Color c, Color d)
{
	Color tmp = Color( c.r * d.r, c.g * d.g, c.b * d.b );
	return tmp;
}

Color operator/( Color c, float a )
{
	Color tmp;
	if( abs( a ) < 1e-12 ) {
		tmp = Color( INFINITY, INFINITY, INFINITY );
	}
	else {
		tmp = Color( c.r / a, c.g / a, c.b / a );
	}
	return tmp;
}

Color operator+( Color a, Color b )
{
	Color tmp = Color( a.r + b.r, a.g + b.g, a.b + b.b );
	return tmp;
}

Color operator-( Color a, Color b )
{
	Color tmp = Color( a.r - b.r, a.g - b.g, a.b - b.b );
	return tmp;
}


Win::Win()
{
	w = NULL;
	w = ( void* )new WinImpl();
}

void Win::open( char* wn, int x, int y, Color c )
{
	num_win++;

	wi = x;
	hi = y;
	CONV_WINIMPL(w)->open( wn, x, y, c );
}

void Win::color( Color c )
{
	CONV_WINIMPL(w)->color( c );
}

void Win::point( int x, int y )
{
	CONV_WINIMPL(w)->point( x, y );
}

Color Win::pixel( int x, int y )
{
	return CONV_WINIMPL(w)->pixel( x, y );
}

void Win::move( int x, int y )
{
	CONV_WINIMPL(w)->move( x, y );
}

void Win::line( int x, int y )
{
	CONV_WINIMPL(w)->line( x, y );
}

void Win::line( int a[], int n )
{
	CONV_WINIMPL(w)->line( a, n );
}

void Win::paint( int a[], int n )
{
	CONV_WINIMPL(w)->paint( a, n );
}

int Win::gprintf( char *format, ... )
{
	va_list arg;

	va_start( arg, format );
	int n = CONV_WINIMPL(w)->gprintf( format, arg );
	va_end( arg );

	return n;
}

void Win::read( char *wn, char *fn )
{
	CONV_WINIMPL(w)->read( wn , fn );
	CONV_WINIMPL(w)->size( wi, hi );
}

void Win::write( char *fn )
{
	CONV_WINIMPL(w)->write( fn );
}

void Win::clear( int to )
{
}

void Win::close()
{
	if( w != NULL )
	{
		delete CONV_WINIMPL(w);
		w = NULL;
	
		num_win--;
	}
}

void Win::plane( int n )
{
	CONV_WINIMPL(w)->plane( n );
}

void Win::active( int n )
{
	CONV_WINIMPL(w)->active( n );
}

void Win::visual( int n )
{
	CONV_WINIMPL(w)->visual( n );
}

void pause( char *txt )
{
	pause_impl( txt );
}

void message_dialog( char *message )
{
	message_dialog_impl( message );
}
