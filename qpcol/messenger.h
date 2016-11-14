#ifndef MESSENGER_H
#define MESSENGER_H

/*******************************************************************************
 * Helper file, defining macros for printing messages, depending on build
 * mode and other defined conditions
 */

#ifdef QPCOL_RELEASE
#define QPCOL_MDEBUG(x) /* (x) */
#else
#define QPCOL_MDEBUG(args...) qDebug() << QString("%1:%2").arg(__FILE__).arg(__LINE__) << args
#endif

#endif // MESSENGER_H

