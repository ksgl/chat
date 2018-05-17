#ifndef CHATLIB_GLOBAL_H
#define CHATLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CHATLIB_LIBRARY)
#  define CHATLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHATLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CHATLIB_GLOBAL_H
