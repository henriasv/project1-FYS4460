TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    particle.cpp \
    cell.cpp \
    mdsystem.cpp \
    mdapplication.cpp

HEADERS += \
    particle.h \
    cell.h \
    mdsystem.h \
    mdapplication.h

unix|win32: LIBS += -larmadillo

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libconfig++
