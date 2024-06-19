#include "Toast.h"
#include "generatortool.h"
#include "ui_generatortool.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QSslSocket>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <QFile>
#include <QDir>
#include <QDesktopServices>
#include <QDateTime>
#include <QFileDialog>

GeneratorTool::GeneratorTool(QWidget *parent) : BaseWindow(parent) , ui(new Ui::GeneratorTool)
{
    ui->setupUi(this);
    // qDebug()<<QSslSocket::sslLibraryBuildVersionString();

    // QString input = "Hello, World!";
    // QString md5Hash = calculateMd5(input);
    // qDebug() << "MD5 Hash of: " << input << " is:" << md5Hash;

    // qDebug() << "QDir=" << QDir::currentPath();

    //标题栏
    this->m_TitleBar->setButtonType(MIN_BUTTON);
    this->m_TitleBar->set_width(this->width());
    this->m_TitleBar->show_windows();
    this->m_TitleBar->setTitle("Key Pair Generator Tool");
    connect(m_TitleBar, &TitleBar::signalButtonCloseClicked, this, [=](){
        QCoreApplication::quit();
    });

    bg = new QWidget(this);
    bg->setObjectName("bg");
    bg->resize(this->width() - 8,this->height()-8 - this->m_TitleBar->height());
    bg->move(4,4+this->m_TitleBar->height());
    bg->setStyleSheet("#bg{background:#F6F7F9;border-top:1px solid #D4D5D8;}");
    bg->lower();
}

GeneratorTool::~GeneratorTool()
{
    delete ui;
}

QString GeneratorTool::calculateMd5(const QString &input)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(input.toLocal8Bit());
    return hash.result().toHex();
}

bool GeneratorTool::generateKeyPair(const QString &publicKeyPath, const QString &privateKeyPath)
{
    int				ret = 0;
    RSA				*r = NULL;
    BIGNUM			*bne = NULL;
    BIO				*bp_public = NULL, *bp_private = NULL;

    int				bits = 2048;
    unsigned long	e = RSA_F4;

    // 1. generate rsa key
    bne = BN_new();
    ret = BN_set_word(bne,e);
    if(ret != 1){
        goto free_all;
    }

    r = RSA_new();
    ret = RSA_generate_key_ex(r, bits, bne, NULL);
    if(ret != 1){
        goto free_all;
    }

    // 2. save public key
    bp_public = BIO_new_file(publicKeyPath.toStdString().c_str(), "w+");
    ret = PEM_write_bio_RSAPublicKey(bp_public, r);
    if(ret != 1){
        goto free_all;
    }

    // 3. save private key
    bp_private = BIO_new_file(privateKeyPath.toStdString().c_str(), "w+");
    ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

// 4. free
free_all:

    BIO_free_all(bp_public);
    BIO_free_all(bp_private);
    RSA_free(r);
    BN_free(bne);

    return (ret == 1);
}

void GeneratorTool::on_btn_generate_clicked()
{
    ui->btn_generate->setText("Loading...");

    QDateTime currentDateTime  =  QDateTime :: currentDateTime();
    QString currentTime  =  currentDateTime.toString( "yyyyMMdd_hh_mm_ss" );

    publicFile = "public_key."+currentTime+".pem";
    privateFile = "private_key."+currentTime+".pem";

    publicKeyPath = QApplication::applicationDirPath() + QDir::separator() + publicFile;
    privateKeyPath = QApplication::applicationDirPath() + QDir::separator() + privateFile;
    generateKeyPair(publicKeyPath,privateKeyPath);

    QFile public_file(publicKeyPath);
    public_file.open(QIODeviceBase::ReadOnly);
    QString public_content = public_file.readAll();
    public_file.close();
    ui->PublicTextEdit->appendPlainText(public_content);

    QFile private_file(privateKeyPath);
    private_file.open(QIODeviceBase::ReadOnly);
    QString private_content = private_file.readAll();
    private_file.close();
    ui->PrivateTextEdit->appendPlainText(private_content);

    Toast::succ("已生成");
    ui->btn_generate->setText("Generate key pair");
}


void GeneratorTool::on_btn_open_location_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("file:///")+QApplication::applicationDirPath()));
}


void GeneratorTool::on_btn_save_clicked()
{
    QString folder= QFileDialog::getExistingDirectory(this,"Choose Folder");

    if (!folder.isEmpty())
    {
        QFile public_file(publicKeyPath);
        public_file.copy(folder + QDir::separator() + publicFile);

        QFile private_file(privateKeyPath);
        private_file.copy(folder + QDir::separator() + privateFile);
        Toast::succ("已复制");
    }
}

