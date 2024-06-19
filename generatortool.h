#ifndef GENERATORTOOL_H
#define GENERATORTOOL_H

#include <QDialog>
#include <common/BaseWindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class GeneratorTool;
}
QT_END_NAMESPACE

class GeneratorTool : public BaseWindow
{
    Q_OBJECT

public:
    GeneratorTool(QWidget *parent = nullptr);
    ~GeneratorTool();

    QString calculateMd5(const QString &input);
    bool generateKeyPair(const QString &publicKeyPath, const QString &privateKeyPath);
private slots:
    void on_btn_generate_clicked();
    void on_btn_open_location_clicked();
    void on_btn_save_clicked();

private:
    Ui::GeneratorTool *ui;
    QWidget* bg;

    QString publicFile = "";
    QString privateFile = "";

    QString publicKeyPath = "";
    QString privateKeyPath = "";
};
#endif // GENERATORTOOL_H
