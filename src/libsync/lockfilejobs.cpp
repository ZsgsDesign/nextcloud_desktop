/*
 * Copyright (C) by Matthieu Gallien <matthieu.gallien@nextcloud.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include "lockfilejobs.h"

namespace OCC {

LockFileJob::LockFileJob(const AccountPtr account,
                         const QString &path,
                         const SyncFileItem::LockStatus requestedLockState,
                         QObject *parent)
    : AbstractNetworkJob(account, path, parent)
    , _requestedLockState(requestedLockState)
{
}

void LockFileJob::start()
{
    QNetworkRequest request;
    request.setRawHeader("X-User-Lock", "1");

    QByteArray verb;
    switch(_requestedLockState)
    {
    case SyncFileItem::LockStatus::LockedItem:
        verb = "LOCK";
        break;
    case SyncFileItem::LockStatus::UnlockedItem:
        verb = "UNLOCK";
        break;
    }
    sendRequest(verb, makeDavUrl(path()), request);

    AbstractNetworkJob::start();
}

bool LockFileJob::finished()
{
    if (reply()->error() != QNetworkReply::NoError) {
        Q_EMIT finishedWithError(reply());
    } else {
        Q_EMIT finishedWithoutError();
    }
    return true;
}

}
