#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "ui_form.h"
#include <vtkImageActor.h>



class vtkImageData;

namespace Ui {
    class Form;
}

class Form : public QWidget, private Ui::Form {
    Q_OBJECT
public:
    Form(QWidget *parent = 0, vtkImageData *vtkImage = 0);
    ~Form();

protected:
    void changeEvent(QEvent *e);


};

#endif // FORM_H
