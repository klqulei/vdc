
#include "vscdeviceipc.h"
#include "factory.hpp"
#include "QColor"

extern Factory *gFactory;

VSCDeviceIPC::VSCDeviceIPC(QTreeWidgetItem *parent, DeviceParam &pParam)
    : QTreeWidgetItem(parent)
{
	m_Param = pParam;
       UpdateOnline();

}

void VSCDeviceIPC::mousePressEvent(QMouseEvent *event)
{
	VDC_DEBUG( "%s \n",__FUNCTION__);
}


void VSCDeviceIPC::UpdateOnline()
{
	BOOL bonline = FALSE;
	bonline = gFactory->GetDeviceOnline(m_Param.m_Conf.data.conf.nId);

	if (bonline == TRUE)
	{
		this->setTextColor(0, QColor(0, 170, 0));
               VDC_DEBUG( "%s Set to Green %d\n",__FUNCTION__, m_Param.m_Conf.data.conf.nId);
	}else
	{
		this->setTextColor(0, QColor(194, 194, 194));
               VDC_DEBUG( "%s Set to black %d\n",__FUNCTION__, m_Param.m_Conf.data.conf.nId);
	}
}

VSCDeviceIPC::~VSCDeviceIPC()
{

}
