//ITK includes
#include <itkImageToVTKImageFilter.h>
#include <itkImage.h>
#include <itkImageFileReader.h>

//VTK includes
// The QVTK widget ...
#include <QVTKWidget.h>

// QT includes
#include <QApplication>
#include "form.h"

// perso
#include "pipeItkVtk.h"





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


  QApplication app(argc, argv);


  // declaration of the QT form we give the image data pointer as input
  Form formQT1(0,itkToVtkImageFilter->GetOutput());

  formQT1.show();

  return app.exec();
}



