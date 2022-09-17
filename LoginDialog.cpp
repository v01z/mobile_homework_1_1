//
// Created by bincat on 9/16/22.
//

#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QSequentialAnimationGroup>
#include <QDebug>

//--------------------------------------------------------------------------

LoginDialog::LoginDialog(QWidget *parent):
    QWidget{ parent },
    login_txt_edit_{ new QLineEdit(this) },
    password_txt_edit_{ new QLineEdit(this) },
    auth_button_{ new QPushButton(tr("Authenticate"), this) }
{
    connect(auth_button_, SIGNAL(clicked()),
            SLOT(authButtonClicked()));
    connect(login_txt_edit_, SIGNAL(returnPressed()),
            SLOT(authButtonClicked()));
    connect(password_txt_edit_, SIGNAL(returnPressed()),
            SLOT(authButtonClicked()));

    auto vbox_layout { new QVBoxLayout(this) };
    vbox_layout->setMargin(35);

    login_txt_edit_->setPlaceholderText(tr("Login"));
    password_txt_edit_->setPlaceholderText(tr("Password"));
    password_txt_edit_->setEchoMode(QLineEdit::Password);

    vbox_layout->addWidget(login_txt_edit_);
    vbox_layout->addWidget(password_txt_edit_);
    vbox_layout->addWidget(auth_button_);

}


//--------------------------------------------------------------------------

void LoginDialog::farewellAnimation() {
    QPropertyAnimation *bye_animation =
            new QPropertyAnimation(this, "windowOpacity");

    QObject::connect(bye_animation, &QPropertyAnimation::finished,
                     this, [this](){this->close();});

    bye_animation->setDuration(500);
    bye_animation->setStartValue(1.0);
    bye_animation->setEndValue(0.0);
    bye_animation->setEasingCurve(QEasingCurve::Linear);

    bye_animation->start();
}
//--------------------------------------------------------------------------

void LoginDialog::changeFontColor(QLineEdit *line_edit) {

    QPalette palette { line_edit->palette() };
    QColor new_color = (palette.text().color() == QColor("black"))?
                       QColor("red"): QColor("black");

    palette.setColor(QPalette::Text, new_color);
    line_edit->setPalette(palette);
    line_edit->setText("");
}

//--------------------------------------------------------------------------

QPropertyAnimation* LoginDialog::horizMovingAnimation(
    const QPoint &starting_point, const QPoint &finish_point, int duration){

    QPropertyAnimation *moving =
            new QPropertyAnimation(this, "pos");

    moving->setStartValue(starting_point);
    moving->setDuration(duration);
    moving->setEndValue(finish_point);

    changeFontColor(login_txt_edit_);
    changeFontColor(password_txt_edit_);
    return moving;
}

//--------------------------------------------------------------------------

void LoginDialog::authButtonClicked() {

    if (correct_login == login_txt_edit_->text() &&
        correct_password == password_txt_edit_->text())
    {
        farewellAnimation();
        return;
    }
    static const int duration { 50 };
    QPoint staring_pos{this->pos().x(), this->pos().y() };
    QPoint finish_pos{ staring_pos.x() + 10, staring_pos.y() };

    auto moving_right_anim{ horizMovingAnimation(staring_pos, finish_pos, duration) };
    auto moving_left_anim{ horizMovingAnimation(finish_pos, staring_pos, duration) };

    QSequentialAnimationGroup *seq_anim_group =
            new QSequentialAnimationGroup(this);
    seq_anim_group->addAnimation(moving_right_anim);
    seq_anim_group->addAnimation(moving_left_anim);

    seq_anim_group->start();
}

//--------------------------------------------------------------------------
