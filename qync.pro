TEMPLATE = subdirs

SUBDIRS += \
    qync \        # App project
    sipe-qync \   # sipe-qync lib

qync.depends = sipe-qync

