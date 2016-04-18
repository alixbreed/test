#include "xmloperator.h"

XMLOperator::XMLOperator()
{
    file = new QFile("catalog.xml");
    writer = new QXmlStreamWriter(file);
    if (!file->exists())
    {
        file->open(QIODevice::WriteOnly | QIODevice::Text);
        writer->writeStartDocument();
        writer->writeStartElement("items");
        writer->writeEndElement();
        writer->writeEndDocument();
    }
    delete writer;
    file->close();
}

XMLOperator::~XMLOperator()
{
    file->close();
    delete file;
}

QString XMLOperator::getNameByID(QString id)
{
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    reader = new QXmlStreamReader(file);
    while(!reader->atEnd())
    {
        QXmlStreamReader::TokenType token = reader->readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (reader->name() == "item")
            {
                QXmlStreamAttributes attr = reader->attributes();
                if(attr.value("id").toString() == id)
                {
                    reader->readNextStartElement();
                    QString out = reader->readElementText();
                    file->close();
                    delete reader;
                    return out;
                }

            }
        }
    }
    file->close();
    delete reader;
    return "";
}

void XMLOperator::addItem(const QString id, const QString name)
{
    QString out;
    QTextStream output;
    writer = new QXmlStreamWriter(&out);
    reader = new QXmlStreamReader();
    if(file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        reader->setDevice(file);
        writer->setAutoFormatting(true);
        bool isAdded = false;

        do
        {
            reader->readNext();
            if(reader->isStartDocument())
                writer->writeStartDocument();
            if(reader->isStartElement())
            {
                writer->writeStartElement(reader->name().toString());
                if(reader->name().toString() == "item")
                {
                    QXmlStreamAttributes attr = reader->attributes();
                    writer->writeAttribute("id", attr.value("id").toString());
                    if(attr.value("id").toString() == id)
                    {
                        isAdded = true;
                        writer->writeStartElement("name");
                        writer->writeCharacters(name);
                        reader->readNext();
                        reader->readNext();
                        reader->readNext();
                        reader->readNext();
                    }
                }
            }
            if(reader->isCharacters())
                writer->writeCharacters(reader->text().toString());

            if(reader->isEndElement())
            {
                if(reader->name().toString() == "items"
                        && !isAdded)
                {
                    writer->writeStartElement("item");
                    writer->writeAttribute("id", id);
                    writer->writeTextElement("name", name);
                    writer->writeEndElement();
                }
                writer->writeEndElement();
            }

            if(reader->isEndDocument())
                writer->writeEndElement();

        } while (!reader->atEnd() && !reader->hasError());
    }
    output.setDevice(file);
    output.seek(0);
    output << out;
    file->close();
    delete reader;
    delete writer;
}

bool XMLOperator::isHexId(QString str)
{
    if (str.size() != 24)
        return false;
    QString chars = "0123456789ABCDEF";
    int counter = 0;
    for (int i=0; i < str.size(); i++)
    {
        for (int j=0; j < chars.size(); j++)
        {
            if (chars[j] == str[i])
            {
                counter++;
                break;
            }
        }
    }
    if (counter == str.size())
        return true;
    else
        return false;
}
