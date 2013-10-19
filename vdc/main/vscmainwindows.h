
#ifndef VSCMAINWINDOWS_H
#define VSCMAINWINDOWS_H

#include <QtWidgets/QMainWindow>
#include "ui_vscmainwindows.h"

#include "vscdockwidget.h"

class VSCDeviceList;
class VSCMainWindows : public QMainWindow
{
    Q_OBJECT

public:
    void SetupToolBar();
    void SetupMenuBar();
    void CreateActions();
    void CreateDockWindows();
    void SetupConnections();


public slots:
    void AddSurveillance();
    void AddCamera();
    void Search();
    void EditCamera(int nId);
    void DeleteCamera(int nId);
    void MainCloseTab(int index);

signals:
    void CameraDeleted();
public:
    VSCMainWindows(QWidget *parent = 0);
    ~VSCMainWindows();
private:
    QTabWidget * m_pMainArea;

private:
    QAction *pActSurveillance;
    QAction *pActSearch;



    QAction *pActDeviceList;
    QAction *pActDeviceAdd;
    QAction *pActDeviceDel;
    QAction *pActDeviceConf;

private:
    VSCDeviceList * m_pDeviceList;

private:
    Ui::VSCMainWindowsClass ui;
};

#endif // VSCMAINWINDOWS_H
