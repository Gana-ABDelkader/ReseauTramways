QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Classes/PartieTraitement/sources/Arret.cpp \
    Classes/PartieTraitement/sources/listechaine.cpp \
    Classes/PartieTraitement/sources/listetram.cpp \
    Classes/PartieTraitement/sources/tramway.cpp \
    main.cpp \
    affichagereseau.cpp

HEADERS += \
    Classes/PartieTraitement/Entete/Arret.h \
    Classes/PartieTraitement/Entete/listechaine.h \
    Classes/PartieTraitement/Entete/listetram.h \
    Classes/PartieTraitement/Entete/tramway.h \
    affichagereseau.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
