#ifndef MWIDGETS_H
#define MWIDGETS_H

#include "mwidgets_global.h"

#ifdef __cplusplus {
extern "C" {
#if defined(FLATSTYLE)
    #include <FlatStyle>
#endif

#if defined(QHTTPREQUEST)
    #include <QHttpRequest>
#endif

#if defined(MEDIAWIDGET)
    #include <MediaWidget>
#endif

#if defined(MPLAYERWIDGET)
    #include <MplayerWidget>
#endif

#if defined(PTABLE)
    #include <PTable>
#endif

#if defined(HTMLEXTRACT)
    #include <HtmlExtract>
#endif
}
#endif

//namespace MWidgets {
#if defined(FLATSTYLE)
    class MWIDGETSSHARED_EXPORT fsContainer;
    class MWIDGETSSHARED_EXPORT fsLabel;
    class MWIDGETSSHARED_EXPORT fsButton;
    class MWIDGETSSHARED_EXPORT fsSeparator;
#endif
#if defined(QHTTPREQUEST)
    class MWIDGETSSHARED_EXPORT QHttpRequestAbstract;
    class MWIDGETSSHARED_EXPORT QHttpRequest;
    class MWIDGETSSHARED_EXPORT QHttpRequestProxy;
    class MWIDGETSSHARED_EXPORT QHttpDownload;
    class MWIDGETSSHARED_EXPORT QHttpHash;
#endif
#if defined(MEDIAWIDGET)
    class MWIDGETSSHARED_EXPORT MediaWidget;
    class MWIDGETSSHARED_EXPORT MediaPlayer;
    class MWIDGETSSHARED_EXPORT DownloadDialog;
    class MWIDGETSSHARED_EXPORT MediaWidgetPlugin;
#endif
#if defined(MPLAYERWIDGET)
    class MWIDGETSSHARED_EXPORT Vo;
    class MWIDGETSSHARED_EXPORT Vf;
    class MWIDGETSSHARED_EXPORT MplayerDispatcher;
    class MWIDGETSSHARED_EXPORT MplayerProcess;
    class MWIDGETSSHARED_EXPORT MplayerWidget;
    class MWIDGETSSHARED_EXPORT MplayerWidgetPlugin;
#endif
#if defined(PTABLE)
    class MWIDGETSSHARED_EXPORT PTableWidget;
    class MWIDGETSSHARED_EXPORT PTableView;
    class MWIDGETSSHARED_EXPORT PTableWidgetPlugin;
    class MWIDGETSSHARED_EXPORT PTableViewPlugin;
#endif
#if defined(HTMLEXTRACT)
    class MWIDGETSSHARED_EXPORT HtmlExtract;
    class MWIDGETSSHARED_EXPORT FileContents;
#endif
    class MWIDGETSSHARED_EXPORT MWidgetsPlugin;
//}

//Q_DECLARE_INTERFACE(MWidgets::MediaWidget, "org.eu.merlin.Qt.MWidgetsPlugin.MediaWidget")

#endif // MWIDGETS_H
