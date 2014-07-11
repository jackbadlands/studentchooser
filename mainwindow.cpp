#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylistmodel.h"


#include <QList>
#include <algorithm>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    classes.append(Class());
    Class &c = classes.last();
    c.name = "Example class";

    QSettings set("_Vi","studentchooser");

    int n = set.value("preview/count", 0).toInt();
    for(int i = 0; i < n; ++i) {
        Student s;
        s.name =    set.value(QString("preview/%1/name"   ).arg(i), "???").toString();
        s.present = set.value(QString("preview/%1/present").arg(i), false).toBool() ? Qt::Checked : Qt::Unchecked;
        c.students.append(s);
    }

    lm = new MyListModel(&c.students, this);

    ui->students->setModel(lm);
    ui->attendants->setModel(lm);
    //ui->classes->setModel(lm);

    connect(lm,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(on_attendants_itemChanged(QModelIndex,QModelIndex)));
    on_attendants_itemChanged(QModelIndex(), QModelIndex());
}

MainWindow::~MainWindow()
{
    delete ui;

    QSettings set("_Vi","studentchooser");
    set.setValue("preview/count", lm->rowCount(QModelIndex()));
    for(int i = 0; i < lm->rowCount(QModelIndex()); ++i) {
        bool present = (Qt::CheckState)lm->data(lm->index(i, 0), Qt::CheckStateRole).toUInt() == Qt::Checked;
        QString name = lm->data(lm->index(i, 0), Qt::DisplayRole).toString();
        set.setValue(QString("preview/%1/name"   ).arg(i), name);
        set.setValue(QString("preview/%1/present").arg(i), present);
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QModelIndex i = lm->addEntry("New student");
    ui->students->edit(i);
    ui->students->scrollTo(i);
}

void MainWindow::on_pushButton_4_clicked()
{
    foreach (QModelIndex i, ui->students->selectionModel()->selectedRows()) {
        lm->removeRow(i.row());
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    for(int i = 0; i < lm->rowCount(QModelIndex()); ++i) {
        lm->setData(lm->index(i, 0), QVariant(Qt::Checked), Qt::CheckStateRole);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    for(int i = 0; i < lm->rowCount(QModelIndex()); ++i) {
        lm->setData(lm->index(i, 0), QVariant(Qt::Unchecked), Qt::CheckStateRole);
    }
}

void MainWindow::on_attendants_itemChanged(const QModelIndex &ib, const QModelIndex &ie)
{
    (void)ib; (void)ie;// FIXME: ineffectinve O(n*n) update
    int present = 0;
    int absent = 0;
    for(int i = 0; i < lm->rowCount(QModelIndex()); ++i) {
        if ((Qt::CheckState)lm->data(lm->index(i, 0), Qt::CheckStateRole).toUInt() == Qt::Checked) {
            ++present;
        } else {
            ++absent;
        }
    }
    ui->absenseStats->setText(tr("%1 students present, %2 students absent").arg(present).arg(absent));
}

QList<QString> MainWindow::getShuffledPresentStudents()
{
    QList<QString> presentStudents;
    for(int i = 0; i < lm->rowCount(QModelIndex()); ++i) {
        if ((Qt::CheckState)lm->data(lm->index(i, 0), Qt::CheckStateRole).toUInt() == Qt::Checked) {
            presentStudents.append(lm->data(lm->index(i, 0), Qt::DisplayRole).toString());
        }
    }

    std::random_shuffle(presentStudents.begin(), presentStudents.end());
    return presentStudents;
}

void MainWindow::doGrouping(QList<QString> s, int groupCount)
{
    int n = s.length();

    ui->result->clear();
    ui->result->setColumnCount(groupCount);
    ui->result->setRowCount(n/groupCount + 1);

    int x = 0;
    int currentColumn = 0;
    int currentRow = 0;
    foreach (QString i, s) {
        QTableWidgetItem *it = new QTableWidgetItem(i);
        ui->result->setItem(currentRow, currentColumn, it);
        ++currentRow;

        // n / groupCount;

        x+=groupCount;
        if (x >= n && currentColumn < groupCount-1) {
            currentRow = 0;
            currentColumn += 1;
            x -= n;
        }
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    QList<QString> s = getShuffledPresentStudents();
    int groupCount = ui->desiredSGcount->text().toInt();
    doGrouping(s, groupCount);
}

void MainWindow::on_pushButton_7_clicked()
{
    QList<QString> s = getShuffledPresentStudents();
    int n = s.length();
    if (n == 0) return;
    int desiredGroupSize = ui->desiredSGsize->text().toInt();

    int groupCountCandidate = n / desiredGroupSize;
    int groupCountRemainder = n % desiredGroupSize;

    if (groupCountRemainder != 0) {
        if (ui->radioPreferIncomplete->isChecked()) {
            ++groupCountCandidate;
        } else
        if (ui->radioBalanced->isChecked()) {
            if (groupCountRemainder - 1 < desiredGroupSize/2) {
                // prefer extended
            } else {
                // prefer incomplete
                ++groupCountCandidate;
            }
        }
    }

    if (groupCountCandidate == 0) ++groupCountCandidate;

    doGrouping(s, groupCountCandidate);
}
