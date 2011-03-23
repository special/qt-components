/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

#include "tst_quickcomponentstest.h"
#include <QTest>
#include <QUrl>
#include <QGraphicsObject>
#include <QDeclarativeComponent>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeView>
#include <QSignalSpy>

class tst_quickcomponentsstatusbar : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void batteryImage();
    void signalWidth();
    void position();
    void height();

private:
    QGraphicsObject *statusBar;
    QObject *priv;
    QScopedPointer<QDeclarativeView> view;
};

void tst_quickcomponentsstatusbar::initTestCase()
{
    view.reset(tst_quickcomponentstest::createDeclarativeView("tst_quickcomponentsstatusbar.qml"));
    QVERIFY(view);
    view->show();
    view->activateWindow();
    QTest::qWaitForWindowShown(view.data());
    QVERIFY(view->rootObject());
    QTRY_COMPARE(QApplication::activeWindow(), static_cast<QWidget *>(view.data()));
    statusBar = view->rootObject()->findChild<QGraphicsObject*>("statusBar");
    QVERIFY(statusBar);
    priv = view->rootObject()->findChild<QObject*>("priv");
    QVERIFY(priv);
}

void tst_quickcomponentsstatusbar::signalWidth()
{
    QVariant returnedValue = 0;
    QVariant widthPercentage = 0;

    QMetaObject::invokeMethod(priv, "signalWidthPercentage",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, widthPercentage));

    QCOMPARE(returnedValue.toInt(), 0);

    widthPercentage = 100;
    returnedValue = 0;
    QMetaObject::invokeMethod(priv, "signalWidthPercentage",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, widthPercentage));

    QCOMPARE(returnedValue.toInt(), 1);
}

void tst_quickcomponentsstatusbar::batteryImage()
{
    QVariant returnedValue = 0;
    int batteryLevel = 0;
    QMetaObject::invokeMethod(priv, "batteryImage",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, batteryLevel));

    QString imagePath = returnedValue.toString();
    batteryLevel = 25;
    QMetaObject::invokeMethod(priv, "batteryImage",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, batteryLevel));

    QVERIFY(imagePath != returnedValue.toString());
    imagePath = returnedValue.toString();
    batteryLevel = 100;
    QMetaObject::invokeMethod(priv, "batteryImage",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, batteryLevel));

    QVERIFY(imagePath != returnedValue.toString());
}

void tst_quickcomponentsstatusbar::position()
{
    QCOMPARE(statusBar->property("x").toInt(), 0);
    QCOMPARE(statusBar->property("y").toInt(), 0);
}

void tst_quickcomponentsstatusbar::height()
{
    QVERIFY(statusBar->property("implicitWidth").toInt() > 0);
    QVERIFY(statusBar->property("implicitHeight").toInt() > 0);
}

QTEST_MAIN(tst_quickcomponentsstatusbar)

#include "tst_quickcomponentsstatusbar.moc"