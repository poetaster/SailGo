# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-sailgo

CONFIG += sailfishapp

SOURCES += src/sailfishos/harbour-sailgo.cpp \
    src/common/abstractboardcontroller.cpp \
    src/common/boardlistmodelwrapper.cpp \
    src/common/boardmodel.cpp \
    src/common/moveAnalysis.cpp \

OTHER_FILES += qml/harbour-sailgo.qml \
    rpm/harbour-sailgo.changes.in \
    rpm/harbour-sailgo.spec \
    translations/*.ts \
    harbour-sailgo.desktop \
    harbour-sailgo.png \

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

TRANSLATIONS += translations/harbour-sailgo-de.ts

HEADERS += \
    src/common/abstractboardcontroller.h \
    src/common/boardlistmodelwrapper.h \
    src/common/boardmodel.h \
    src/common/common.h \
    src/common/moveAnalysis.h

SAILFISHAPP_ICONS += 86x86 108x108 128x128 172x172

DISTFILES += \
    qml/sailfishos/pages/About.qml \
    qml/elements/GoBoard.qml \
    qml/elements/GoPiece.qml \
    qml/elements/GoSquare.qml \
    qml/sailfishos/harbour-sailgo.qml \
    qml/sailfishos/pages/FirstPage.qml \
    qml/sailfishos/cover/CoverPage.qml \
    qml/elements/images/black_piece.svg \
    qml/elements/images/board.svg \
    qml/elements/images/white_piece.svg
