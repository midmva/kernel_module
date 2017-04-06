TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    netfilter_http.c

INCLUDEPATH += /usr/src/linux-headers-4.4.0-72/include/

include(deployment.pri)
qtcAddDeployment()

