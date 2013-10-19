/********************************************************************************
** Form generated from reading UI file 'vscdevicelist.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VSCDEVICELIST_H
#define UI_VSCDEVICELIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "vscdevicetrash.h"
#include "vscdevicetree.h"

QT_BEGIN_NAMESPACE

class Ui_VSCDeviceList
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pbCamera;
    QPushButton *pushButton_3;
    QPushButton *pbSurveillance;
    QPushButton *pushButtonSearch;
    QPushButton *pushButton_8;
    VSCDeviceTrash *pushButtonTrash;
    QSpacerItem *verticalSpacer;
    VSCDeviceTree *treeWidget;

    void setupUi(QWidget *VSCDeviceList)
    {
        if (VSCDeviceList->objectName().isEmpty())
            VSCDeviceList->setObjectName(QStringLiteral("VSCDeviceList"));
        VSCDeviceList->resize(200, 1024);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VSCDeviceList->sizePolicy().hasHeightForWidth());
        VSCDeviceList->setSizePolicy(sizePolicy);
        VSCDeviceList->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(VSCDeviceList);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(VSCDeviceList);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(40, 40));
        QIcon icon;
        icon.addFile(QStringLiteral(":/action/resources/devicelist.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(VSCDeviceList);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(40, 40));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/device/resources/computer.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);
        pushButton_2->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(pushButton_2);

        pbCamera = new QPushButton(VSCDeviceList);
        pbCamera->setObjectName(QStringLiteral("pbCamera"));
        pbCamera->setMinimumSize(QSize(40, 40));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/device/resources/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCamera->setIcon(icon2);
        pbCamera->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(pbCamera);

        pushButton_3 = new QPushButton(VSCDeviceList);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(40, 40));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/device/resources/recorder.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon3);
        pushButton_3->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(pushButton_3);

        pbSurveillance = new QPushButton(VSCDeviceList);
        pbSurveillance->setObjectName(QStringLiteral("pbSurveillance"));
        pbSurveillance->setMinimumSize(QSize(40, 40));
        pbSurveillance->setMaximumSize(QSize(40, 40));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/action/resources/surveillance.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSurveillance->setIcon(icon4);
        pbSurveillance->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(pbSurveillance);

        pushButtonSearch = new QPushButton(VSCDeviceList);
        pushButtonSearch->setObjectName(QStringLiteral("pushButtonSearch"));
        pushButtonSearch->setMinimumSize(QSize(40, 40));
        pushButtonSearch->setMaximumSize(QSize(40, 40));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/action/resources/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSearch->setIcon(icon5);
        pushButtonSearch->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(pushButtonSearch);

        pushButton_8 = new QPushButton(VSCDeviceList);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(40, 40));
        pushButton_8->setMaximumSize(QSize(40, 40));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/action/resources/videosearch.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_8->setIcon(icon6);
        pushButton_8->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(pushButton_8);

        pushButtonTrash = new VSCDeviceTrash(VSCDeviceList);
        pushButtonTrash->setObjectName(QStringLiteral("pushButtonTrash"));
        pushButtonTrash->setMinimumSize(QSize(40, 40));
        pushButtonTrash->setMaximumSize(QSize(40, 40));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/action/resources/user-trash-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonTrash->setIcon(icon7);
        pushButtonTrash->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(pushButtonTrash);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        treeWidget = new VSCDeviceTree(VSCDeviceList);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem2->setIcon(0, icon3);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setIndentation(30);
        treeWidget->setRootIsDecorated(false);
        treeWidget->setItemsExpandable(true);
        treeWidget->setAnimated(true);
        treeWidget->setWordWrap(false);
        treeWidget->setHeaderHidden(true);
        treeWidget->setExpandsOnDoubleClick(true);
        treeWidget->setColumnCount(1);
        treeWidget->header()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout->addWidget(treeWidget);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(VSCDeviceList);

        QMetaObject::connectSlotsByName(VSCDeviceList);
    } // setupUi

    void retranslateUi(QWidget *VSCDeviceList)
    {
        VSCDeviceList->setWindowTitle(QString());
        pushButton->setText(QString());
        pushButton_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbCamera->setToolTip(QApplication::translate("VSCDeviceList", "Click to add Camera", 0));
#endif // QT_NO_TOOLTIP
        pbCamera->setText(QString());
        pushButton_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbSurveillance->setToolTip(QApplication::translate("VSCDeviceList", "Click to add VSCView", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pbSurveillance->setStatusTip(QApplication::translate("VSCDeviceList", "2", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pbSurveillance->setWhatsThis(QApplication::translate("VSCDeviceList", "3", 0));
#endif // QT_NO_WHATSTHIS
        pbSurveillance->setText(QString());
        pushButtonSearch->setText(QString());
        pushButton_8->setText(QString());
        pushButtonTrash->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("VSCDeviceList", "VS Cloud", 0));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("VSCDeviceList", "Localhost", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("VSCDeviceList", "Camera", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem3->setText(0, QApplication::translate("VSCDeviceList", "Recorder", 0));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class VSCDeviceList: public Ui_VSCDeviceList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VSCDEVICELIST_H
