#include <QWSServer>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative>
#include <QDebug>
#include <QTextCodec>
#include "qmlapplicationviewer.h"
#include "animalmodel.h"
#include "menumodel.h"
#include "managemenus.h"





Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

//    QWSServer::setCursorVisible(false);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ManageMenus manageMenus;
    MenuModel &model = manageMenus.menuModel();

    QmlApplicationViewer viewer;
    QDeclarativeContext *ctxt = viewer.rootContext();
    ctxt->setContextProperty("myModel", &model);

    QSortFilterProxyModel &filterModel = manageMenus.orderFormModel();
    ctxt->setContextProperty("myOrderModel", &filterModel);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
//    viewer.showFullScreen();
    viewer.setMainQmlFile(QLatin1String("qml/OpenMenusClientQml/main.qml"));
    viewer.showExpanded();
//    const QString box("operationBox");
     QObject *operationBox = viewer.rootObject();
     QObject::connect(operationBox, SIGNAL(submit()), &manageMenus, SLOT(submit()));
    return app->exec();
}
