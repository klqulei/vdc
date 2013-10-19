

#include "vscmainwindows.h"

#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <qdebug.h>
#include <QDockWidget>
#include <QToolBar>
#include <QTabWidget>
#include <QListWidget>
#include <QMessageBox>

#include "vscdevicelist.h"
#include "vscview.h"
#include "vscvwidget.h"
#include "vscvideowall.h"
#include "vsccameraadd.h"
#include "factory.hpp"
#include "vscsearch.h"

extern Factory *gFactory;

Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

VSCMainWindows::VSCMainWindows(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
#if 0
    //TODO add a test device
    DeviceParam mParam(VSC_DEVICE_CAM, VSC_SUB_DEVICE_FILE, "dtneu_winter.mpg", "192.168.0.1");
    gFactory->AddDevice(mParam);
    DeviceParam mParam1(VSC_DEVICE_CAM, VSC_SUB_DEVICE_FILE, "AVSS_PV_Hard_Divx.avi", "192.168.0.2");
    gFactory->AddDevice(mParam1);
    DeviceParam mParam2(VSC_DEVICE_CAM, VSC_SUB_DEVICE_FILE, "test.mov", "TestFile");
    gFactory->AddDevice(mParam2);
#endif    

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    CreateActions();
    SetupMenuBar();
    SetupToolBar();
    CreateDockWindows();

    m_pMainArea = new QTabWidget(this);

    m_pMainArea->setTabsClosable(true);
    m_pMainArea->setMovable(true);

    VSCView *pView = new VSCView(m_pMainArea, *m_pMainArea);
    //VSCView *pView2 = new VSCView(this);
    m_pMainArea->addTab(pView,"VSCView");
    //m_pMainArea->addTab(pView2,"2x2 View");


    //pVideo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //pVideo->setMinimumSize(pView->ui.widget->width(),
    //        pView->ui.widget->height());
#if 0
    QVBoxLayout* layout = new QVBoxLayout();
    VSCVideoWall * pVideo = new VSCVideoWall();

    //layout->setSpacing(10);

    layout->addWidget(pVideo);
    layout->setMargin(0);

    pView->ui.widget->setLayout(layout);
#endif
    setCentralWidget(m_pMainArea);

    QString message = tr("VS Cloud Client");
    statusBar()->showMessage(message);
    //pVideo->Start();
    SetupConnections();

}

VSCMainWindows::~VSCMainWindows()
{

}



void VSCMainWindows::SetupConnections()
{
    connect(m_pMainArea, SIGNAL(tabCloseRequested(int)), this, SLOT(MainCloseTab(int)));
    connect(m_pDeviceList, SIGNAL(SurveillanceClicked()), this, SLOT(AddSurveillance()));
    connect(m_pDeviceList, SIGNAL(CameraAddClicked()), this, SLOT(AddCamera()));
    connect(m_pDeviceList, SIGNAL(SearchClicked()), this, SLOT(Search()));
    connect(m_pDeviceList, SIGNAL(CameraEditClicked(int)), this, SLOT(EditCamera(int)));
    connect(m_pDeviceList, SIGNAL(CameraDeleteClicked(int)), this, SLOT(DeleteCamera(int)));

    connect(this, SIGNAL(CameraDeleted()), m_pDeviceList, SLOT(CameraTreeUpdated()));

}

void VSCMainWindows::AddSurveillance()
{
    VSCView *pView = new VSCView(m_pMainArea,  *m_pMainArea);
    //VSCView *pView2 = new VSCView(this);
    m_pMainArea->addTab(pView,"VSCView");
    //m_pMainArea->addTab(pView2,"2x2 View");

#if 0
    //pVideo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //pVideo->setMinimumSize(pView->ui.widget->width(),
    //        pView->ui.widget->height());
    QVBoxLayout* layout = new QVBoxLayout();
    VSCVideoWall * pVideo = new VSCVideoWall();
    //layout->setSpacing(10);

    layout->addWidget(pVideo);
    layout->setMargin(0);

    pView->ui.widget->setLayout(layout);
#endif
    m_pMainArea->setCurrentWidget(pView);
}

void VSCMainWindows::AddCamera()
{
    DeviceParam mParam;
    VSCCameraAdd *pCameraadd = new VSCCameraAdd(mParam, this);
    //VSCView *pView2 = new VSCView(this);
    m_pMainArea->addTab(pCameraadd,tr("Camera"));  
    m_pMainArea->setCurrentWidget(pCameraadd);
    connect(pCameraadd, SIGNAL(CameraTreeUpdated()), m_pDeviceList, SLOT(CameraTreeUpdated()));
}

void VSCMainWindows::Search()
{
    if (VSCSearch::m_bStarted == TRUE)
    {
        QMessageBox msgBox;
        //Set text
        msgBox.setText("Search is In Processing ...");
            //Set predefined icon, icon is show on left side of text.
        //msgBox.setIcon(QMessageBox::Information);
            //set inforative text
        //msgBox.setInformativeText("Just show infornation.");
            //Add ok and cancel button.
        msgBox.setStandardButtons(QMessageBox::Ok);
            //Set focus of ok button
        msgBox.setDefaultButton(QMessageBox::Ok);

            //execute message box. method exec() return the button value of cliecke button
        int ret = msgBox.exec();

        return;
    }
    VSCSearch *pSearch = new VSCSearch(this);

    m_pMainArea->addTab(pSearch, tr("Search"));
    m_pMainArea->setCurrentWidget(pSearch);
	
	connect(pSearch, SIGNAL(CameraTreeUpdated()), m_pDeviceList, SLOT(CameraTreeUpdated()));
}

void VSCMainWindows::EditCamera(s32 nId)
{
    VDC_DEBUG( "%s %d\n",__FUNCTION__, nId);
    DeviceParam mParam;
    gFactory->GetDeviceParamById(mParam, nId);
    VSCCameraAdd *pCameraadd = new VSCCameraAdd(mParam, this);
    //VSCView *pView2 = new VSCView(this);
    m_pMainArea->addTab(pCameraadd,tr("Camera"));
    m_pMainArea->setCurrentWidget(pCameraadd);
    connect(pCameraadd, SIGNAL(CameraTreeUpdated()), m_pDeviceList, SLOT(CameraTreeUpdated()));
}
void VSCMainWindows::DeleteCamera(s32 nId)
{
    VDC_DEBUG( "%s %d\n",__FUNCTION__, nId);
    QMessageBox msgBox;
    //Set text
    msgBox.setText("Delete the Camera ...");
        //Set predefined icon, icon is show on left side of text.
    msgBox.setIcon(QMessageBox::Information);
        //set inforative text
    //msgBox.setInformativeText("Just show infornation.");
        //Add ok and cancel button.
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        //Set focus of ok button
    msgBox.setDefaultButton(QMessageBox::Ok);

        //execute message box. method exec() return the button value of cliecke button
    int ret = msgBox.exec();

        //User get input from returned value (ret). you can handle it here.
    switch (ret) {
    case QMessageBox::Ok:
       gFactory->DelDevice(nId);
       emit CameraDeleted();
       break;
    default:
       // should never be reached
       break;
    }

    return;
}

void VSCMainWindows::CreateActions()
{
    pActSurveillance = new QAction(tr("&Surveillance"), this);
    pActSurveillance->setIcon(QIcon(":/action/resources/surveillance.png"));

    pActSearch = new QAction(tr("&Search"), this);
    pActSearch->setIcon(QIcon(":/action/resources/search.png"));


    pActDeviceList = new QAction(tr("&Devices List"), this);
    pActDeviceList->setIcon(QIcon(":/action/resources/devicelist.png"));

    pActDeviceAdd = new QAction(tr("&Add"), this);
    pActDeviceAdd->setIcon(QIcon(":/action/resources/list-add.png"));

    pActDeviceDel = new QAction(tr("&Delete"), this);
    pActDeviceDel->setIcon(QIcon(":/action/resources/list-remove.png"));

    pActDeviceConf = new QAction(tr("&Configurate"), this);
    pActDeviceConf->setIcon(QIcon(":/action/resources/configure.png"));

}

void VSCMainWindows::SetupToolBar()
{

    //QToolBar *pToolBarHome = addToolBar(tr("&Home"));
#if 0
    QToolBar *pToolBarView = addToolBar(tr("&Video"));
    pToolBarView->addAction(pActDeviceList);
    pToolBarView->addAction(pActDeviceAdd);
    pToolBarView->addAction(pActDeviceDel);
    pToolBarView->addAction(pActDeviceConf);

    QToolBar *pToolBarVideo = addToolBar(tr("&Video"));
    pToolBarVideo->addAction(pActSurveillance);
    pToolBarVideo->addAction(pActSearch);
#endif

}
void VSCMainWindows::SetupMenuBar()
{
    QMenu *pMenuHome = menuBar()->addMenu(tr("&Home"));

#if 0
    QMenu *pMenuViews = menuBar()->addMenu(tr("&Views"));
    pMenuViews->addAction(pActDeviceList);
    pMenuViews->addAction(pActDeviceAdd);
    pMenuViews->addAction(pActDeviceDel);
    pMenuViews->addAction(pActDeviceConf);

    QMenu *pMenuVideo = menuBar()->addMenu(tr("&Video"));
    pMenuVideo->addAction(pActSurveillance);
    pMenuVideo->addAction(pActSearch);


    QMenu *pMenuSystem = menuBar()->addMenu(tr("&System"));
#endif
    QMenu *pMenuHelp = menuBar()->addMenu(tr("&Help"));

}

void VSCMainWindows::CreateDockWindows()
{
    QDockWidget *pDockDevicelist = new QDockWidget(tr("Devices"), this);
    //QDockWidget *pDockDevicelist = new QDockWidget(this);
    pDockDevicelist->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

#if 1
    //pDockDevicelist->setWidget(new VSCDeviceList(pDockDevicelist));
    m_pDeviceList = new VSCDeviceList(pDockDevicelist);
    pDockDevicelist->setWidget(m_pDeviceList);
#else
    QListWidget * customerList = new QListWidget(pDockDevicelist);
    customerList->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    pDockDevicelist->setWidget(customerList);
#endif



    addDockWidget(Qt::LeftDockWidgetArea, pDockDevicelist);
}

void VSCMainWindows::MainCloseTab(int index)
{
    QWidget *wdgt = m_pMainArea->widget(index );
    if (wdgt)
    {
        delete wdgt;
        wdgt = NULL;
    }
    m_pMainArea->removeTab(index);
}
