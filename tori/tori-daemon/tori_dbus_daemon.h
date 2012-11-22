/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c TodiDBusDaemon -a tori_dbus_daemon.h:tori_dbus_daemon.cpp com.saruneko.tori.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef TORI_DBUS_DAEMON_H
#define TORI_DBUS_DAEMON_H

#include <QtCore/QObject>
#include <QVariantMap>

#include "twitter/account_manager.h"

class ToriDBusDaemon : public QObject
{
    Q_OBJECT

public:
    ToriDBusDaemon(QObject *parent = 0);
    virtual ~ToriDBusDaemon() {}

    void emitOAuthPinUrl(const QString &pinUrl, uint accountId, const QString &username);
    void emitAuthenticated(uint accountId, QString &username);

public Q_SLOTS:
    /**
     * \brief Return all the twitter accounts that have been added to the system.
     *
     * The method returns all the twitter accounts that have been register to the online-accounts
     * service in the system. The result is a dictionay with the username of the account and its
     * unique id in the system.
     */
    QVariantMap getAccounts();

    /**
     * \brief Authenticate the twitter account with the given id.
     *
     * The method with authenticate the account and will store the token and token secrets in the
     * users keyring.
     */
    void authenticate(uint accountId);

    /**
     * \brief Set the pin to be used to authenticate an account against twitter.
     *
     * Allows the application to authenticate agains twitter and get the token and token secret
     * that can be used to access the account.
     */
    void setPin(const QString &pin, uint accountId);

Q_SIGNALS:

    /**
     * \brief Signal raised when the user provides the pin for a given account. This signal is not exposed
     *        via DBus.
     */
    void pinReceived(const QString &pin, uint accountId);

    // dbus signals

    /**
     * \brief Signal raised when a new twitter account is created in the system.
     */
    void accountCreated(uint accountId);

    /**
     * \brief Signal raised when a twitter account is removed from the system.
     */
    void accountDeleted(uint accountId);

    void accountUpdated(uint accountId);

    void authenticated(uint accountId, const QString &username);

    /**
     * \brief Signal raised when the authentication required the pin input from the user.
     */
    void oauthPinUrl(const QString &pinUrl, uint accountId, const QString &username);

private:
    AccountManager* _man;
};

#endif
