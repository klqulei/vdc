

#ifndef VSCDEVICE_TREE_H
#define VSCDEVICE_TREE_H

#include <QWidget>
#include <QTreeWidget>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>

#include "factory.hpp"

class VSCDeviceTree : public QTreeWidget
{
    Q_OBJECT
public:
    VSCDeviceTree(QWidget *parent = 0);
public:
	void mousePressEvent(QMouseEvent *event);
	void contextMenuEvent(QContextMenuEvent * event);
	void createActions();
	void SetupConnections();

public slots:
    void CameraAddClick();
    void CameraEditClick();
    void CameraDeleteClick();

signals:
    void CameraAddClicked();
    void CameraEditClicked(int nId);
    void CameraDeleteClicked(int nId);

private:
	QAction *pActDeleteCamera;
	QAction *pActAddCamera;
	QAction *pActEditCamera;
	QMenu *pPopMenu;
    //~VSCDeviceTree();

};

#endif // VSCDEVICE_TREE_H
