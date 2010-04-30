#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "ui_form.h"
#include <vtkImageActor.h>


// forward declaration (just used as pointers in the header, this is okay)
class vtkImageData;
class vtkCamera;


namespace Ui {
    class Form;
}

class Form : public QWidget, private Ui::Form {
    Q_OBJECT
public:
    Form(QWidget *parent = 0, vtkImageData *vtkImage = 0,vtkImageData *vtkImage2 = 0);
    ~Form();

protected:
    void changeEvent(QEvent *e);

 private:


};

#endif // FORM_H
