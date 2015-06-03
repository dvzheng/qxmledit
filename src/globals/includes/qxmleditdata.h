/**************************************************************************
 *  This file is part of QXmlEdit                                         *
 *  Copyright (C) 2011 by Luca Bellonda and individual contributors       *
 *    as indicated in the AUTHORS file                                    *
 *  lbellonda _at_ gmail.com                                              *
 *                                                                        *
 * This library is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU Library General Public            *
 * License as published by the Free Software Foundation; either           *
 * version 2 of the License, or (at your option) any later version.       *
 *                                                                        *
 * This library is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 * Library General Public License for more details.                       *
 *                                                                        *
 * You should have received a copy of the GNU Library General Public      *
 * License along with this library; if not, write to the                  *
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,       *
 * Boston, MA  02110-1301  USA                                            *
 **************************************************************************/
#ifndef QXMLEDITDATA_H
#define QXMLEDITDATA_H

#include <QObject>

#include "libQXmlEdit_global.h"

#include "xmlEdit.h"
#include "style.h"
#include "plugin.h"

#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkAccessManager>

#include "modules/copyattr/copiedattribute.h"
#include "modules/xslt/xsltmanager.h"
#include "modules/search/searchmanager.h"
#include "modules/services/colormanager.h"

#include "data/DataInterface.h"
#include "framework/include/Notifier.h"
#include "modules/services/anotifier.h"
#include "modules/encoding/unicodehelper.h"

#define STYLE_DIR_USESTD    "Standard"
#define STYLE_DIR_USEDIR    "Directory"
#define STYLE_DIR_USEAPPL    "Application"

enum EStylesDir {
    ESTYLE_DIR_USESTD,
    ESTYLE_DIR_USEDIR ,
    ESTYLE_DIR_USEAPPL
};


class XsdPlugin;
class Element;
class UnicodeHelper;
class XSDManager;

class LIBQXMLEDITSHARED_EXPORT ClipboardElementList
{
    bool _deleteItems;
    QList<Element *> _elements;
public:
    ClipboardElementList(bool newDeleteItems, QList<Element *> &newElements);
    ~ClipboardElementList();

    QList<Element *> &elements();
};

class LIBQXMLEDITSHARED_EXPORT QXmlEditData : public QObject
{

    Q_OBJECT
protected:

    SearchManager _searchManager;

    //--- region(styles)
    static const QString XsltStyleName;
    static const QString XsltStyleDescription;

    QVector<VStyle*>  _styles;
    QVector<VStyle*>  _predefinedStyles;
    VStyle*  _defaultStyle;
    VStyle*  _xsltStyle;
    ColorManager _colorManager;
    //--- endregion(styles)

    QNetworkAccessManager _networkAccessManager ;
    bool _experimentalFeaturesEnabled;
    CopyAttributesManager _copyAttributesManager;
    QStringList _searchTerms;
    UnicodeHelper _unicodeHelper;

    //--- region(xslt)
    XsltManager _xsltManager;
    //--- endregion(xslt)

    //--- region(clipboard)
    Element *_clipBoardItem;
    QString _clipBoardKey;
    //--- endregion(clipboard)

    //--- region(files)
    QString _filePathForOperation;
    QStringList _lastFilesNames;
    //--- endregion(files)

    //--- region(data)
    DataInterface *_dataInterface;
    //--- endregion(data)

    //--- region(styleVersion)
    int _styleVersion;
    //--- endregion(styleVersion)

    //--- region(notify)
    ANotifier _notifier;
    //--- endregion(notify)

    //--- region(xsdMode)
    XSDManager *_xsdManager;
    //--- endregion(xsdMode)

    VStyle *createDefaultStyle();
    bool loadStyles();

public:
    QXmlEditData();
    virtual ~QXmlEditData();


    virtual void init();
    virtual void end();

    VStyle* getStyle(const QString &tag) const;
    VStyle *getPredefinedStyle(const QString &tag) const;
    VStyle* defaultStyle() const ;
    const QVector<VStyle*> &getStyles() const ;
    const QVector<VStyle*> &getPredefinedStyles() const;
    ColorManager *colorManager() ;

    EStylesDir getStylesDirLocation();
    void setStylesDirLocation(const EStylesDir type);

    QString cacheProgramDirectory();
    QString dataDirectory();

    QString getStylesDirSpecific();
    QString getStylesDirStandard();
    QString getStylesDirApplication();

    QString snippetsLocalDir();
    QString snippetsProgramDir();
    static QString getResourceDir();
    static QString getDocsDir();

    IQXmlEditPlugIn *xsdPlugin();

    //--- region(notify)
    ANotifier *notifier();
    //--- endregion(notify)

    //--- region(xsd)
    bool isAutovalidationOn();
    void setAutovalidationOn(const bool newState);
    //--- endregion(xsd)

    //--- region(xsdDisplay)
    bool isXsdDisplayHoriz();
    void setXsdDisplayHoriz(const bool value);
    //--- endregion(xsdDisplay)

    //--- region(behaviour)
    void enableAutoscroll(const bool enabled);
    bool isAutoscroll();
    //--- endregion(behaviour)

    //--- region(network)
    QNetworkAccessManager *xsdNetworkAccessManager() ;
    //--- endregion(network)

    QString predefinedStyleName();

    //--- region(experimental)
    bool areExperimentalFeaturesEnabled();
    void setExperimentalFeaturesEnabled(const bool value);
    //--- endregion(experimental)

    //--- region(copyAttributes)
    CopyAttributesManager *copyAttributesManager();
    //--- endregion(copyAttributes)

    //--- region(searchTerms)
    QStringList &searchTerms();
    //--- endregion(searchTerms)

    //--- region(xslt)
    XsltManager *xsltManager();
    bool isShowXSLTPanel();
    bool isAutoXSLTMode();
    void setShowXSLTPanel(const bool value);
    void setAutoXSLTMode(const bool value);
    //--- endregion(xslt)

    //--- region(metadata)
    static bool isUpdateMetadata();
    static void setUpdateMetadata(const bool value);
    //--- endregion(metadata)

    //--- region(prolog)
    bool isAutoInsertProlog();
    void setAutoInsertProlog(const bool value);
    QString autoInsertPrologEncoding();
    void setAutoInsertPrologEncoding(const QString &value);
    QString insertPrologEncoding();
    void setInsertPrologEncoding(const QString &value);
    QString defaultEncoding();
    //--- endregion(prolog)

    //--- region(styleVersion)
    void updateStyleVersion();
    int styleVersion();

    static const bool DefaultStyleFontBold = false ;
    //--- endregion(styleVersion)

    SearchManager *searchManager();

    //--- region(clipboard)
private slots:
    void onClipboardDataChanged();
signals:
    void clipboardDataChanged(bool hasData);
public:
    static const QString QXmlEditMimeDataFormat;

    Element *clipBoardItem();
    //QList<Element*> clipBoardItemList();
    ClipboardElementList *clipBoardItemList(const bool onlyElements = true);
    Element *internalClipBoardItem();
    void setClipBoardItem(Element *value, const QString &textualRepresentation);

    //--- region(files)
    static const int MaxEntriesLastFiles = 15;
    void setLastFileForOperation(const QString &lastFile);
    QString filePathForOperation(const QString &opFile);
    static QString sysFilePathForOperation(const QString &opFile);
    QStringList &lastFiles();
    bool addFileAccess(const QString &entry);
    //--- endregion(files)

    //--- region(data)
    virtual DataInterface *storageManager();
    virtual void setStorageManager(DataInterface *value);
    //--- endregion(data)

    //--- region(indentxml)
    static const int XmlIndentDefault = 1 ;
    int xmlIndent();
    void setXmlIndent(const int value);
    //--- endregion(indentxml)

    //--- region(xsdMode)
    XSDManager *xsdManager();
    //--- endregion(xsdMode)

    UnicodeHelper *unicodeHelper();


private:
    void cleanClipBoardData();
    void setClipBoardActionsState();
    //--- endregion(clipboard)
};


#endif // QXMLEDITDATA_H