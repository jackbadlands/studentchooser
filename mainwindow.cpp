#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QList>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QListWidgetItem* item;

    classes.append(Class());
    Class &c = classes.last();
    c.name = "Example class";
    c.students.append("mist");
    c.students.append("spank");
    c.students.append("bob");
    c.students.append("alice");
    c.students.append("malice");
    c.students.append("kill");
    c.students.append("dragon");

    item = new QListWidgetItem("234", ui->attendants);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->students->addItem("New student");
    QListWidgetItem* i = ui->students->item(ui->students->count()-1);
    i->setFlags (i->flags () | Qt::ItemIsEditable);
    ui->students->editItem(i);
    ui->students->scrollToItem(i);
}

void MainWindow::on_pushButton_4_clicked()
{
    foreach (QListWidgetItem *i, ui->students->selectedItems()) {
        delete i;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    for(int i = 0; i < ui->attendants->count(); ++i) {
        ui->attendants->item(i)->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    for(int i = 0; i < ui->attendants->count(); ++i) {
        ui->attendants->item(i)->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_attendants_itemChanged(QListWidgetItem *item)
{
    (void)item; // FIXME: ineffectinve O(n*n) update
    int present = 0;
    int absent = 0;
    for(int i = 0; i < ui->attendants->count(); ++i) {
        if (ui->attendants->item(i)->checkState() == Qt::Checked) {
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
    for(int i = 0; i < ui->attendants->count(); ++i) {
        QListWidgetItem *it = ui->attendants->item(i);
        if (it->checkState() == Qt::Checked) {
            presentStudents.append(it->text());
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

    if (groupCountRemainder != 0 && ui->radioPreferExtended->isChecked()) {
        ++groupCountCandidate;
    }
    if (groupCountCandidate == 0) ++groupCountCandidate;

    doGrouping(s, groupCountCandidate);
}
