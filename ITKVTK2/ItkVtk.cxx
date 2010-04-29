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
#include <vtkCallbackCommand.h>

//#include <vtkViewImage2DCommand.h>
#include <vtkObject.h>
#include <vtkImageViewer2.h>
#include <vtkCamera.h>


// ITK :

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>
#include <itkNumericTraits.h>
#include <itkThresholdImageFilter.h>




class filteringItk
{




};

class displayingVtk
{





};


int parseInput (int argc, char* argv[], std::string fileName, char thresholdValue)
{

  //Verify input arguments
  if ( argc != 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "(.exe) takes 1 argument" <<std::endl;
    std::cerr <<"1- input image file" <<std::endl;
    std::cerr <<"2- threshold value" <<std::endl;
    return 1;
    }

  //Parse input argument
  fileName = static_cast<std::string> (argv[1]);
  thresholdValue = static_cast<char> (atoi(argv[2]));
  return 0;
}






void ZoomFunction ( vtkObject* caller, long unsigned int eventId, void* clientData, void* callData );


int main(int argc, char* argv[])
{


  //Parse input
  std::string argInputFilename = static_cast<std::string> (argv[1]);
  char argThresholdLevel = static_cast<char> (atoi(argv[2]));
  if (parseInput ( argc, argv, argInputFilename, argThresholdLevel))
    return EXIT_FAILURE;

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
  std::cout << "Reading " << inputFilename1.c_str() << std::endl;
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

  //Connecting itk pipeline to vtk pipeline :
  //declaration of the adapter
  typedef itk::ImageToVTKImageFilter<itkImageType> itkToVtkImageFilterType;
  itkToVtkImageFilterType::Pointer itkToVtkImageFilter =
                            itkToVtkImageFilterType::New();
  //connections itk to vtk
  itkToVtkImageFilter->SetInput(itkReader->GetOutput());


  vtkSmartPointer<vtkImageViewer2> vtkImgViewer1 = vtkSmartPointer<vtkImageViewer2>::New();

  vtkImgViewer1->SetInput(itkToVtkImageFilter->GetOutput());

  // Set up the visualization 1
  vtkSmartPointer<vtkInteractorStyleImage> vtkInteractorStyle =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> vtkInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkInteractor->SetInteractorStyle(vtkInteractorStyle);

  vtkImgViewer1->SetupInteractor(vtkInteractor);

  vtkImgViewer1->Render();

  vtkCamera* cam = vtkImgViewer1->GetRenderer()->GetActiveCamera();


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
  itkToVtkImageFilterType::Pointer itkToVtkImageFilter2 =
                            itkToVtkImageFilterType::New();

  //connections itk to vtk
  itkToVtkImageFilter2->SetInput(itkThresholdFilter->GetOutput());


  vtkSmartPointer<vtkImageViewer2> vtkImgViewer2 = vtkSmartPointer<vtkImageViewer2>::New();
  vtkImgViewer2->SetInput(itkToVtkImageFilter2->GetOutput());

  // Set up the visualization 2
  vtkSmartPointer<vtkInteractorStyleImage> vtkInteractorStyle2 =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> vtkInteractor2 =
   vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkInteractor2->SetInteractorStyle(vtkInteractorStyle2);

  vtkImgViewer2->SetupInteractor(vtkInteractor);

  vtkImgViewer2->Render();


  // visualize

 // vtkImgViewer2->GetRenderWindow()->GetInteractor()->Initialize();
 // vtkImgViewer1->GetRenderWindow()->GetInteractor()->Initialize();


  // add observer to process events :
  // declare a callback
  vtkSmartPointer<vtkCallbackCommand> zoomCallback =
                                    vtkSmartPointer<vtkCallbackCommand>::New();
  //declare the function associated to callback
  zoomCallback->SetCallback ( ZoomFunction );
  // set client data of the callback
  zoomCallback->SetClientData(vtkImgViewer1);
  // add observer
  vtkImgViewer2->GetRenderWindow()->AddObserver
                            ( vtkCommand::AnyEvent, zoomCallback );

  vtkImgViewer2->GetRenderer()->SetActiveCamera(cam);
  std::cout << "gf" ;
  // display loop
  vtkImgViewer2->GetRenderWindow()->GetInteractor()->Start();


  return EXIT_SUCCESS;
}


void ZoomFunction ( vtkObject* caller, long unsigned int eventId, void* clientData, void* callData )
{
  vtkSmartPointer<vtkImageViewer2> clientViewer =
                                    static_cast<vtkImageViewer2*>(clientData);
  clientViewer->Render();
  std::cout << "evt" <<std::endl ;
}
