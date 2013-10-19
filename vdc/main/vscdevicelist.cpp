
#include "vscdevicelist.h"
#include "vscdeviceipc.h"
#include "factory.hpp"

extern Factory *gFactory;

VSCDeviceList::VSCDeviceList(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    CameraTreeUpdated();

    SetupConnections();
    m_Timer = new QTimer(this);
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(UpdateOnline()));  
    m_Timer->start(1000 * 20);  

}

void VSCDeviceList::SetupConnections()
{
    connect(ui.pbSurveillance, SIGNAL(clicked()), this, SLOT(SurveillanceClick()));
    connect(ui.pbCamera, SIGNAL(clicked()), this, SLOT(CameraAddClick()));
    connect(ui.pushButtonSearch, SIGNAL(clicked()), this, SLOT(SearchClick()));
    connect(ui.treeWidget, SIGNAL(CameraAddClicked()), this, SIGNAL(CameraAddClicked()));
    connect(ui.treeWidget, SIGNAL(CameraEditClicked(int)), this, SIGNAL(CameraEditClicked(int)));
    connect(ui.treeWidget, SIGNAL(CameraDeleteClicked(int)), this, SIGNAL(CameraDeleteClicked(int)));
    connect(ui.pushButtonTrash, SIGNAL(CameraDeleted()), this, SLOT(CameraTreeUpdated()));
}

void VSCDeviceList::CameraTreeUpdated()
{
    RemoveAllCamera();
    DeviceParamMap pMap;
    gFactory->GetDeviceParamMap(pMap);


    DeviceParamMap::iterator it = pMap.begin();

    for(; it!=pMap.end(); ++it)
    {
        u32 nId = (*it).first;
        DeviceParam pParam = (*it).second;
        switch (pParam.m_Conf.data.conf.nType)
        {
            case VSC_DEVICE_CAM:
            {
                AddIPCamera(pParam);
                break;
            }
            default:
            {

                break;
            }
        }

    }
}

void VSCDeviceList::AddIPCamera(DeviceParam &pParam)
{
    QTreeWidgetItem *qtreewidgetitem = ui.treeWidget->topLevelItem(1);
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/device/resources/camera.png"), QSize(), QIcon::Normal, QIcon::Off);

    QTreeWidgetItem *qtreewidgetitemChild = new VSCDeviceIPC(qtreewidgetitem, pParam);

    qtreewidgetitemChild->setIcon(0, icon1);

    qtreewidgetitemChild->setText(0, QApplication::translate("Camera",
            pParam.m_Conf.data.conf.Name, 0));

    qtreewidgetitem->setExpanded(true);


}

void VSCDeviceList::UpdateOnline()
{
    BOOL bonline = FALSE;
#if 0    
    DeviceParamMap pMap;
    gFactory->GetDeviceParamMap(pMap);

    DeviceParamMap::iterator it = pMap.begin();

    for(; it!=pMap.end(); ++it)
    {
        u32 nId = (*it).first;
        DeviceParam pParam = (*it).second;
	 bonline = gFactory->GetDeviceOnline(pParam.m_Conf.data.conf.nId);

    }
#endif
    QTreeWidgetItem *qtreewidgetitem = ui.treeWidget->topLevelItem(1);

    int cnt = qtreewidgetitem->childCount();
    VDC_DEBUG( "%s cnt %d\n",__FUNCTION__, cnt);
    for (int i = 0; i < cnt; i ++)
    {
        VDC_DEBUG( "%s cnt %d\n",__FUNCTION__, i);
        QTreeWidgetItem * pChild = qtreewidgetitem->child(i);
	 VSCDeviceIPC *pIPC = dynamic_cast<VSCDeviceIPC*>(pChild);
	 if (pIPC)
	     pIPC->UpdateOnline();
        
    }
}

void VSCDeviceList::RemoveAllCamera()
{
    QTreeWidgetItem *qtreewidgetitem = ui.treeWidget->topLevelItem(1);

    qDeleteAll(qtreewidgetitem->takeChildren());
#if 0
    int cnt = qtreewidgetitem->childCount();
    VDC_DEBUG( "%s cnt %d\n",__FUNCTION__, cnt);
    for (int i = 0; i < cnt; i ++)
    {
        VDC_DEBUG( "%s cnt %d\n",__FUNCTION__, i);
        QTreeWidgetItem * pChild = qtreewidgetitem->child(i);
        delete pChild;
    }
#endif
}

VSCDeviceList::~VSCDeviceList()
{
	m_Timer->stop();
	delete m_Timer;
}

void VSCDeviceList::SurveillanceClick()
{
    emit SurveillanceClicked();
    return;
}

void VSCDeviceList::CameraAddClick()
{
    emit CameraAddClicked();
    return;
}

void VSCDeviceList::SearchClick()
{
    emit SearchClicked();
    return;
}

