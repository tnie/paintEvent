#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private slots:
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_actionp_triggered();
    void on_actionl_triggered();
};
#endif // MAINWINDOW_H
