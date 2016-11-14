#ifndef PROVIDERS_H
#define PROVIDERS_H

#include "girlfriendvideos.h"
#include "hotpornshow.h"
#include "meendo.h"
#include "moviesand.h"
#include "pornhub.h"
#include "redtube.h"
#include "slutload.h"
#include "stileproject.h"
#include "submityourflicks.h"
#include "tube8.h"
#include "xflogger.h"
#include "xhamster.h"
#include "xvideos.h"
#include "youjizz.h"
#include "youporn.h"

enum Provider {
//    p_Girlfriendvideos,
//    p_Hotpornshow,
//    p_Meendo,
//    p_Moviesand,
//    p_Pornhub,
//    p_Redtube,
//    p_Slutload,
//    p_Stileproject,
//    p_Submityourflicks,
//    p_Tube8,
//    p_Xflogger,
    p_Xhamster,
    p_Xvideos,
//    p_Youjizz,
//    p_Youporn
};

typedef QHash<QString, Provider> ProviderMap;

Q_DECLARE_METATYPE(ProviderMap)

#endif // PROVIDERS_H
