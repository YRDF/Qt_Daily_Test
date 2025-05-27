/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *TopWidget;
    QHBoxLayout *horizontalLayout;
    ClickedBtn *OpenBtn;
    ClickedBtn *SaveBtn;
    ClickedBtn *CloseBtn;
    QSpacerItem *horizontalSpacer;
    QWidget *MidWidget;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEdit;
    QWidget *BotWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *time_lab;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *show_line_label;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(617, 517);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/yrdf.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TopWidget = new QWidget(Widget);
        TopWidget->setObjectName("TopWidget");
        horizontalLayout = new QHBoxLayout(TopWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        OpenBtn = new ClickedBtn(TopWidget);
        OpenBtn->setObjectName("OpenBtn");
        OpenBtn->setMinimumSize(QSize(20, 20));

        horizontalLayout->addWidget(OpenBtn);

        SaveBtn = new ClickedBtn(TopWidget);
        SaveBtn->setObjectName("SaveBtn");

        horizontalLayout->addWidget(SaveBtn);

        CloseBtn = new ClickedBtn(TopWidget);
        CloseBtn->setObjectName("CloseBtn");

        horizontalLayout->addWidget(CloseBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(TopWidget);

        MidWidget = new QWidget(Widget);
        MidWidget->setObjectName("MidWidget");
        horizontalLayout_2 = new QHBoxLayout(MidWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(MidWidget);
        textEdit->setObjectName("textEdit");

        horizontalLayout_2->addWidget(textEdit);


        verticalLayout->addWidget(MidWidget);

        BotWidget = new QWidget(Widget);
        BotWidget->setObjectName("BotWidget");
        horizontalLayout_3 = new QHBoxLayout(BotWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        time_lab = new QLabel(BotWidget);
        time_lab->setObjectName("time_lab");

        horizontalLayout_3->addWidget(time_lab);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        comboBox = new QComboBox(BotWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout_3->addWidget(comboBox);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        show_line_label = new QLabel(BotWidget);
        show_line_label->setObjectName("show_line_label");

        horizontalLayout_3->addWidget(show_line_label);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(BotWidget);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "MyText", nullptr));
        OpenBtn->setText(QString());
        SaveBtn->setText(QString());
        CloseBtn->setText(QString());
        time_lab->setText(QCoreApplication::translate("Widget", "0000-00-00  08:55:00", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "UTF-8", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "GBK", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Widget", "ANSI", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Widget", "UTF-16", nullptr));

        show_line_label->setText(QCoreApplication::translate("Widget", "00\350\241\214 00\345\210\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
