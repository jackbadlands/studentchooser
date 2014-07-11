#include "listviewwithmessagewhenempty.h"

#include <QPainter>

void ListViewWithMessageWhenEmpty::paintEvent(QPaintEvent *e)
{
    QListView::paintEvent(e);
    if (model() && model()->rowCount(rootIndex())) return;
    // The view is empty.
    QPainter p(this->viewport());
    p.drawText(rect(), Qt::AlignCenter, "No students in this class so far.\nSwitch to 'manage' tab to add them.");
}
