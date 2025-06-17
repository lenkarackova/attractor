#pragma once

#include <QObject>
#include <QQmlEngine>

class PlatformHelper : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool isWeb READ isWeb CONSTANT)

public:
    explicit PlatformHelper(QObject* parent = nullptr) : QObject(parent) {}

    bool isWeb() const
    {
#ifdef __EMSCRIPTEN__
        return true;
#else
        return false;
#endif
    }
};
