#ifndef VSCVIEW_H
#define VSCVIEW_H

#include <QWidget>
#include "ui_vscview.h"
#include "utility.hpp"
#include "vscvwidget.h"
#include "vscvideowall.h"
#include "QTabWidget"
#include "vscplaycontrol.h"

class VSCView : public QWidget
{
    Q_OBJECT

public:
    VSCView(QWidget *parent, QTabWidget &pTabbed);
    ~VSCView();
public:
    void mouseDoubleClickEvent(QMouseEvent *e);
    void createContentMenu();
public:
    void SetupConnections();
	
public slots:
    void floatingClicked();
    void TabbedClicked();
    void ShowDisplayClicked(int nId);
    void ShowFocusClicked(int nId);
    void ShowPlayControl();
	
public:
    Ui::VSCView ui;
private:
    QWidget *m_pParent;
    QAction *m_pFloating;
    QAction *m_pUnFloating;
    BOOL m_bFloated;
    int m_currentFocus;
    VSCVideoWall * m_pVideo;
    VSCPlayControl * m_pPlayControl;
    BOOL m_bPlayControl;
    QTabWidget &m_pTabbed;
    
};

#endif // VSCVIEW_H
