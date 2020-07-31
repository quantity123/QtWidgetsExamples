#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDebug>
#include <QDomNamedNodeMap>
//#include <QtXml>

void writeXML()
{
    QDomDocument doc;
    QDomProcessingInstruction instruction;  //处理指令
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);   //添加处理指令
    //添加根节点
    QDomElement rootElement;
    rootElement = doc.createElement("library"); //所有creaet 相关得函数只有QDomDocument类才有
    doc.appendChild(rootElement);//把root节点添加到QDomDocument XML文档, 通过doc.documentElement()可以取到rootElement根元素
    //添加一个子节点book与book属性和子元素
    QDomElement bookElement;
    bookElement = doc.createElement("book");
    rootElement.appendChild(bookElement);
    bookElement.setAttribute("id", 1);  //创建属性方法1，键值可以是各种类型
//        bookElement.setNodeValue("book setNodeValue_1......");    //不显示的
    QDomAttr timeDomAttr = doc.createAttribute("time");    //创建属性方法2，值只能是字符串
    timeDomAttr.setValue("2020-07-18");
//        timeDomAttr.setNodeValue("book setNodeValue_2......");  //覆盖掉了domAttr.setValue设置得值
    bookElement.setAttributeNode(timeDomAttr);
    QDomElement titleElement = doc.createElement("title"); //创建title子元素
    bookElement.appendChild(titleElement);
    QDomText textNode;
    textNode = doc.createTextNode("C++ primer");   //创建节点的文本，也是节点尖括号里的文本值
    titleElement.appendChild(textNode);
    QDomElement authorElement = doc.createElement("author"); //创建author子元素
    bookElement.appendChild(authorElement);
    textNode = doc.createTextNode("Stanley B.Lippman");
    authorElement.appendChild(textNode);
    QDomComment comment;
    comment = doc.createComment("id=1 Comment");
    authorElement.appendChild(comment);

    bookElement = doc.createElement("book");
//    bookElement.setTagName("book_1")  //可以修改标签名称
    rootElement.appendChild(bookElement);
    bookElement.setAttribute("id", 2);
    bookElement.setAttribute("time", "2020-07-17");
//    bookElement.setAttribute("time", "2021-05-10"); //可以这样修改属性值
    titleElement = doc.createElement("title");
    bookElement.appendChild(titleElement);
    textNode = doc.createTextNode("设计模式");
//    textNode.setData("dddddd");   //可以修改QDomText节点(bookElement元素的文本子节点)文本值
//    textNode.setNodeValue("aaaaaaaaaa");  //QDomText节点也可以这样修改文本值
    titleElement.appendChild(textNode);
    authorElement = doc.createElement("author");
    bookElement.appendChild(authorElement);
    textNode = doc.createTextNode("some body");
    authorElement.appendChild(textNode);
    comment = doc.createComment("id=2 Comment");   //这是html的注释
//    comment.setData("aaaaa"); //可以修改 comment 注释
    authorElement.appendChild(comment);

    QFile file("testXML.xml");
    bool openRet = file.open(QFile::WriteOnly|QFile::Truncate); //只写模式和Truncate是清空原来得内容
    if (openRet)
    {
//        QTextStream ts(&file);    //用文本流来保存到文件
//        ts.setCodec("utf-8");   //设置文本流编码格式
//        doc.save(ts, 4);  //4 是缩进4格

        file.write(doc.toByteArray());  //也可以直接保存到文件
        file.close();
    }
}

void repeatShowXmlDomNode(QDomNode &element)
{
    if (element.isNull())
        return;
    if (element.isElement())
        qDebug() << element.nodeName();
    if (element.isText())
        qDebug() << element.nodeValue();
    if (element.isComment())
        qDebug() << element.nodeValue();
    if (element.hasAttributes())
    {
        QDomNamedNodeMap attributes = element.attributes();
        for (quint16 i=0; i<attributes.count(); ++i)
        {
            qDebug() << attributes.item(i).nodeName();
            qDebug() << attributes.item(i).nodeValue();
        }
    }
    if (element.hasChildNodes())
    {
        for (quint16 i=0; i<element.childNodes().count(); ++i)
        {
            QDomNode node = element.childNodes().at(i);
            repeatShowXmlDomNode(node);
        }
    }
}

void repeatShowXmlElementTextAndComment(QDomElement domEle)
{
    domEle = domEle.firstChildElement("title");
    if (!domEle.isNull())
    {
        qDebug() << domEle.tagName();
        qDebug() << domEle.text();
    }
    domEle = domEle.nextSiblingElement("author");
    if (!domEle.isNull())
    {
        qDebug() << domEle.tagName();
        qDebug() << domEle.text();
//        qDebug() << domEle.childNodes().item(1).toComment().data();
        qDebug() << domEle.childNodes().at(1).toComment().data();
//        qDebug() << domEle.childNodes().item(1).nodeValue();
//        qDebug() << domEle.childNodes().at(1).nodeValue();
    }
}

void repeatShowXmlElementAttribute(QDomElement domEle)
{
    domEle = domEle.firstChildElement("book");
    while (!domEle.isNull())
    {
        qDebug() << domEle.tagName();
        qDebug() << domEle.attributeNode("id").name();
//        qDebug() << domEle.attributeNode("id").value();
        qDebug() << domEle.attribute("id");
        qDebug() << domEle.attributeNode("time").name();
//        qDebug() << domEle.attributeNode("time").value();
        qDebug() << domEle.attribute("time");
        repeatShowXmlElementTextAndComment(domEle);
        domEle = domEle.nextSiblingElement("book");
    }
}

void readXML()
{
    QFile file("testXML.xml");
    bool openRet = file.open(QFile::ReadOnly|QFile::Text);
    if (openRet)
    {
        QDomDocument xmlDoc;
        QString errorMsg;
        int errorLine;
        int errorcolumn;
        bool retResult = xmlDoc.setContent(&file, false, &errorMsg, &errorLine, &errorcolumn);
        if (retResult)
        {
            QDomElement domEle;
            domEle = xmlDoc.documentElement();
    //        repeatShowXmlDomNode(domEle); //读取1

            qDebug() << domEle.tagName();
            repeatShowXmlElementAttribute(domEle);  //读取2
        }
        else
        {
            qDebug() << "setContent errorMsg:" << errorMsg << ", errorLine:" << errorLine << ", errorcolumn:" << errorcolumn;
        }
        file.close();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    writeXML();

    readXML();

    return a.exec();
}
