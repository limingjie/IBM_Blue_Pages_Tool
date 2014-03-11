#include "progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent)
    : QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    searchLabel = new QLabel();
    searchLabel->setText(tr("Searching..."));

    progressLabel = new QLabel();
    progressLabel->setText(tr("Spead..."));

    currentProgress = new QProgressBar();
    currentProgress->setTextVisible(false);

    overallProgress = new QProgressBar();
    overallProgress->setTextVisible(false);
    overallProgress->setMinimumWidth(390);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);
    buttonBox->setCenterButtons(true);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(searchLabel);
    vLayout->addWidget(progressLabel);
    vLayout->addWidget(currentProgress);
    vLayout->addWidget(overallProgress);
    vLayout->addWidget(buttonBox);
    vLayout->setSizeConstraint(QLayout::SetFixedSize);

    this->setLayout(vLayout);

    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    total = 0;
}

void ProgressDialog::setText(QString text)
{
    searchLabel->setText(tr("Searching \"") + text.left(39) + tr("\"..."));
}

void ProgressDialog::increase(int increase)
{
    total += increase;
}

void ProgressDialog::setCurrentProgress(int done, int total)
{
    currentProgress->setMaximum(total);
    currentProgress->setValue(done);

    progressLabel->setText(tr("Downloaded %1bytes (%2bytes in all)")
                           .arg(done).arg(this->total + done));
}

void ProgressDialog::setOverallProgress(int done, int total)
{
    overallProgress->setMaximum(total);
    overallProgress->setValue(done);
}
