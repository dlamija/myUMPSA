/********************************************************************************
** Form generated from reading UI file 'myumpsa.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYUMPSA_H
#define UI_MYUMPSA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_myUMPSA
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelLogo;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *username;
    QLineEdit *password;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBoxCheckINAuto;
    QCheckBox *checkBoxCheckOutBefore4pm;
    QCheckBox *checkBoxDisableOutside;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonSave;

    void setupUi(QDialog *myUMPSA)
    {
        if (myUMPSA->objectName().isEmpty())
            myUMPSA->setObjectName("myUMPSA");
        myUMPSA->resize(412, 349);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(myUMPSA->sizePolicy().hasHeightForWidth());
        myUMPSA->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(myUMPSA);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        groupBox = new QGroupBox(myUMPSA);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labelLogo = new QLabel(groupBox);
        labelLogo->setObjectName("labelLogo");
        labelLogo->setFrameShape(QFrame::Shape::Panel);
        labelLogo->setPixmap(QPixmap(QString::fromUtf8(":/images/icon2.icns")));

        horizontalLayout_2->addWidget(labelLogo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        username = new QLineEdit(groupBox);
        username->setObjectName("username");

        verticalLayout_2->addWidget(username);

        password = new QLineEdit(groupBox);
        password->setObjectName("password");
        password->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_2->addWidget(password);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_4->addWidget(groupBox);


        verticalLayout_4->addLayout(horizontalLayout_4);

        groupBox_2 = new QGroupBox(myUMPSA);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        horizontalLayout_5 = new QHBoxLayout(groupBox_2);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        checkBoxCheckINAuto = new QCheckBox(groupBox_2);
        checkBoxCheckINAuto->setObjectName("checkBoxCheckINAuto");

        verticalLayout_3->addWidget(checkBoxCheckINAuto);

        checkBoxCheckOutBefore4pm = new QCheckBox(groupBox_2);
        checkBoxCheckOutBefore4pm->setObjectName("checkBoxCheckOutBefore4pm");

        verticalLayout_3->addWidget(checkBoxCheckOutBefore4pm);

        checkBoxDisableOutside = new QCheckBox(groupBox_2);
        checkBoxDisableOutside->setObjectName("checkBoxDisableOutside");

        verticalLayout_3->addWidget(checkBoxDisableOutside);


        horizontalLayout_5->addLayout(verticalLayout_3);


        verticalLayout_4->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 21, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(118, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonDelete = new QPushButton(myUMPSA);
        pushButtonDelete->setObjectName("pushButtonDelete");

        horizontalLayout_3->addWidget(pushButtonDelete);

        pushButtonSave = new QPushButton(myUMPSA);
        pushButtonSave->setObjectName("pushButtonSave");

        horizontalLayout_3->addWidget(pushButtonSave);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(myUMPSA);

        QMetaObject::connectSlotsByName(myUMPSA);
    } // setupUi

    void retranslateUi(QDialog *myUMPSA)
    {
        myUMPSA->setWindowTitle(QCoreApplication::translate("myUMPSA", "myUMPSA", nullptr));
        groupBox->setTitle(QCoreApplication::translate("myUMPSA", "E-Community Credential", nullptr));
        labelLogo->setText(QString());
        label_3->setText(QCoreApplication::translate("myUMPSA", "Username:", nullptr));
        label_4->setText(QCoreApplication::translate("myUMPSA", "Password:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("myUMPSA", "Check IN/OUT", nullptr));
        checkBoxCheckINAuto->setText(QCoreApplication::translate("myUMPSA", "Auto Check IN", nullptr));
        checkBoxCheckOutBefore4pm->setText(QCoreApplication::translate("myUMPSA", "Disable Check Out before 4pm", nullptr));
        checkBoxDisableOutside->setText(QCoreApplication::translate("myUMPSA", "Disable outside UMPSA's network", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("myUMPSA", "Delete Settings", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("myUMPSA", "Save Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myUMPSA: public Ui_myUMPSA {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYUMPSA_H
