#pragma once

#include <QtCore/qglobal.h>

#if defined(ZOMBIETILES_LIBRARY)
#define ZOMBIETILES_EXPORT Q_DECL_EXPORT
#else
#  define ZOMBIETILES_EXPORT Q_DECL_IMPORT
#endif
