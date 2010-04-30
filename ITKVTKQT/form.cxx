#include "form.h"
#include "ui_form.h"

#include <QVTKWidget.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>




#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageData.h>
#include <vtkCamera.h>
// Form constructor
Form::Form(QWidget *parent, vtkImageData *vtkImage, vtkImageData *vtkImage2) : QWidget(parent)

{
    setupUi(this);



  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();

  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
      vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  // VTK Renderer
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(sphereActor);

  // VTK/Qt wedded
  this->widget->GetRenderWindow()->AddRenderer(renderer);















  // Set up the visualization 1


  vtkSmartPointer<vtkImageViewer2> vtkImgViewer1 = vtkSmartPointer<vtkImageViewer2>::New();

  vtkImgViewer1->SetInput(vtkImage);


  vtkSmartPointer<vtkInteractorStyleImage> vtkInteractorStyle =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> vtkInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkInteractor->SetInteractorStyle(vtkInteractorStyle);

  vtkImgViewer1->SetupInteractor(vtkInteractor);

  vtkImgViewer1->Render();

  // set the camera
  vtkCamera *cam = vtkImgViewer1->GetRenderer()->GetActiveCamera();


// makes the program crash :
//this->qvtkWidget_a->SetRenderWindow(vtkImgViewer1->GetRenderWindow());
//this->qvtkWidget_a->GetRenderWindow()->SetInteractor(vtkInteractor);
//vtkInteractor->Start();


this->qvtkWidget_a->GetRenderWindow()->AddRenderer(vtkImgViewer1->GetRenderer());




  // Set up the visualization 2
  vtkSmartPointer<vtkImageViewer2> vtkImgViewer2 = vtkSmartPointer<vtkImageViewer2>::New();

  vtkImgViewer2->SetInput(vtkImage2);

  vtkImgViewer2->GetRenderer()->SetActiveCamera(cam);



// No effect ????
  vtkImgViewer2->SetupInteractor(vtkInteractor);


  vtkImgViewer2->Render();

this->qvtkWidget_b->GetRenderWindow()->AddRenderer(vtkImgViewer2->GetRenderer());

}

// Form destructor
Form::~Form()
{

}

void Form::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
