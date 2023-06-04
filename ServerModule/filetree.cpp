#include "filetree.h"
#include <map>
#include <QDebug>

fileTree::fileTree()
{
    qm=new QMap<QString,QString>;
}

QString fileTree::find(QString in)
{
    last_find=in;
    qDebug()<<"find";
    qDebug()<<in;
    if((*qm).contains(in))
        return (*qm)[in];
    else return QString("未找到条目");
}

void fileTree::refresh(QString key, QString cont)
{
    (*qm)[key]=cont;
}

fileTree::~fileTree()
{
    delete qm;
}


