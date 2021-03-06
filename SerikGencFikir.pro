QT -= gui
QT += core xml

CONFIG += c++14 console
CONFIG -= app_bundle

CONFIG += no_keywords

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    mainapplication.cpp \
    src/header.cpp \
    src/body.cpp \
    src/footer.cpp \
    src/lloginwidget.cpp \
    src/user.cpp \
    src/baseclass.cpp \
    src/userwidget.cpp \
    src/project.cpp \
    src/davetiyewidget.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




win32: LIBS += -L$$PWD/Wt-4.0.4-msvs2015-Windows-x64-SDK/lib/ -lwt -lwthttp

INCLUDEPATH += $$PWD/Wt-4.0.4-msvs2015-Windows-x64-SDK/include
DEPENDPATH += $$PWD/Wt-4.0.4-msvs2015-Windows-x64-SDK/include

INCLUDEPATH += $$PWD/../../Comman
DEPENDPATH += $$PWD/../../Comman

HEADERS += \
    ../../Comman/bootstrap.h \
    ../../Comman/inlinestyle.h \
    ../url.h \
    mainapplication.h \
    src/header.h \
    src/body.h \
    src/footer.h \
    src/lloginwidget.h \
    ../url.h \
    src/user.h \
    src/baseclass.h \
    src/userwidget.h \
    src/project.h \
    src/davetiyewidget.h \
    todolist.h

DISTFILES += \
    ../Release/docroot/css/css.css \
    README.md







win32: LIBS += -L$$PWD/mongo/lib/ -lbsoncxx -lmongocxx

INCLUDEPATH += $$PWD/mongo/include/mongocxx/v_noabi
DEPENDPATH += $$PWD/mongo/include/mongocxx/v_noabi

INCLUDEPATH += $$PWD/mongo/include/bsoncxx/v_noabi
DEPENDPATH += $$PWD/mongo/include/bsoncxx/v_noabi







win32: LIBS += -L$$PWD/../../Boost/boost/lib64-msvc-14.0/ -lboost_atomic-vc140-mt-1_65_1

INCLUDEPATH += $$PWD/../../Boost/boost/
DEPENDPATH += $$PWD/../../Boost/boost/
