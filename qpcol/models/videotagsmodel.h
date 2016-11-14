#ifndef VIDEOTAGSMODEL_H
#define VIDEOTAGSMODEL_H

#include <QStringListModel>
#include "tag.h"
#include "filmhandler.h"

class VideoTagsModel : public QStringListModel
{
        Q_OBJECT

    public:
        VideoTagsModel(int, QObject *parent = 0);

    private:
        TagCollection tc;
        QStringList tagNames;
        
};

#endif // VIDEOTAGSMODEL_H
