#ifndef XMLOPERATOR_H
#define XMLOPERATOR_H
#include <QFile>
#include <QtCore>
#include <QMessageBox>
#include <QtXml>

class XMLOperator
{
public:
    XMLOperator();
    ~XMLOperator();
    QString getNameByID(QString id);
    void addItem(const QString id, const QString name);
    void traverseNode(const QDomNode& node);
    bool isHexId(QString str);

    QXmlStreamReader* reader;
    QXmlStreamWriter* writer;
private:
    QFile* file;
};

#endif // XMLOPERATOR_H
