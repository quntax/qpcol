#ifndef OPTIONS_H
#define OPTIONS_H

#ifdef USING_PCH
    #include "precompiled.h"
#else
    #include <QMap>
    #include <QString>
#endif

typedef QMap<QString, QString> CmdLineOptions;

enum Parameter {
    ApplicationSessionId,
    ApplicationSessionKey,
    LastScannedDirectory,
    DownloadDirectory,
    LastSearchQuery,
    LastProvider,
    CaptureClipboard,
    ColumnWidth_FileName,
    ColumnWidth_Tags,
    ColumnWidth_Size,
    DumpAudioDirectory,
    MplayerVideoOutput,
    MplayerVideoFilter,
    MplayerOsdLevel,
    OpenLastVideoPlayDir,
    PlaylistMode,
    NormalizedAudioVolume
};

extern QString SettingsMap[];

#endif // OPTIONS_H
