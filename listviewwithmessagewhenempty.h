#ifndef LISTVIEWWITHMESSAGEWHENEMPTY_H
#define LISTVIEWWITHMESSAGEWHENEMPTY_H

#include <QListView>

// http://stackoverflow.com/a/20766271/266720
class ListViewWithMessageWhenEmpty : public QListView
{
    Q_OBJECT
    void paintEvent(QPaintEvent *e);
public:
    ListViewWithMessageWhenEmpty(QWidget* parent = 0) : QListView(parent) {}
};

#endif // LISTVIEWWITHMESSAGEWHENEMPTY_H
