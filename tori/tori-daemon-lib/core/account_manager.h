/**
 *
 * Copyright (c) 2012 mandel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <QScopedPointer>
#include <QDBusConnection>
#include <QDBusObjectPath>
#include <QObject>
#include <QVariantMap>
#include "dbus/dbus_helper.h"
#include "keyring/keyring.h"

namespace tori
{

namespace core
{

class AccountManagerPrivate;
class AccountManager : public QObject
{
    Q_DECLARE_PRIVATE(AccountManager)
    Q_OBJECT
public:
    explicit AccountManager(QDBusConnection connection,
        tori::keyring::Keyring* key, bool useDefault = false, QObject *parent = 0);
    ~AccountManager();

public slots:
    DBusObjectPathHash getAccounts();

Q_SIGNALS:
    void accountCreated(quint32 acc_id, QString accountName);
    void accountDeleted(quint32 acc_id, QString accountName);
    void accountUpdated(quint32 acc_id, QString accountName);

private:
    QScopedPointer<AccountManagerPrivate> d_ptr;

private:
    Q_PRIVATE_SLOT(d_func(), void onAccountCreated(quint32))
    Q_PRIVATE_SLOT(d_func(), void onAccountDeleted(quint32))
    Q_PRIVATE_SLOT(d_func(), void onAccountUpdated(quint32))

};

} // core

} // tori

#endif // ACCOUNT_MANAGER_H