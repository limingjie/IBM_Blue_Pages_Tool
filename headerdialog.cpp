#include "headerdialog.h"

HeaderDialog::HeaderDialog(QWidget *parent)
    : QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    listWidget = new QListWidget();
    listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    topButton = new QPushButton();
    topButton->setText(tr("To top"));

    upButton = new QPushButton();
    upButton->setText(tr("Move up"));

    downButton = new QPushButton();
    downButton->setText(tr("Move down"));

    bottomButton = new QPushButton();
    bottomButton->setText(tr("To bottom"));

    checkAllButton = new QPushButton();
    checkAllButton->setText(tr("Check All"));

    checkButton = new QPushButton();
    checkButton->setText(tr("Check Selected"));

    uncheckButton = new QPushButton();
    uncheckButton->setText(tr("Uncheck Selected"));

    okButton = new QPushButton();
    okButton->setText(tr("Save"));
    okButton->setDefault(true);

    cancelButton = new QPushButton();
    cancelButton->setText(tr("Cancel"));

    rightLayout = new QVBoxLayout();
    rightLayout->addWidget(topButton);
    rightLayout->addWidget(upButton);
    rightLayout->addWidget(downButton);
    rightLayout->addWidget(bottomButton);
    rightLayout->addWidget(checkButton);
    rightLayout->addWidget(uncheckButton);
    rightLayout->addWidget(checkAllButton);
    rightLayout->addStretch();
    rightLayout->addWidget(okButton);
    rightLayout->addWidget(cancelButton);

    hLayout = new QHBoxLayout();
    hLayout->addWidget(listWidget, 1);
    hLayout->addLayout(rightLayout, 0);

    this->setLayout(hLayout);
    this->setMinimumHeight(480);

    buttonState();

    connect(okButton,       SIGNAL(clicked()), this, SLOT(saveChanges()));
    connect(okButton,       SIGNAL(clicked()), this, SLOT(close()));
    connect(cancelButton,   SIGNAL(clicked()), this, SLOT(close()));
    connect(topButton,      SIGNAL(clicked()), this, SLOT(top()));
    connect(upButton,       SIGNAL(clicked()), this, SLOT(up()));
    connect(downButton,     SIGNAL(clicked()), this, SLOT(down()));
    connect(bottomButton,   SIGNAL(clicked()), this, SLOT(bottom()));
    connect(checkAllButton, SIGNAL(clicked()), this, SLOT(checkAll()));
    connect(checkButton,    SIGNAL(clicked()), this, SLOT(checkSelected()));
    connect(uncheckButton,  SIGNAL(clicked()), this, SLOT(uncheckSelected()));
    connect(listWidget,     SIGNAL(itemSelectionChanged()), this, SLOT(buttonState()));
}

void HeaderDialog::setValues(QList<QString> *columns, QList<QString> *headers)
{
    int i, size = columns->size();

    this->columns = columns;
    this->headers = headers;

    QListWidgetItem *item;
    for(i = 0; i < size; i++)
    {
        item = new QListWidgetItem(columns->at(i));

        if(headers->contains(columns->at(i)))
        {
            item->setCheckState(Qt::Checked);
        }
        else
        {
            item->setCheckState(Qt::Unchecked);
        }

        listWidget->addItem(item);
    }
}

void HeaderDialog::saveChanges()
{
    int i, count = listWidget->count();
    QListWidgetItem *item;

    columns->clear();
    headers->clear();

    for(i = 0; i < count; i++)
    {
        item = listWidget->item(i);
        columns->append(item->text());
        if(item->checkState() == Qt::Checked)
        {
            headers->append(item->text());
        }
    }

    emit accepted();
}

void HeaderDialog::top()
{
    size_t i, count, index;
    QListWidgetItem *item;

    count = listWidget->count();
    index = 0;
    for(i = 0; i < count; i++)
    {
        item = listWidget->item(i);
        if(item->isSelected())
        {
            item = listWidget->takeItem(i);
            listWidget->insertItem(index++, item);
            item->setSelected(true);
        }
    }

    listWidget->setFocus();
}

void HeaderDialog::up()
{
    size_t i, count, index;
    QListWidgetItem *item;

    count = listWidget->count();
    index = 0;
    for(i = 0; i < count; i++)
    {
        item = listWidget->item(i);
        if(item->isSelected() && i > index++)
        {
            item = listWidget->takeItem(i);
            listWidget->insertItem(i - 1, item);
            item->setSelected(true);
        }
    }

    listWidget->setFocus();
}

void HeaderDialog::down()
{
    int i, index;
    size_t count;
    QListWidgetItem *item;

    count = listWidget->count();
    index = count - 1;
    for(i = count - 1; i >= 0; i--)
    {
        item = listWidget->item(i);
        if(item->isSelected() && i < index--)
        {
            item = listWidget->takeItem(i);
            listWidget->insertItem(i + 1, item);
            item->setSelected(true);
        }
    }

    listWidget->setFocus();
}

void HeaderDialog::bottom()
{
    int i;
    size_t count, index;
    QListWidgetItem *item;

    count = listWidget->count();
    index = count - 1;
    for(i = count - 1; i >= 0; i--)
    {
        item = listWidget->item(i);
        if(item->isSelected())
        {
            item = listWidget->takeItem(i);
            listWidget->insertItem(index--, item);
            item->setSelected(true);
        }
    }

    listWidget->setFocus();
}

void HeaderDialog::checkAll()
{
    size_t count = listWidget->count();
    size_t i;

    for(i = 0; i < count; i++)
    {
        listWidget->item(i)->setCheckState(Qt::Checked);
    }

    listWidget->setFocus();
}

void HeaderDialog::checkSelected()
{
    QList<QListWidgetItem *> list = listWidget->selectedItems();
    size_t count = list.count();
    size_t i;

    for(i = 0; i < count; i++)
    {
        list[i]->setCheckState(Qt::Checked);
    }

    listWidget->setFocus();
}

void HeaderDialog::uncheckSelected()
{
    QList<QListWidgetItem *> list = listWidget->selectedItems();
    size_t count = list.count();
    size_t i;

    for(i = 0; i < count; i++)
    {
        list[i]->setCheckState(Qt::Unchecked);
    }

    listWidget->setFocus();
}

void HeaderDialog::buttonState()
{
    if(listWidget->selectedItems().count() > 0)
    {
        topButton->setEnabled(true);
        upButton->setEnabled(true);
        downButton->setEnabled(true);
        bottomButton->setEnabled(true);
        checkButton->setEnabled(true);
        uncheckButton->setEnabled(true);
    }
    else
    {
        topButton->setEnabled(false);
        upButton->setEnabled(false);
        downButton->setEnabled(false);
        bottomButton->setEnabled(false);
        checkButton->setEnabled(false);
        uncheckButton->setEnabled(false);
    }
}
