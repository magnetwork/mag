// Copyright (c) 2018-present The MAG developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "merchantdialog.h"
#include "ui_merchantdialog.h"
#include "optionsmodel.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtWidgets>
#include <QSettings>
#include <QDesktopServices>

#include <utilmoneystr.h>

MerchantDialog::MerchantDialog(QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowCloseButtonHint),
                                                          ui(new Ui::MerchantDialog),
                                                          model(new QStandardItemModel(0, 0, this))
{
    ui->setupUi(this);

    ui->labelMerchantImage->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->labelMerchantImage->setContentsMargins(0,0,0,0);
    ui->labelMerchantImage->setSizePolicy(QSizePolicy::MinimumExpanding,  QSizePolicy::MinimumExpanding);
    ui->labelStats1->setText(tr("Last <b>7 Days</b>:"));
    ui->labelStats2->setText(tr("Last <b>24 Hours</b>:"));
    ui->labelStats3->setText(tr("Total Transactions:"));
    ui->labelStats4->setText(tr("Total Merchants:"));

    ui->labelLoginEmail->setPlaceholderText(tr("Enter your email"));
    ui->labelLoginPassword->setPlaceholderText(tr("Enter your password"));
    ui->labelLoginPassword->setEchoMode(QLineEdit::Password);
    ui->labelLoginEmail->setFixedWidth(200);
    ui->labelLoginPassword->setFixedWidth(200);

    ui->merchantTransactions->setModel(model);
    ui->merchantTransactions->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->merchantTransactions->setAlternatingRowColors(true);
    ui->merchantTransactions->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->merchantTransactions->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->merchantTransactions->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QSizePolicy retain = ui->merchantTransactions->sizePolicy();
    retain.setRetainSizeWhenHidden(true);
    ui->merchantTransactions->setSizePolicy(retain);

    ui->merchantSignUp->setText("<a href=\"https://merchant.magnetwork.io/\">Sign up for MAG Merchant Account</a>");
    ui->merchantSignUp->setTextFormat(Qt::RichText);
    ui->merchantSignUp->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->merchantSignUp->setOpenExternalLinks(true);    

    networkManager = new QNetworkAccessManager();
    QObject::connect(networkManager, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QString answer = reply->readAll();
            if (!answer.isEmpty()) {
                QJsonDocument doc = QJsonDocument::fromJson(answer.toUtf8());
                if (doc.isObject()) {
                    QVariantMap map = doc.object().toVariantMap();
                    if (map.contains("ivusers")) {
                        // Process stats.
                        ui->labelStats1Amount->setText(map["iv7d"].toString() + tr(" MAG"));
                        ui->labelStats2Amount->setText(map["iv1d"].toString() + tr(" MAG"));
                        ui->labelStats3Amount->setText(map["ivcount"].toString());
                        ui->labelStats4Amount->setText(map["ivusers"].toString());
                        ui->labelStatsMerchantAmount->setText(map["ivtotal"].toString() + tr(" MAG"));
                    }
                    else if (map.contains("token")) {
                        // Process login.
                        if (map["token"].toString().isEmpty()) {
                            QMessageBox::information(this, tr("Failed Login."), map["error"].toString(), QMessageBox::Ok, QMessageBox::Ok);
                            token = QString();
                            updateMerchantUI();
                        }
                        else {                            
                            token = map["token"].toString();
                            refreshAccountData();
                        }
                    }
                    else if (map.contains("data")) {
                        QVariantMap dataMap = qvariant_cast<QVariantMap>(map["data"]);
                        ui->labelMerchantAmount->setText(dataMap["balance"].toString() + tr(" MAG"));
                        ui->labelMerchantNameValue->setText(dataMap["name"].toString());
                        ui->labelMerchantEmailValue->setText(dataMap["email"].toString());
                        ui->labelMerchantAddressValue->setText(dataMap["address"].toString());

                        // Proceed with invoices.
                        model->clear();
                        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Invoice ID")));
                        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Date")));
                        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Amount")));
                        model->setHorizontalHeaderItem(3, new QStandardItem(QString("Transaction ID")));
                        for (int header = 0; header < ui->merchantTransactions->horizontalHeader()->count(); ++header) {
                            ui->merchantTransactions->horizontalHeader()->setSectionResizeMode(header, QHeaderView::Stretch);
                        }
                        QVariantList invoices = dataMap["invoices"].toList();
                        int curItem = 0;
                        for (QVariantList::iterator it = invoices.begin(); it != invoices.end(); it++)  {
                            QDateTime timestamp;
                            timestamp.setTime_t(int(qvariant_cast<QVariantMap>(*it)["stamp"].toDouble()/1000));
                            model->setItem(curItem, 0, new QStandardItem(qvariant_cast<QVariantMap>(*it)["id"].toString()));
                            model->setItem(curItem, 1, new QStandardItem(timestamp.toString(Qt::SystemLocaleShortDate)));
                            model->setItem(curItem, 2, new QStandardItem(qvariant_cast<QVariantMap>(*it)["amount"].toString()));
                            model->setItem(curItem, 3, new QStandardItem(qvariant_cast<QVariantMap>(*it)["txid"].toString()));
                            curItem += 1;
                        }
                        updateMerchantUI();
                    }
                }
            }
        }
    );

    refreshStats();
    updateMerchantUI();
}

MerchantDialog::~MerchantDialog()
{
    delete ui;
    delete networkManager;
}

void MerchantDialog::updateMerchantUI()
{
    if (token.isEmpty()) {
        ui->horizontalSpacer_102->changeSize(40,20, QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->merchantTransactions->setVisible(false);
        ui->labelMerchantLoginStatus->setText(tr("Not logged in"));
        ui->labelMerchantBalance->setVisible(false);
        ui->labelMerchantAmount->setVisible(false);
        ui->labelMerchantName->setVisible(false);
        ui->labelMerchantNameValue->setVisible(false);
        ui->labelMerchantAddress->setVisible(false);
        ui->labelMerchantAddressValue->setVisible(false);
        ui->labelMerchantEmail->setVisible(false);
        ui->labelMerchantEmailValue->setVisible(false);
        ui->labelLoginEmail->setVisible(true);
        ui->labelLoginPassword->setVisible(true);
        ui->merchantSignUp->setVisible(true);
        ui->merchantSignIn->setVisible(true);
        ui->merchantSignOut->setVisible(false); 
        ui->merchantRefreshAccount->setVisible(false); 
    }
    else{
        ui->horizontalSpacer_102->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->merchantTransactions->setVisible(true);
        ui->labelMerchantLoginStatus->setText(tr(" "));
        ui->labelMerchantBalance->setVisible(true);
        ui->labelMerchantAmount->setVisible(true);
        ui->labelMerchantName->setVisible(true);
        ui->labelMerchantNameValue->setVisible(true);
        ui->labelMerchantAddress->setVisible(true);
        ui->labelMerchantAddressValue->setVisible(true);
        ui->labelMerchantEmail->setVisible(true);
        ui->labelMerchantEmailValue->setVisible(true);
        ui->labelLoginEmail->setVisible(false);
        ui->labelLoginPassword->setVisible(false);        
        ui->merchantSignUp->setVisible(false);
        ui->merchantSignIn->setVisible(false);
        ui->merchantSignOut->setVisible(true);  
        ui->merchantRefreshAccount->setVisible(true); 
    }
    ui->labelMerchantLoginStatus->repaint();
}

void MerchantDialog::on_merchantRefreshAccount_clicked()
{
    ui->labelMerchantLoginStatus->setText(tr("Refreshing please wait..."));
    ui->labelMerchantLoginStatus->repaint();
    refreshAccountData();
}

void MerchantDialog::on_refreshMagStats_clicked()
{
    refreshStats();
}

void MerchantDialog::on_merchantSignUp_clicked()
{
  //  QString link = "https://merchant.magnetwork.io/accounts/?up=true";
//    QDesktopServices::openUrl(QUrl(link));
}

void MerchantDialog::on_merchantWebsite_clicked()
{
    QString link = "https://merchant.magnetwork.io";
    QDesktopServices::openUrl(QUrl(link));
}

void MerchantDialog::on_merchantSignIn_clicked()
{
    bool cannotLogin = ui->labelLoginEmail->text().isEmpty() || ui->labelLoginPassword->text().isEmpty();
    if (!cannotLogin) {
        ui->labelMerchantLoginStatus->setText(tr("Signing In. Please wait..."));
        ui->labelMerchantLoginStatus->repaint();

        QNetworkRequest request;
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        request.setSslConfiguration(conf);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setUrl(QUrl("https://walletbackend.magnetwork.io:8711/.account/appsignin"));

        QJsonObject body;
        body.insert(QString("email"), ui->labelLoginEmail->text());
        body.insert(QString("password"), ui->labelLoginPassword->text());
        networkManager->post(request, QJsonDocument(body).toJson());
    }
    else {
        QMessageBox::information(this, tr("Error"), tr("Please enter both your password and email."), QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MerchantDialog::on_merchantSignOut_clicked()
{
    if (!token.isEmpty()) {
        QNetworkRequest request;
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        request.setSslConfiguration(conf);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setUrl(QUrl("https://walletbackend.magnetwork.io:8711/.account/appsignout"));

        QJsonObject body;
        body.insert(QString("token"), token);
        networkManager->post(request, QJsonDocument(body).toJson());
    }

    // Lose the token.
    token = QString();
    updateMerchantUI();
}

void MerchantDialog::keyPressEvent(QKeyEvent* event)
{
    if (event->key() != Qt::Key_Escape) // press esc -> ignore
    {
        this->QDialog::keyPressEvent(event);
    } else {
        event->ignore();
    }
}

void MerchantDialog::refreshStats()
{
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);

    request.setUrl(QUrl("https://walletbackend.magnetwork.io:8711/.tools/stats"));
    networkManager->post(request, "");
}


void MerchantDialog::refreshAccountData()
{
    if (!token.isEmpty()) {
        QNetworkRequest request;
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        request.setSslConfiguration(conf);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setUrl(QUrl("https://walletbackend.magnetwork.io:8711/.account/getdata"));

        QJsonObject body;
        body.insert(QString("token"), token);
        networkManager->post(request, QJsonDocument(body).toJson());
    }
}