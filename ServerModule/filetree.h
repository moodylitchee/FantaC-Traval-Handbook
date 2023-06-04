#ifndef FILETREE_H
#define FILETREE_H

#include <QMap>

class fileTree
{
public:
    fileTree();
    QString find(QString);
    void refresh(QString,QString);
    ~fileTree();
    QString last_find;

private:
    QMap<QString,QString> *qm;
};

#endif // FILETREE_H
