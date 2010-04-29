#include <vtkSmartPointer.h>

#include <vtkJPEGReader.h>
//#include “itkCommand.h” // for later use se itk vtk connection
#include <itkImage.h>
#include <vtkImageData.h>
//#include “vtkKWImageIO.h”
//#include “vtkKWImage.h”
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkInteractorStyleImage.h>

int main(int argc, char* argv[])
{

  //Verify input arguments
  if ( argc != 2 )
    {
    vtkstd::cerr << "Usage: " << std::endl;
    vtkstd::cerr << argv[0] << "(.exe) takes 1 argument" <<std::endl;
    vtkstd::cerr <<"1- inputImageFile" <<std::endl;
    return EXIT_FAILURE;
    }

  //Parse input argument
  vtkstd::string inputFilename1 = static_cast<vtkstd::string> (argv[1]);

  //Read the image : with a vtk jpg reader :
  vtkSmartPointer<vtkJPEGReader> jPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName ( inputFilename1.c_str() );
  vtkstd::cout << "Reading " << inputFilename1.c_str() << vtkstd::endl;

  // Storing image in a vtkimagedata object :
  // Good count referencing pointer declaration & allocation
  // Smart pointer musn't be reallocated (<=>references)
  vtkSmartPointer<vtkImageData> vtkImage = jPEGReader->GetOutput();

  // Define the actor(s) of the screen : only one image
  vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
  actor->SetInput( vtkImage );

  // Define the renderer with its actor (our camera)
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> window =
    vtkSmartPointer<vtkRenderWindow>::New();
  window->AddRenderer(renderer);

  // Set up the interaction
  vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetInteractorStyle(imageStyle);
  window->SetInteractor(interactor);
  window->Render();


  // Start interaction
  // The Start() method doesn't return until the window is closed by the user
  interactor->Start();





  return EXIT_SUCCESS;
}
