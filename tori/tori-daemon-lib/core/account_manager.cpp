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

#include <QVariant>
#include <Accounts/Manager>
#include "account_manager.h"

namespace tori
{

namespace core
{


class AccountManagerPrivate
{

    Q_DECLARE_PUBLIC(AccountManager)

public:
    AccountManagerPrivate(AccountManager* parent);

    QHash<QString, QDBusObjectPath> getAccounts();

protected:
    void onAccountCreated(Accounts::AccountId);
    void onAccountDeleted(Accounts::AccountId);
    void onAccountUpdated(Accounts::AccountId);

private:
    bool isTwitterAccount(Accounts::AccountId acc_id);

    static QString BASE_ACCOUNT_URL;
private:
    AccountManager* q_ptr;
    Accounts::Manager* _man;
};

QString AccountManagerPrivate::BASE_ACCOUNT_URL = "%1";

AccountManagerPrivate::AccountManagerPrivate(AccountManager* parent) :
    q_ptr(parent)
{
    Q_Q(AccountManager);
    _man = new Accounts::Manager("microblogging");

    // do connect the signals so that we can let people know changes happened
    q->connect(_man, SIGNAL(accountCreated(Accounts::AccountId)),
        q, SLOT(onAccountCreated(Accounts::AccountId)));
    q->connect(_man, SIGNAL(accountUpdated(Accounts::AccountId)),
        q, SLOT(onAccountUpdated(Accounts::AccountId)));
    q->connect(_man, SIGNAL(accountRemoved(Accounts::AccountId)),
        q, SLOT(onAccountDeleted(Accounts::AccountId)));
}

bool AccountManagerPrivate::isTwitterAccount(Accounts::AccountId acc_id)
{
    Accounts::Account* acc = _man->account(acc_id);
    return acc->providerName() == "twitter";
}

QHash<QString, QDBusObjectPath> AccountManagerPrivate::getAccounts()
{
    QHash<QString, QDBusObjectPath> accounts;

    // loop and just add those accounts from twitter
    Accounts::AccountIdList allAccounts = _man->accountList();

    for(int pos = 0; pos < allAccounts.length(); ++pos)
    {
        Accounts::Account* acc = _man->account(allAccounts.at(pos));
        if(acc->providerName() == "twitter")
        {
            accounts[acc->displayName()] = QDBusObjectPath(
                AccountManagerPrivate::BASE_ACCOUNT_URL.arg(QString::number(acc->id())));
        }
    }
    return accounts;
}

void AccountManagerPrivate::onAccountCreated(Accounts::AccountId acc_id)
{
    Q_Q(AccountManager);
    if(isTwitterAccount(acc_id))
    {
        Accounts::Account* acc = _man->account(acc_id);
        emit q->accountCreated(acc->id(), acc->displayName());
    }
}

void AccountManagerPrivate::onAccountDeleted(Accounts::AccountId acc_id)
{
    Q_Q(AccountManager);
    if(isTwitterAccount(acc_id))
    {
        Accounts::Account* acc = _man->account(acc_id);
        emit q->accountDeleted(acc->id(), acc->displayName());
    }
}

void AccountManagerPrivate::onAccountUpdated(Accounts::AccountId acc_id)
{
    Q_Q(AccountManager);
    if(isTwitterAccount(acc_id))
    {
        Accounts::Account* acc = _man->account(acc_id);
        emit q->accountUpdated(acc->id(), acc->displayName());
    }
}

AccountManager::AccountManager(QObject *parent) :
    QObject(parent),
    d_ptr(new AccountManagerPrivate(this))
{
}

AccountManager::~AccountManager()
{
}

QHash<QString, QDBusObjectPath> AccountManager::getAccounts()
{
    Q_D(AccountManager);
    return d->getAccounts();
}




} // core

} // tori

#include "moc_account_manager.cpp"
