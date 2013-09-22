#ifndef WIN_HIGHGUI_H
# define WIN_HIGHGUI_H

# include <string>
# include <vector>

# include "cv.h"
# include "highgui.h"
# include "win.h"

#define CONV_WINIMPL( W ) ((WinImpl*)W)

class WinImpl {
	private:
		static std::vector< WinImpl* > winList;

		std::vector< cv::Mat > canvasList;
		cv::Mat canvas;
		cv::Scalar canvasColor;
		std::string windowName;
		cv::Point position;

	public:
    	WinImpl();                                          //  コンストラクタ
    	~WinImpl();                       //  デストラクタ
    	void    open ( char* wn, int x, int y, const Color& c );//ウインドウを開く
    	void    color( const Color& c);                         //  描画色の設定
    	void    point(int x, int y);                    //  点を描画する
    	const Color pixel(int x, int y) const;                    //  描画色を返す    
    	void    move (int x, int y);                    //  カーソルを移動する
    	void    line (int x, int y);                    //  線分を描画する
    	void    line (int a[], int n);                  //  複数線分を描画する  
    	void    paint(int a[], int n);                  //  点の描画
    	int     gprintf(char *format,...);
    	void    read (char *wn, char *fn);              //  ファイルから画像を読込む
    	void    read (char *fn){	read(fn,fn);	}   //  ファイルから画像を読込む
    	void    write(char *fn);
    	void    clear(int to=500);                      //  描画領域をクリアする
    	void    close();                                //  ウインドウを閉じる

 		void	plane(int n);
    	void	active(int n);
    	void	visual(int n);
    	//void	flush();
    	//void	copy(int s);
    	//void	copy(int d, int s);

    	//void    mouse(char& b, int& x, int& y);
    	void    size(int& x, int& y);
    	void    show();

    	//static	void to_lock();
    	//static	void to_lock_wait(); 
    	//static	void to_release(); 
    	//static	void to_redraw();
    	//static	void to_accept();						//  timeout
    	//static	void to_flush();						//	
    	//static	void to_restart();						//  timer restart
		static  void showAll();
};

void 	pause_impl(char *txt="ＯＫで終了します！");			//  一時停止(ボタン入力待ち関数)
void 	message_dialog_impl(char *message);
#endif WIN_HIGHGUI_H
