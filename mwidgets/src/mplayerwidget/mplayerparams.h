#ifndef MPLAYERPARAMS
#define MPLAYERPARAMS

#include <QObject>

class Vo : public QObject
{
        Q_OBJECT

    public:
        /**
         * Most of those drivers were not tested by me. Note that vaapi requires
         * also using vaapi filter, and mplayer with compiled in vaapi support.
         *
         * @brief The VideoOutput enum
         */
        enum VideoOutput {
            Xv,
            X11,
            Vaapi,
            Gl,
            Gl_nosw,
            Xover
        };

        Q_ENUMS(VideoOutput)
};

class Vf : public QObject
{
        Q_OBJECT

    public:
        /**
         * Actually, only this one is used (when using vaapi video output).
         * Otherwise - not needed, unless someone defines other filters
         *
         * @brief The VideoFilter enum
         */
        enum VideoFilter {
            Vaapi
        };

        Q_ENUMS(VideoFilter)
};

class Af : public QObject
{
    Q_OBJECT

public:
    /**
     * Audio filters for mplayer, this one is normalize volume and prevent
     * clipping
     */
    enum AudioFilter {
        NormalizeVolume
    };

    Q_ENUMS(AudioFilter)
};

#endif // MPLAYERPARAMS

