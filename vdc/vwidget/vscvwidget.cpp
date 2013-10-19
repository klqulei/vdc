#include "vscvwidget.h"
#include "factory.hpp"
#include "ffmpeg_scale.hpp"
#include "tcmalloc.h"
#include <QResizeEvent>
#include <QMimeData>
#include <QDrag>
#include <QAction>
#include <QDesktopWidget>
#include <QApplication>
#include <QDateTime>
#include <QTime>
#include <time.h>

extern Factory *gFactory;
#define ENABLE_OSD_SDL_TTF 0

VSCVWidget::VSCVWidget(s32 nId, QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    m_pStarted = FALSE;
    m_nId = nId;
    m_nPlayId = 0;
    m_pRenderBuffer = NULL;
    m_bDeviceDeleted = FALSE;
    m_bFocus = FALSE;
#if 0
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        puts("# error initializing SDL");
        puts(SDL_GetError());
        return ;
    }
#endif
    if ( TTF_Init() < 0 ) 
    {
        fprintf(stderr, "Couldn't initialize TTF: %s\n",  SDL_GetError());
        //SDL_Quit();
        return;
    }
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);
    
    m_Scale = new FFmpegScale;
    m_Scale->SetAttribute(SWS_PF_RGB24, SWS_PF_RGB24, SWS_SA_FAST_BILINEAR);

    m_SdlWin = SDL_CreateWindowFrom((void *)this->winId());
    /*  0 stand for direct3d */
    m_SdlRender = SDL_CreateRenderer(m_SdlWin, 0, 
        0);
    m_w = width();
    m_h = height();
    m_w = (m_w/4) * 4;
    m_h = (m_h/4) * 4;
    m_pTex = SDL_CreateTexture(m_SdlRender, SDL_PIXELFORMAT_RGB24, 
        SDL_TEXTUREACCESS_STREAMING, m_w, m_h);
   //SDL_SetRenderDrawColor(m_SdlRender, 85, 255, 0, 255);

   m_pRenderBuffer = (unsigned char *)malloc(m_w * m_h * 3);
   
   m_pFont = NULL;
   InitFont();
   RenderBlack();
   UpdateFontSurface();
   
   //SDL_SetRenderDrawBlendMode(m_SdlRender, SDL_BLENDMODE_NONE);

    this->setAcceptDrops(true);

    m_pStop = new QAction(QIcon(tr("images/open.ico")), tr("Stop"), this);
    connect(m_pStop, SIGNAL(triggered()), this, SLOT(stopAction()));
    m_pStop->setEnabled(false);

    m_pFloating = new QAction(QIcon(tr("images/open.ico")), tr("Float"), this);
    connect(m_pFloating, SIGNAL(triggered()), this, SIGNAL(ShowFloatingClicked()));

    m_pTabbed = new QAction(QIcon(tr("images/open.ico")), tr("Tabbed Document"), this);
    connect(m_pTabbed, SIGNAL(triggered()), this, SIGNAL(ShowTabbedClicked()));

    m_pDisplay1 = new QAction(QIcon(tr(":/action/resources/display.png")), tr("DISPLAY1"), this);
    connect(m_pDisplay1, SIGNAL(triggered()), this, SLOT(showDisplay1()));

    m_pDisplay2 = new QAction(QIcon(tr(":/action/resources/display.png")), tr("DISPLAY2"), this);
    connect(m_pDisplay2, SIGNAL(triggered()), this, SLOT(showDisplay2()));

    m_pDisplay3 = new QAction(QIcon(tr(":/action/resources/display.png")), tr("DISPLAY3"), this);
    connect(m_pDisplay3, SIGNAL(triggered()), this, SLOT(showDisplay3()));

    m_pDisplay4 = new QAction(QIcon(tr(":/action/resources/display.png")), tr("DISPLAY4"), this);
    connect(m_pDisplay4, SIGNAL(triggered()), this, SLOT(showDisplay4()));
    createContentMenu();

    /* Start idle thread */
    m_IdleThread = new tthread::thread(VSCVWidget::RunIdle, (void *)this);
}

VSCVWidget::~VSCVWidget()
{
    VDC_DEBUG( "%s ~VSCVWidget id %d\n",__FUNCTION__,
            m_nId);
    StopPlay();
    if (m_pStarted != TRUE)
    {
        m_pStarted = TRUE;
        m_IdleThread->join();
        delete m_IdleThread;
        m_IdleThread = NULL;
    }
}

void VSCVWidget::dragEnterEvent(QDragEnterEvent *event)
{
    VDC_DEBUG( "%s Event %s id %d\n",__FUNCTION__,
            event->mimeData()->text().toLatin1().data(),
            m_nId);
    event->acceptProposedAction();
    QWidget::dragEnterEvent(event);
}
void VSCVWidget::dropEvent(QDropEvent *event)
{
    VDC_DEBUG( "%s Enter in dropEvent id %d\n",__FUNCTION__, m_nId);
    if (m_pStarted == TRUE)
    {
        return;
    }

    m_nPlayId = atoi(event->mimeData()->text().toLatin1().data());
    StopPlay();
    StartPlay("fake");

    VDC_DEBUG( "%s Enter in dropEvent Play %d\n",__FUNCTION__, m_nPlayId);
}

void VSCVWidget::stopAction()
{
    StopPlay();
}

void VSCVWidget::showDisplay1()
{
    emit ShowDisplayClicked(0);
}
void VSCVWidget::showDisplay2()
{
    emit ShowDisplayClicked(1);
}
void VSCVWidget::showDisplay3()
{
    emit ShowDisplayClicked(2);
}

void VSCVWidget::showDisplay4()
{
    emit ShowDisplayClicked(3);
}

BOOL VSCVWidget::SetPlayId(u32 nPlayId)
{
    m_nPlayId = nPlayId;
    VDC_DEBUG( "%s Set Player ID %d\n",__FUNCTION__, m_nPlayId);
    return true;
}

BOOL VSCVWidget::StartPlay(std::string strUrl)
{
    m_UpdateSize = false;
    m_pStarted = TRUE;
    m_bDeviceDeleted = FALSE;
    m_IdleThread->join();
    delete m_IdleThread;
    m_IdleThread = NULL;
    UpdateFontSurface();
    m_SdlThread = new tthread::thread(VSCVWidget::Run, (void *)this);
    m_pStop->setEnabled(true);
    return TRUE;
}

void VSCVWidget::createContentMenu()
{
    QDesktopWidget *desktop = QApplication::desktop();
    this->addAction(m_pStop);
    this->addAction(m_pFloating);
    this->addAction(m_pTabbed);

    int screenCnt = desktop->screenCount();
    if (screenCnt == 1)
    {
        this->addAction(m_pDisplay1);
    }else if (screenCnt == 2)
    {
        this->addAction(m_pDisplay1);
        this->addAction(m_pDisplay2);
    }else if (screenCnt == 3)
    {
        this->addAction(m_pDisplay1);
        this->addAction(m_pDisplay2);
        this->addAction(m_pDisplay3);
    }else if (screenCnt == 4)
    {
        this->addAction(m_pDisplay1);
        this->addAction(m_pDisplay2);
        this->addAction(m_pDisplay3);
        this->addAction(m_pDisplay4);
    }else
    {
        this->addAction(m_pDisplay1);
        this->addAction(m_pDisplay2);
        this->addAction(m_pDisplay3);
        this->addAction(m_pDisplay4);
    }

    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}


BOOL VSCVWidget::StopPlay()
{
    if (m_pStarted == true)
    {
        VDC_DEBUG( "%s StopPlay begin\n",__FUNCTION__);
        m_pStarted = false;
        m_bDeviceDeleted = false;
        m_SdlThread->join();
        delete m_SdlThread;
        m_SdlThread = NULL;

        RenderBlack();
        m_pStop->setEnabled(false);
        /* Start idle thread */
        m_IdleThread = new tthread::thread(VSCVWidget::RunIdle, (void *)this);
        VDC_DEBUG( "%s StopPlay End\n",__FUNCTION__);
    }
    VDC_DEBUG( "%s StopPlay End\n",__FUNCTION__);
    return TRUE;
}

BOOL VSCVWidget::DeviceDeleted(u32 nId)
{
    if (m_pStarted == true)
    {
        VDC_DEBUG( "%s DeviceDeleted begin\n",__FUNCTION__);
        m_pStarted = false;
        m_bDeviceDeleted = TRUE;
        m_SdlThread->join();
        delete m_SdlThread;

        RenderBlack();
        VDC_DEBUG( "%s DeviceDeleted end\n",__FUNCTION__);
        m_pStop->setEnabled(false);
	 m_IdleThread = new tthread::thread(VSCVWidget::RunIdle, (void *)this);
    }

    return TRUE;
}

void VSCVWidget::DeviceDeletedCallback(u32 nId, void * pParam)
{
    VSCVWidget *pWidget = NULL;

    if (pParam == NULL)
    {
        return;
    }

    pWidget = (VSCVWidget *)pParam;
    pWidget->DeviceDeleted(nId);

	return;
}

void VSCVWidget::resizeEvent( QResizeEvent * event )
{
    m_Mutex.lock();
    //m_UpdateSize = true;
    updateSize();
    //RenderBlack();
    
    QWidget::resizeEvent(event);
    RenderBlack();
    m_Mutex.unlock();
}

void VSCVWidget::SetVideoFocus(BOOL on)
{
    m_bFocus = on;
}

void VSCVWidget::mousePressEvent(QMouseEvent *e)
{
    VDC_DEBUG( "%s mousePressEvent %d\n",__FUNCTION__, m_nId);
    QWidget::mousePressEvent(e);
    Qt::MouseButtons mouseButtons = e->buttons();
    if( mouseButtons != Qt::LeftButton )
    {
        return;
    }

    emit ShowFocusClicked(m_nId);

}
void VSCVWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    VDC_DEBUG( "%s mouseDoubleClickEvent %d\n",__FUNCTION__, m_nId);
    QWidget::mouseDoubleClickEvent(e);
    if(isFullScreen()) {
        this->setWindowState(Qt::WindowMaximized);
    } else {
        //setParent(NULL);
        //showFullScreen();
        this->setWindowState(Qt::WindowFullScreen);
    }
}

void VSCVWidget::updateSize()
{
    m_UpdateSize = false;

    SDL_DestroyTexture(m_pTex);
    m_pTex = NULL;
    SDL_DestroyRenderer(m_SdlRender);
    m_SdlRender = NULL;
    //SDL_DestroyWindow(m_SdlWin);
    //m_SdlWin = NULL;
    
    //m_SdlWin = SDL_CreateWindowFrom((void *)this->winId());
    m_w = width();
    m_h = height();
    //w = 1280;
    //h = 700;
    VDC_DEBUG( "%s updateSize %d (%d, %d)\n",__FUNCTION__, __LINE__,
            m_w, m_h);
    m_w = (m_w/4) * 4;
    m_h = (m_h/4) * 4;
    //m_Cap->setSize(w, h);
    
    m_SdlRender = SDL_CreateRenderer(m_SdlWin, 0, 
        0);
    m_pTex = SDL_CreateTexture(m_SdlRender, SDL_PIXELFORMAT_RGB24, 
        SDL_TEXTUREACCESS_STREAMING, m_w, m_h);
    //SDL_SetRenderDrawColor(m_SdlRender, 85, 255, 0, 255);
	UpdateFontSurface();
    //SDL_SetRenderDrawBlendMode(m_SdlRender, SDL_BLENDMODE_BLEND);
    if (m_pRenderBuffer != NULL)
    {
        free(m_pRenderBuffer);
        m_pRenderBuffer = (unsigned char *)malloc(m_w * m_h * 3);
    }

}

void VSCVWidget::Run(void * pParam)
{
    VSCVWidget *pQtSdl2 = NULL;
    if (pParam == NULL)
    {
        return;
    }
    pQtSdl2 = (VSCVWidget *)pParam;
    //Sleep(3000);

    pQtSdl2->Run1();
}

void VSCVWidget::paintEvent(QPaintEvent *)
{
#if 0
    m_Mutex.lock();
    RenderBlack();
    m_Mutex.unlock();
#endif
}

void VSCVWidget::showEvent(QPaintEvent *)
{
#if 0
    m_Mutex.lock();
    RenderBlack();
    m_Mutex.unlock();
#endif
}

void VSCVWidget::DrawCurrent()
{
    return;
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = width();
    Rect.h  = height();
    SDL_RenderDrawRect(m_SdlRender, &Rect);
    SDL_RenderPresent(m_SdlRender);
}

void VSCVWidget::RenderBlack()
{
    int pitch;
    void * pixels = NULL;
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = width();
    Rect.h  = height();
#if 0
    memset(m_pRenderBuffer, 0, m_w * m_h * 3);
    pixels = NULL;

    SDL_LockTexture(m_pTex, NULL, &pixels, &pitch);
    if (pixels)
        memcpy(pixels, m_pRenderBuffer, m_w * m_h * 3);

    SDL_UnlockTexture(m_pTex);
#endif
    SDL_RenderClear(m_SdlRender);
    //SDL_RenderCopy(m_SdlRender, m_pTex, NULL, NULL);
    drawFocus();
    SDL_RenderPresent(m_SdlRender);
    //DrawCurrent();
}

void VSCVWidget::setVideoFocus(BOOL bFocus)
{
    m_bFocus = bFocus;
}

void VSCVWidget::drawFocus()
{
       if (m_bFocus != TRUE)
        {
             return;
        }
	int w = width();
	int h = height();
	//w = 1280;
	//h = 700;
	SDL_Rect rect;

	//w = (w/4) * 4;
	//h = (h/4) * 4;
	rect.x = 0;
	rect.y = 0;
	rect.w = w;
	rect.h = h;
       SDL_SetRenderDrawColor(m_SdlRender, 85, 255, 0, 255);
	SDL_RenderDrawRect(m_SdlRender, &rect);
       rect.x = 1;
	rect.y = 1;
	rect.w = w - 1;
	rect.h = h - 1;
	SDL_RenderDrawRect(m_SdlRender, &rect);

       SDL_SetRenderDrawColor(m_SdlRender, 0, 0, 0, 0xff);
}

void VSCVWidget::RunIdle(void * pParam)
{
    VSCVWidget *pQtSdl2 = NULL;
    if (pParam == NULL)
    {
        return;
    }
    pQtSdl2 = (VSCVWidget *)pParam;
    //Sleep(3000);

    pQtSdl2->RunIdle1();
}
void VSCVWidget::RunIdle1()
{
    Sleep(1000);
    while (m_pStarted != TRUE)
    {
        m_Mutex.lock();
        RenderBlack();
        m_Mutex.unlock();
        Sleep(200);
    }
}

void VSCVWidget::Run1()
{
    NotificationQueue *pCmd = NULL;
    cmn_cmd cmd;
    int pitch;
    void * pixels = NULL;
    gFactory->StartDevice(m_nPlayId);
    pCmd = gFactory->GetRawDataQueue(m_nPlayId);
    gFactory->RegDeleteCallback(m_nPlayId, VSCVWidget::DeviceDeletedCallback, (void *)this);

    while (m_pStarted == TRUE)
    {
            //Get test queue

                Notification::Ptr pNf(pCmd->waitDequeueNotification(1000));
                if (pNf)
                {
                    SinkNotification::LPtr pWorkNf = pNf.cast<SinkNotification>();
                    if (pWorkNf)
                    {
                        m_Mutex.lock();
                        //VDC_DEBUG( "%s size %d \n",__FUNCTION__, pWorkNf->cmd.size);

                        m_Scale->Scale((unsigned char *)(pWorkNf->cmd.data), pWorkNf->cmd.w, 
                                        pWorkNf->cmd.h, pWorkNf->cmd.w * 3,
                                    m_pRenderBuffer,
                                    m_w, m_h, m_w * 3);
                        pixels = NULL;

                        SDL_LockTexture(m_pTex, NULL, &pixels, &pitch);
                        if (pixels)
                            memcpy(pixels, m_pRenderBuffer, m_w * m_h * 3);

                        SDL_UnlockTexture(m_pTex);
                        SDL_RenderClear(m_SdlRender);
                        
                        SDL_RenderCopy(m_SdlRender, m_pTex, NULL, NULL);
                        DrawOSD();
			  
                        drawFocus();
			  
                        SDL_RenderPresent(m_SdlRender);
                        m_Mutex.unlock();                      
                    }
                }else
                {
                    Sleep(100);
                    //RenderBlack();
                    continue;
                }
                //Sleep(0);
        }

    if (m_bDeviceDeleted != TRUE)
    {
        VDC_DEBUG( "%s ReleaseRawDataQueue m_nPlayId %d\n",__FUNCTION__, 
                m_nPlayId);
        gFactory->ReleaseRawDataQueue(m_nPlayId, pCmd);
    }

	return ;
}

void VSCVWidget::UpdateTime()
{
#if ENABLE_OSD_SDL_TTF
    int currentTime = time(NULL);
    SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };

    QDateTime current = QDateTime::currentDateTime();
    if (currentTime == m_lastTime)
    {
        return;
    }
    current.setTime_t(currentTime);

    m_lastTime = currentTime;

    astring timeStr = current.toTimeSpec(Qt::UTC).toString("yyyy-MM-dd hh:mm:ss").toStdString();
    if (m_pTime)
    {
    	SDL_DestroyTexture(m_pTime);
    }
    SDL_Surface *pTime = TTF_RenderText_Solid(m_pFont, 
    			timeStr.c_str(), white);
    m_timeRect.x = 4;
    m_timeRect.y = 30;
    m_timeRect.w = pTime->w;
    m_timeRect.h = pTime->h;
    m_pTime = SDL_CreateTextureFromSurface(m_SdlRender, pTime);
    SDL_FreeSurface(pTime);
 #endif   
}

void VSCVWidget::InitFont()
{
#if ENABLE_OSD_SDL_TTF
	m_nFontSize = 20; 
       m_pFont =  TTF_OpenFont("FreeSansBold.ttf", m_nFontSize);
	if (m_pFont == NULL)
	{
		VDC_DEBUG( "%s Font Open Error\n",__FUNCTION__);
		return;
	}
	TTF_SetFontStyle(m_pFont, 1);
	m_pCaption = NULL;
	m_pTime = NULL;
       m_lastTime = time(NULL);

	return;
#endif
}


void VSCVWidget::UpdateFontSurface()
{
#if ENABLE_OSD_SDL_TTF
	if (m_pFont == NULL)
	{
		VDC_DEBUG( "%s Font Open Error\n",__FUNCTION__);
		return;
	}
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };
	
	if (m_pCaption)
	{
		SDL_DestroyTexture(m_pCaption);
	}
	
	if (m_pTime)
	{
		SDL_DestroyTexture(m_pTime);
	}
	char OSD[64];
       sprintf(OSD, "Camera %d", m_nPlayId);
       QDateTime current = QDateTime::currentDateTime();
	SDL_Surface *pCaption = TTF_RenderText_Solid(m_pFont, OSD, white);
       astring timeStr = current.toTimeSpec(Qt::UTC).toString("yyyy-MM-dd hh:mm:ss").toStdString();
	SDL_Surface *pTime = TTF_RenderText_Solid(m_pFont, 
					timeStr.c_str(), white);

	m_captionRect.x = 4;
	m_captionRect.y = 4;
	m_captionRect.w = pCaption->w;
	m_captionRect.h = pCaption->h;

	m_pCaption = SDL_CreateTextureFromSurface(m_SdlRender, pCaption);
	SDL_FreeSurface(pCaption);	


	m_timeRect.x = 4;
	m_timeRect.y = 30;
	m_timeRect.w = pTime->w;
	m_timeRect.h = pTime->h;
	m_pTime = SDL_CreateTextureFromSurface(m_SdlRender, pTime);
	SDL_FreeSurface(pTime);
	
  #endif


}
void VSCVWidget::DrawOSD()
{
 #if ENABLE_OSD_SDL_TTF
	if (m_pFont == NULL)
	{
		VDC_DEBUG( "%s Font Open Error\n",__FUNCTION__);
		return;
	}

       UpdateTime();
	SDL_RenderCopy(m_SdlRender, m_pCaption, NULL, &m_captionRect);
	SDL_RenderCopy(m_SdlRender, m_pTime, NULL, &m_timeRect);
#endif
}


