#ifndef LOCKFILEJOBS_H
#define LOCKFILEJOBS_H

#include "abstractnetworkjob.h"

#include "syncfileitem.h"

namespace OCC {

class OWNCLOUDSYNC_EXPORT LockFileJob : public AbstractNetworkJob
{
    Q_OBJECT

public:
    explicit LockFileJob(const AccountPtr account,
                         const QString &path,
                         const SyncFileItem::LockStatus requestedLockState,
                         QObject *parent = nullptr);
    void start() override;

signals:
    void finishedWithError(QNetworkReply *reply);
    void finishedWithoutError();

private:
    bool finished() override;

    SyncFileItem::LockStatus _requestedLockState = SyncFileItem::LockStatus::LockedItem;
};

}

#endif // LOCKFILEJOBS_H
