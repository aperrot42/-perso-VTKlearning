// VTK :

#include <vtkSmartPointer.h>

#include <vtkJPEGReader.h>
//#include “itkCommand.h” // for later use se itk vtk connection

#include <vtkImageData.h>

#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkInteractorStyleImage.h>

#include <vtkImageViewer2.h>

// ITK :

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>
#include <itkNumericTraits.h>
#include <itkThresholdImageFilter.h>





int main(int argc, char* argv[])
{

  //Verify input arguments
  if ( argc != 3 )
    {
    vtkstd::cerr << "Usage: " << std::endl;
    vtkstd::cerr << argv[0] << "(.exe) takes 1 argument" <<std::endl;
    vtkstd::cerr <<"1- input image file" <<std::endl;
    vtkstd::cerr <<"2- threshold value" <<std::endl;
    return EXIT_FAILURE;
    }

  //Parse input argument
  vtkstd::string argInputFilename = static_cast<vtkstd::string> (argv[1]);
  char argThresholdLevel = static_cast<char> (atoi(argv[2]));

  //image itk type :
  // Dimension of the image
  const unsigned Dimension = 2;
  // The type of manipulated pixels :
  typedef unsigned char itkPixelType;
  // The type of manipulated images :
  typedef itk::Image< itkPixelType, Dimension > itkImageType;

  //Read the image with an itk reader:
  typedef itk::ImageFileReader<itkImageType> itkReaderType;
  itkReaderType::Pointer itkReader = itkReaderType::New();
  itkReader->SetFileName(argInputFilename);
  itkReader->Update();



  /*
  //Read the image : with a vtk jpg reader :
  vtkSmartPointer<vtkJPEGReader> jPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName ( inputFilename1.c_str() );
  vtkstd::cout << "Reading " << inputFilename1.c_str() << vtkstd::endl;
  */

  try // try to read the input file
    {
    itkReader->Update();
    }
  catch( itk::ExceptionObject & excp )  // If something goes wrong
    {
    std::cerr << "Problem reading the input file" << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  //Threshold filtering :
  // Threshold filter creation :
  typedef itk::ThresholdImageFilter< itkImageType > itkThresholdFilterType;
  itkThresholdFilterType::Pointer itkThresholdFilter = itkThresholdFilterType::New();

  //Threshold filter initialization
  itkThresholdFilter->SetInput(itkReader->GetOutput());
  itkThresholdFilter->SetOutsideValue( itk::NumericTraits< itkPixelType >::Zero );

  // Threshold level setting
  itkThresholdFilter->ThresholdBelow(argThresholdLevel);

  try
    {
    itkThresholdFilter->Update();
    }
  catch( itk::ExceptionObject & excp )  // If something goes wrong
    {
    std::cerr << "Problem while filtering" << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  //Connecting itk pipeline to vtk pipeline :
  //declaration of the adapter
  typedef itk::ImageToVTKImageFilter<itkImageType> itkToVtkImageFilterType;
  itkToVtkImageFilterType::Pointer itkToVtkImageFilter =
                            itkToVtkImageFilterType::New();
  //connections itk to vtk
  itkToVtkImageFilter->SetInput(itkThresholdFilter->GetOutput());


  vtkSmartPointer<vtkImageViewer2> vtkImgViewer = vtkSmartPointer<vtkImageViewer2>::New();

  vtkImgViewer->SetInput(itkToVtkImageFilter->GetOutput());

  // Set up the visualization
  vtkSmartPointer<vtkInteractorStyleImage> vtkInteractorStyle =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> vtkInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkInteractor->SetInteractorStyle(vtkInteractorStyle);

  vtkImgViewer->SetupInteractor(vtkInteractor);

  vtkImgViewer->Render();

  std::cout << vtkImgViewer->GetRenderWindow()->GetInteractor() << vtkstd::endl;
  vtkImgViewer->GetRenderWindow()->GetInteractor()->Start();


  return EXIT_SUCCESS;
}
