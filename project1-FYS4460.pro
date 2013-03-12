TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fpermissive

release {
DEFINES += ARMA_NO_DEBUG
}

SOURCES += main.cpp \
    particle.cpp \
    cell.cpp \
    mdsystem.cpp \
    mdapplication.cpp \
    outputmd.cpp \
    integrator.cpp \
    velocityverlet.cpp \
    interparticleforce.cpp \
    lennardjones.cpp \
    measurements.cpp

HEADERS += \
    particle.h \
    cell.h \
    mdsystem.h \
    mdapplication.h \
    outputmd.h \
    integrator.h \
    velocityverlet.h \
    interparticleforce.h \
    lennardjones.h \
    measurements.h

#unix|win32: LIBS += -larmadillo

unix: CONFIG += link_pkgconfig
unix: CONFIG += larmadillo
#unix: PKGCONFIG += libconfig++

