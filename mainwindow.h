#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class QListWidgetItem;

namespace Ui {
class MainWindow;
}

struct Class {
    QList<QString> students;
    QString name;
};

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

    void on_attendants_itemChanged(QListWidgetItem *item);

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QList<Class> classes;

    QList<QString> getShuffledPresentStudents();
    void doGrouping(QList<QString> s, int groupCount);
};

#endif // MAINWINDOW_H
