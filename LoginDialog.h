//
// Created by bincat on 9/16/22.
//

#ifndef INC_1_1_LOGINDIALOG_H
#define INC_1_1_LOGINDIALOG_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPropertyAnimation>

//--------------------------------------------------------------------------

class LoginDialog : public QWidget{
    Q_OBJECT

private:
    QLineEdit* login_txt_edit_;
    QLineEdit* password_txt_edit_;
    QPushButton* auth_button_;

    void farewellAnimation();
    void changeFontColor(QLineEdit*);
    QPropertyAnimation *horizMovingAnimation(const QPoint&, const QPoint&, int);

private slots:
    void authButtonClicked();

public:
    LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog() override = default;

};

//--------------------------------------------------------------------------

static const QString correct_login{ "login" };
static const QString correct_password{ "pass" };

//--------------------------------------------------------------------------

#endif //INC_1_1_LOGINDIALOG_H
