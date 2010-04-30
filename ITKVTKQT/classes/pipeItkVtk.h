#ifndef PIPEITKVTK_H
#define PIPEITKVTK_H

//VTK includes
#include <vtkSmartPointer.h>
#include <itkImage.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageViewer2.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleImage.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

// ITK includes
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>
#include <itkNumericTraits.h>
#include <itkThresholdImageFilter.h>






class pipeItkVtk
{
public:
    pipeItkVtk();
    static void funcinclass();

};

#endif // PIPEITKVTK_H
