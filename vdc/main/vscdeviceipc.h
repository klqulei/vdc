

#ifndef VSCDEVICE_IPC_H
#define VSCDEVICE_IPC_H

#include <QWidget>
#include <QTimer>
#include <QTreeWidgetItem>
#include "factory.hpp"

class VSCDeviceIPC : public QTreeWidgetItem
{
public:
	void mousePressEvent(QMouseEvent *event);

public:
    VSCDeviceIPC(QTreeWidgetItem *parent, DeviceParam &pParam);
    ~VSCDeviceIPC();
	
public:
	u32 GetDeviceId()
	{
	    return m_Param.m_Conf.data.conf.nId;
	}
	
public:
    void UpdateOnline();	


private:
	DeviceParam m_Param;

};

#endif // VSCDEVICE_IPC_H
