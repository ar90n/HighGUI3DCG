#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>

#include "win_highgui.h"

std::vector< WinImpl* > WinImpl::winList = std::vector< WinImpl* >();

WinImpl::WinImpl()
{
	canvas = cv::Mat::zeros( 0, 0, CV_32FC3 );
	canvasColor = cv::Scalar( 0.0f, 0.0f, 0.0f );
	windowName = std::string( "" );
	position = cv::Point( 0, 0 );
}

WinImpl::~WinImpl()
{
}

void WinImpl::open( char* wn, int x, int y, const Color& c )
{
	windowName = std::string( wn );
	canvas = cv::Mat( y, x, CV_32FC3 );
	color( c );

	canvas = canvasColor;
	
	canvasList.push_back( canvas );
	winList.push_back( this );
}

void WinImpl::color( const Color& c )
{
	canvasColor =  cv::Scalar( c.b, c.g, c.r, 1.0f );
}

void WinImpl::point( int x, int y )
{
	CV_Assert( 0 <= y && y < canvas.rows );
	CV_Assert( 0 <= x && x < canvas.cols );

	cv::Point beg = cv::Point( x, y );
	cv::Point end = cv::Point( x, y );
	cv::line(  canvas, beg, end, canvasColor );
}

const Color WinImpl::pixel( int x, int y ) const
{
	y = std::max( std::min( y, canvas.rows ), 0 );
	x = std::max( std::min( x, canvas.cols ), 0 );

	cv::Vec3f tmpPixel = canvas.at< cv::Vec3f >( y, x );

	Color tmpColor = Color( tmpPixel[2], tmpPixel[1], tmpPixel[0] );
	return tmpColor;
}

void WinImpl::move( int x, int y )
{
	CV_Assert( 0 <= y && y < canvas.rows );
	CV_Assert( 0 <= x && x < canvas.cols );

	position = cv::Point( x, y );
}

void WinImpl::line( int x, int y )
{
	CV_Assert( 0 <= y && y < canvas.rows );
	CV_Assert( 0 <= x && x < canvas.cols );

	cv::Point destination = cv::Point( x, y );
	cv::line(  canvas, position, destination, canvasColor );
	move( x, y );
}

void WinImpl::line( int a[], int n )
{
	cv::Point tmpPosition = position;

	if( n < 2 )
	{
		return;
	}

	move( a[0], a[1] );
	for( int i = 1; i < n; i++ ) 
	{
		int x = a[ 2 * i ];
		int y = a[ 2 * i + 1 ];

		line( x, y );
		move( x, y );
	}

	move( tmpPosition.x, tmpPosition.y );
}

#define		sup(p1,p2,a1,a2)	((a1+a2==0)?p1:((a2)*p1+(a1)*p2)/(a1+a2))	//	p1,p2を補間する
void WinImpl::paint( int a[], int n )
{
	int yMin = a[1];
	int yMax = a[1];
	int leftTopIndex = 0;
	int rightTopIndex = 0;

	for( int i = 0; i < n; ++i )
	{
		int y = a[ 2 * i + 1 ];
		if( y < yMin )
		{
			yMin = y;
			leftTopIndex = i;
			rightTopIndex = i;
		}
		else if( yMin == y )
		{
			rightTopIndex = i;
		}

		yMax = std::max( yMax, y );
	}
	
	for( int y = yMin; y <= yMax; ++y )
	{
		int nextLeftTopIndex = ( leftTopIndex + 1 ) % n;
		int nextRightTopIndex = ( rightTopIndex - 1 + n ) % n;

		if( a[ nextLeftTopIndex * 2 + 1 ] < y )
		{
			leftTopIndex = nextLeftTopIndex;
		}

		if( a[ nextRightTopIndex * 2 + 1 ] < y )
		{
			rightTopIndex = nextRightTopIndex;
		}

		int leftBottomIndex = ( leftTopIndex + 1 ) % n;
		int rightBottomIndex = ( rightTopIndex - 1 + n ) % n;
		int leftTopX = a[ leftTopIndex * 2 + 0 ];
		int leftTopY = a[ leftTopIndex * 2 + 1 ];
		int leftBottomX = a[ leftBottomIndex * 2 + 0 ];
		int leftBottomY = a[ leftBottomIndex * 2 + 1 ];
		int rightTopX = a[ rightTopIndex * 2 + 0 ];
		int rightTopY = a[ rightTopIndex * 2 + 1 ];
		int rightBottomX = a[ rightBottomIndex * 2 + 0 ];
		int rightBottomY = a[ rightBottomIndex * 2 + 1 ];

		int xMin;
		int xMax;
		int a1 = y - leftTopY;
		int b1 = y - rightTopY;
		int a2 = leftBottomY - y;
		int b2 = rightBottomY - y;
		xMax = sup( rightTopX, rightBottomX, b1, b2 );
		xMin = sup( leftTopX, leftBottomX, a1, a2 );

		for( int x = xMin; x <= xMax; ++x )
		{
			point( x, y );
		}
	}
}
#undef		sup(p1,p2,a1,a2)

int WinImpl::gprintf( char *format, ... )
{
	va_list arg;
	int n;
	char buf[ 4096 ];

	va_start( arg, format );
	n = vsprintf( buf, format, arg );
	va_end( arg );

	std::string tmpText = std::string( buf );
	cv::putText( canvas, tmpText, position, cv::FONT_HERSHEY_SIMPLEX, 1.0f, canvasColor );

	return n;
}

void WinImpl::read( char *wn, char *fn )
{
	windowName = std::string( wn );

	cv::Mat tmpImage = cv::imread( fn );

	canvas = cv::Mat( tmpImage.size(), CV_32FC3 );
	tmpImage.convertTo( canvas, CV_32FC3 );
	canvas /= 255.0;

	canvasList.push_back( canvas );
	winList.push_back( this );
}

void WinImpl::write( char *fn )
{
	cv::Mat cvtImage = cv::Mat( canvas.size(), CV_8UC3 );
	cv::Mat scaledImage = 255.0 * canvas;
	scaledImage.convertTo( cvtImage, CV_8UC3 );
	
	imwrite( fn, cvtImage );
}

void WinImpl::close()
{
}

void WinImpl::plane( int n )
{
	CV_Assert( 0 < n );

	for( int i = 0; i < ( n - canvasList.size() ); ++i )
	{
		cv::Mat tmpCanvas = cv::Mat( canvas.size(), CV_32FC3 );
		canvasList.push_back( tmpCanvas );
	}
}

void WinImpl::active( int n )
{
	CV_Assert( n < canvasList.size() );

	canvas = canvasList[ n ];
}

void WinImpl::visual( int n )
{
	CV_Assert( n < canvasList.size() );

	cv::imshow( windowName, canvasList[ n ] );
}

void WinImpl::size( int& x, int& y )
{
	cv::Size size = canvas.size();
	x = size.width;
	y = size.height;
}

void WinImpl::show()
{
	cv::namedWindow( windowName.c_str(), 1 );
	cv::imshow( windowName.c_str(), canvas );
}

void WinImpl::showAll()
{
	std::vector< WinImpl* >::iterator it = WinImpl::winList.begin();
	while( it != WinImpl::winList.end() )
	{
		(*it)->show();
		++it;
	}
}

void pause_impl( char *txt )
{
	std::cout << txt << std::endl;
	WinImpl::showAll();
	cv::waitKey();
}

void message_dialog_impl( char *message )
{
	std::cout << message << std::endl;
}
