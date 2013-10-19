
#include "vscdevicetree.h"
#include <QMimeData>
#include <QDrag>
#include "factory.hpp"
#include "vscdeviceipc.h"
#include <QPainter>

VSCDeviceTree::VSCDeviceTree(QWidget *parent)
    : QTreeWidget(parent)
{
    createActions();
}

void VSCDeviceTree::createActions()
{
    pActAddCamera = new QAction(tr("&New"), this);
    //pActSurveillance->setIcon(QIcon(":/action/resources/surveillance.png"));
    pActEditCamera = new QAction(tr("&Edit"), this);
    pActDeleteCamera = new QAction(tr("&Delete"), this);

    SetupConnections();
    pPopMenu = new QMenu(this);
    //pPopMenu->addAction(pActAddCamera);
    //pPopMenu->addAction(pActEditCamera);
    //pPopMenu->addAction(pActDeleteCamera);
}

void VSCDeviceTree::SetupConnections()
{
    connect(pActAddCamera, SIGNAL(triggered()), this, SLOT(CameraAddClick()));
    connect(pActEditCamera, SIGNAL(triggered()), this, SLOT(CameraEditClick()));
    connect(pActDeleteCamera, SIGNAL(triggered()), this, SLOT(CameraDeleteClick()));

}

void VSCDeviceTree::contextMenuEvent(QContextMenuEvent * event)
{
    QTreeWidgetItem *item = NULL;
#if 0
    QPoint point = QCursor::pos();
    point = mapFromGlobal(point);
    item = this->itemAt(point);
    //pActAddCamera->setEnabled (false);
    //pActEditCamera->setEnabled (false);
    //pActDeleteCamera->setEnabled (false);
#endif
    item = currentItem();
    pPopMenu->removeAction(pActAddCamera);
    pPopMenu->removeAction(pActEditCamera);
    pPopMenu->removeAction(pActDeleteCamera);
    if(item != NULL)
    {
        VSCDeviceIPC *pIpc = dynamic_cast<VSCDeviceIPC * >(item);
        if (pIpc)
        {
            pPopMenu->addAction(pActEditCamera);
            pPopMenu->addAction(pActDeleteCamera);
        }

        /* This is Top level Camera Item */
        if (item == topLevelItem(1))
        {
            pPopMenu->addAction(pActAddCamera);
        }
    }
    pPopMenu->exec(QCursor::pos());//菜单出现的位置为当前鼠标的位置
    event->accept();
}

void VSCDeviceTree::mousePressEvent(QMouseEvent *event)
{
	VDC_DEBUG( "%s \n",__FUNCTION__);
	// Get current selection
	QTreeWidgetItem *selectedItem = currentItem();
	
    if (event->buttons() & Qt::RightButton)
    {
        return;
    }
	// If the selected Item exists
	if (selectedItem)
	{
		VSCDeviceIPC *pIpc = dynamic_cast<VSCDeviceIPC * >(selectedItem);
	    //VSCDeviceIPC *pIpc = (VSCDeviceIPC * )(selectedItem);
        // Create data
		if (pIpc)
		{
		    u32 nId = pIpc->GetDeviceId();
		    VDC_DEBUG( "%s id %d\n",__FUNCTION__, nId);
			QMimeData *mimeData = new QMimeData();
			mimeData->setText(QString::number(nId));
			
			// Create drag
			QPixmap pixmap(":/device/resources/camera1.png");
			QPainter painter(&pixmap);

			QDrag *drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->setPixmap(pixmap);
                      drag->setHotSpot(QPoint(drag->pixmap().width()/2,
                             drag->pixmap().height()/2));
			drag->exec();
		}

	}
	
	QTreeWidget::mousePressEvent(event);
}

void VSCDeviceTree::CameraAddClick()
{
    VDC_DEBUG( "%s \n",__FUNCTION__);
    emit CameraAddClicked();
    return;
}
void VSCDeviceTree::CameraEditClick()
{
    QTreeWidgetItem *item = NULL;
    item = currentItem();

    VDC_DEBUG( "%s \n",__FUNCTION__);
    if(item != NULL)
    {
        VSCDeviceIPC *pIpc = dynamic_cast<VSCDeviceIPC * >(item);
        if (pIpc)
        {
            VDC_DEBUG( "%s \n",__FUNCTION__);
            u32 nId = pIpc->GetDeviceId();
            emit CameraEditClicked(nId);
        }
    }

    return;
}
void VSCDeviceTree::CameraDeleteClick()
{
    QTreeWidgetItem *item = NULL;
    item = currentItem();

    VDC_DEBUG( "%s \n",__FUNCTION__);
    if(item != NULL)
    {
        VSCDeviceIPC *pIpc = dynamic_cast<VSCDeviceIPC * >(item);
        if (pIpc)
        {
            VDC_DEBUG( "%s \n",__FUNCTION__);
            u32 nId = pIpc->GetDeviceId();
            emit CameraDeleteClicked(nId);
        }
    }

    return;
}


