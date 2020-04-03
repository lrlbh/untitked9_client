#-------------------------------------------------
#
# Project created by QtCreator 2019-07-05T15:22:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled9
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        bio_base64.cpp \
        gua_info.pb.cpp \
        hash_lr.cpp \
        laozi_widget.cpp \
        main.cpp \
        my_aes.cpp \
        my_base64.cpp \
        my_rsa.cpp \
        my_tcp.cpp \
        my_thread.cpp \
        my_widget.cpp \
        one_widget.cpp \
        protocol_laozi.cpp \
        protocol_register_is_pub_key.cpp \
        protocol_zhouyi.cpp \
        ui.cpp \
        user_account_widget.cpp \
        user_long_in.cpp \
        user_register_widget.cpp \
        widget.cpp

HEADERS += \
        aes_crypto.h \
        bio_base64.h \
        gua_info.pb.h \
        hash_lr.h \
        laozi_widget.h \
        my_aes.h \
        my_base64.h \
        my_tcp.h \
        my_thread.h \
        my_widget.h \
        one_widget.h \
        protocol_laozi.h \
        protocol_register_is_pub_key.h \
        protocol_zhouyi.h \
        ui.h \
        user_account_widget.h \
        user_long_in.h \
        user_register_widget.h \
        widget.h

CONFIG += mobility
MOBILITY = 

#头文件
INCLUDEPATH += $$PWD/include
#mingw使用库
win32:LIBS += $$PWD/libs/protobuf/mingw_32/libprotobuf.a
win32:LIBS += $$PWD/libs/protobuf/mingw_64/libprotobuf.a
win32:LIBS += -L"D:\zm\35_my_code\Qt\untitled9\libs\openssl\mingw32" -lcrypto
win32:LIBS += -L"D:\zm\35_my_code\Qt\untitled9\libs\openssl\mingw32" -lssl

#安卓使用库
unix:android{
    LIBS += -L$$PWD/libs/protobuf\arm64_va8 \
            -lprotobuf \
}

unix:android{
    LIBS += -L$$PWD/libs/openssl\arm64 \
            -lssl \
            -lcrypto
}
#把库打包到apk中
contains(ANDROID_TARGET_ARCH,armeabi-v8a)
{
    ANDROID_EXTRA_LIBS =\
        $$PWD/libs/protobuf\arm64_va8/libprotobuf.so\
        $$PWD/libs/protobuf\arm64_va8/libprotobuf-lite.so\
        $$PWD/libs/protobuf\arm64_va8/libprotoc.so\
}
contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_EXTRA_LIBS += \
        $$PWD/libs/openssl/arm64/libcrypto.so \
        $$PWD/libs/openssl/arm64/libssl.so
}







# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
