#include <stdio.h>
#include <glib.h>

#include <QtGlobal>
#include <QThread>

#include "sipe-backend.h"

void qync_debug_info(sipe_debug_level level, const gchar *msg)
{
	switch (level) {
		case SIPE_DEBUG_LEVEL_INFO:
            qDebug("SIPE-D 0x%08x: %s\n", QThread::currentThreadId(), msg);
			break;
		case SIPE_DEBUG_LEVEL_WARNING:
            qWarning("SIPE-W 0x%08x: %s\n", QThread::currentThreadId(), msg);
			break;
		case SIPE_DEBUG_LEVEL_ERROR:
            qCritical("SIPE-C 0x%08x: %s", QThread::currentThreadId(), msg);
			break;
		case SIPE_DEBUG_LEVEL_FATAL:
            qFatal("SIPE-F 0x%08x: %s", QThread::currentThreadId(), msg);
			break;
	}
}

void sipe_backend_debug_literal(sipe_debug_level level,
				const gchar *msg)
{
	if (sipe_backend_debug_enabled()) {
        qync_debug_info(level, msg);
	}
}

void sipe_backend_debug(sipe_debug_level level,
			const gchar *format,
			...)
{
	va_list ap;

	va_start(ap,format);

	if (sipe_backend_debug_enabled()) {
		gchar *msg = g_strdup_vprintf(format, ap);
		sipe_backend_debug_literal(level, msg);
		g_free(msg);
	}

	va_end(ap);
}

gboolean sipe_backend_debug_enabled(void)
{
    return TRUE;
}

