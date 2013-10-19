

#ifndef VSCDEVICELIST_H
#define VSCDEVICELIST_H

#include <QWidget>
#include "ui_vscdevicelist.h"
#include "factory.hpp"
#include "QTimer"

class VSCDeviceList : public QWidget
{
    Q_OBJECT

public:
    //QSize sizeHint()
    //{
    //    return QSize(300, 300);
    //}

public:
    VSCDeviceList(QWidget *parent);
    ~VSCDeviceList();
public:
    void SetupConnections();

public:
    void AddIPCamera(DeviceParam &pParam);
    void RemoveAllCamera();

public slots:
    void SurveillanceClick();
    void CameraAddClick();
    void SearchClick();
    void CameraTreeUpdated();
    void UpdateOnline();

signals:
    void SurveillanceClicked();
    void CameraAddClicked();
    void SearchClicked();
    void CameraEditClicked(int nId);
    void CameraDeleteClicked(int nId);

private:
    Ui::VSCDeviceList ui;
private:
    QTimer *m_Timer;
    
};

#endif // VSCDEVICELIST_H
