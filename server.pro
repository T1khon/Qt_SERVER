QT -= gui
QT += network

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = fedora_server

SOURCES += \
    main.cpp \
    server.cpp

HEADERS += \
    server.h
