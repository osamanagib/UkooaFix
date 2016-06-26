QT += core
QT += gui
QT       +=  widgets

CONFIG += c++11

TARGET = UkooaFix
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS_RELEASE = -std=c++14  -unroll-aggressive -g  -qopt-assume-safe-padding  -xCORE-AVX2 -ip -fma  -ftz -fp-model fast=2  -qopt-report-phase=vec  -O3  -falign-functions=16 -ansi-alias -fstrict-aliasing -D_REENTRANT  -fno-jump-tables

INCLUDEPATH +=   /Users/nagioi0a/Downloads/qwt-6.1.2/src /opt/intel/compilers_and_libraries_2016/mac/include
INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/Headers
INCLUDEPATH +=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/AGL.framework/Headers/

TEMPLATE = app

SOURCES += main.cpp
LIBS += -F/usr/local/qwt-6.1.2/lib -framework qwt
INCLUDEPATH += $$PWD/../Downloads/qwt-6.1.2/lib/qwt.framework/Versions/6/Headers
DEPENDPATH += $$PWD/../Downloads/qwt-6.1.2/lib/qwt.framework/Versions/6/Headers
