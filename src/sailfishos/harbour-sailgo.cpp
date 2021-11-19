/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QtQuick>
#include <sailfishapp.h>
#include "../common/boardmodel.h"
#include "../common/boardlistmodelwrapper.h"
#include "../common/abstractboardcontroller.h"


int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).


    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    BoardModel * model = new BoardModel(13, 13);
    AbstractBoardController * controller = new AbstractBoardController(model);
    BoardListModelWrapper * listWrapper = new BoardListModelWrapper(model);

    view->rootContext()->setContextProperty("boardTableModel",  model);
    view->rootContext()->setContextProperty("boardController",  controller);
    view->rootContext()->setContextProperty("boardListModel",  listWrapper);

    view->setSource(SailfishApp::pathTo("qml/sailfishos/harbour-sailgo.qml"));
    //view->setSource(QUrl(QStringLiteral("/usr/share/harbour-sailgo/qml/sailfishos/harbour-sailgo.qml")));

    view->setTitle("SailGo");
    view->showFullScreen();
    return app->exec();
}

/*QTranslator *appTranslator = new QTranslator;
appTranslator->load("harbour-tidings-" + QLocale::system().name(), SailfishApp::pathTo("translations").path());
app->installTranslator(appTranslator);

qmlRegisterType<Database>("harbour.tidings", 1, 0, "Database");
qmlRegisterType<FeedLoader>("harbour.tidings", 1, 0, "FeedLoader");
qmlRegisterType<HtmlFilter>("harbour.tidings", 1, 0, "HtmlFilter");
qmlRegisterType<UrlLoader>("harbour.tidings", 1, 0, "UrlLoader");
qmlRegisterType<NewsBlendModel>("harbour.tidings", 1, 0, "NewsModel");

DateParser dateParser;
Json json;

QScopedPointer<QQuickView> view(SailfishApp::createView());
view->rootContext()->setContextProperty("appVersion", appVersion);
view->rootContext()->setContextProperty("dateParser", &dateParser);
view->rootContext()->setContextProperty("json", &json);

view->setSource(SailfishApp::pathTo("qml/harbour-tidings.qml"));
view->setTitle("Tidings");
view->showFullScreen();

return app->exec();
*/
