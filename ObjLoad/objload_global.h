#ifndef OBJLOAD_GLOBAL_H
#define OBJLOAD_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>
#include <QStringList>

#if defined(OBJLOAD_LIBRARY)
#  define OBJLOADSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OBJLOADSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OBJLOAD_GLOBAL_H
