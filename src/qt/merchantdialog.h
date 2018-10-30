// Copyright (c) 2018-present The MAG developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_MERCHANTDIALOG_H
#define BITCOIN_QT_MERCHANTDIALOG_H

#include "guiutil.h"

#include <QDialog>
#include <QHeaderView>
#include <QItemSelection>
#include <QKeyEvent>
#include <QMenu>
#include <QPoint>
#include <QTimer>
#include <QVariant>
#include <QNetworkAccessManager>
#include <QStandardItemModel>

class OptionsModel;
class WalletModel;

namespace Ui
{
class MerchantDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog for merchants management */
class MerchantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MerchantDialog(QWidget* parent = 0);
    ~MerchantDialog();

    void setModel(WalletModel* model) {};
    void showOutOfSyncWarning(bool fShow) {};

protected:
    virtual void keyPressEvent(QKeyEvent* event);

private:
    Ui::MerchantDialog* ui;
    GUIUtil::TableViewLastColumnResizingFixer* columnResizingFixer;
    QMenu* contextMenu;
    QString token;

    CAmount currentBalance;
    CAmount currentUnconfirmedBalance;
    CAmount currentImmatureBalance;
    CAmount currentZerocoinBalance;
    CAmount currentUnconfirmedZerocoinBalance;
    CAmount currentImmatureZerocoinBalance;
    CAmount currentWatchOnlyBalance;
    CAmount currentWatchUnconfBalance;
    CAmount currentWatchImmatureBalance;

    QNetworkAccessManager* networkManager;
    QStandardItemModel* model;

    void refreshStats();
    void updateMerchantUI();
    void refreshAccountData();  
    
private slots:
    void on_merchantSignIn_clicked();
    void on_refreshMagStats_clicked();
    void on_merchantSignOut_clicked();
    void on_merchantWebsite_clicked();
    void on_merchantSignUp_clicked();
    void on_merchantRefreshAccount_clicked();

};

#endif // BITCOIN_QT_MERCHANTDIALOG_H
