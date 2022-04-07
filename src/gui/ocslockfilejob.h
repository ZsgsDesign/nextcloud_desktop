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

#ifndef OCSLOCKFILEJOB_H
#define OCSLOCKFILEJOB_H

#include "ocsjob.h"

#include "accountfwd.h"

#include <QObject>

class QJsonDocument;

namespace OCC {

/**
 * @brief The OcsShareJob class
 * @ingroup gui
 *
 * Handle talking to the OCS Share API.
 * For creation, deletion and modification of shares.
 */
class OcsLockFileJob : public OcsJob
{
    Q_OBJECT
public:
    explicit OcsLockFileJob(const AccountPtr account);

    void acquireLock(const int fileId);

    void releaseLock(const int fileId);
};

}

#endif // OCSLOCKFILEJOB_H
