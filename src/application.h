#pragma once

#include <QCoreApplication>

class MyApplication : public QCoreApplication
{
public:
    explicit MyApplication(int &argc, char **argv);
    ~MyApplication() override;
};
