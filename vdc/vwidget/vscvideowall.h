
#ifndef __VIDEO_WALL_H_
#define __VIDEO_WALL_H_

#include <QWidget>
#include <QGridLayout>
#include <map>
#include "utility.hpp"

/* Control command */
typedef enum
{
    LAYOUT_MODE_1 = 1,
    LAYOUT_MODE_2X2,
    LAYOUT_MODE_3X3,
    LAYOUT_MODE_4X4,
    LAYOUT_MODE_6,
    LAYOUT_MODE_8,
    LAYOUT_MODE_12p1,
    LAYOUT_MODE_LAST
} VideoWallLayoutMode;

#define VIDEO_WALL_WIDGET_MAX 16

class VSCVWidget;
typedef std::map<int, VSCVWidget *> VideoWidgetMap;

class VSCVideoWall : public QWidget
{
    Q_OBJECT

public:
    VSCVideoWall(QWidget *parent = 0);
    ~VSCVideoWall();

public:
    void mouseDoubleClickEvent(QMouseEvent *e);
    void createContentMenu();

public:
    void ClearVideoLayout();
    void SetupVideoLayout4x4();
    void SetupVideoLayout2x2();
    void SetupVideoLayout3x3();
    void SetupVideoLayout1();
    void SetupVideoLayout12p1();
    void SetupVideoLayout6();
    void StopVideoBeforeSetLayout();
    void SetVideoFocus(int nId, BOOL on);

public slots:
    void floatingAction();
    void unFloatingAction();
    void SetLayoutMode4x4(){SetLayoutMode(LAYOUT_MODE_4X4);}
    void SetLayoutMode3x3(){SetLayoutMode(LAYOUT_MODE_3X3);}
    void SetLayoutMode2x2(){SetLayoutMode(LAYOUT_MODE_2X2);}
    void SetLayoutMode6(){SetLayoutMode(LAYOUT_MODE_6);}
    void SetLayoutMode12p1(){SetLayoutMode(LAYOUT_MODE_12p1);}
    void SetLayoutMode1(){SetLayoutMode(LAYOUT_MODE_1);}

public:
    void UpdateVideoWallLayout();
    void SetLayoutMode(VideoWallLayoutMode nMode);

signals:
    void ShowDisplayClicked(int nId);
    void ShowFloatingClicked();
    void ShowTabbedClicked();
    void ShowFocusClicked(int nId);

public:
    bool Start();
    bool Stop();
private:
    QWidget *m_pParent;
    VideoWidgetMap m_VideoMap;
    QGridLayout *m_pLayout;
    QAction *m_pFloating;
    QAction *m_pUnFloating;
    BOOL m_bFloated;
    VideoWallLayoutMode m_VideoWallMode;


};

#endif // __VIDEO_WALL_H_
