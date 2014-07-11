#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data.h"

class QListWidgetItem;
class MyListModel;
class QModelIndex;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_attendants_itemChanged(const QModelIndex &ib, const QModelIndex &ie);

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionExport_to_file_triggered();

    void on_actionImport_from_file_triggered();

private:
    Ui::MainWindow *ui;
    QList<Class> classes;
    MyListModel *lm;

    QList<QString> getShuffledPresentStudents();
    void doGrouping(QList<QString> s, int groupCount);
};

#endif // MAINWINDOW_H
