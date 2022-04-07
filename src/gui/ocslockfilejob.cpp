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

#include "ocslockfilejob.h"

#include "account.h"

namespace OCC {

OcsLockFileJob::OcsLockFileJob(const AccountPtr account)
    : OcsJob(account)
{
    setPath("ocs/v2.php/apps/files_lock/lock/");
}

void OCC::OcsLockFileJob::acquireLock(const int fileId)
{
    appendPath(QString::number(fileId));
    setVerb("PUT");

    start();
}

void OcsLockFileJob::releaseLock(const int fileId)
{
    appendPath(QString::number(fileId));
    setVerb("DELETE");

    start();
}

}
