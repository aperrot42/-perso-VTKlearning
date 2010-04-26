#include <vtkSmartPointer.h>
#include <vtkMinimalStandardRandomSequence.h>

int main(int arc, char argv[])
{
  // Create the random number generator with an associated smart pointer
  vtkSmartPointer<vtkMinimalStandardRandomSequence> RandomSeq
    = vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();

  // Initialize the random generator
  RandomSeq->SetSeed(20);

  // lets randomize
  RandomSeq->Next();


  // diplay a random number
  std::cout << "a random number VTK generated... Ouch my god ! : "
  << RandomSeq->GetValue() << std::endl
  << "Careful with this method thoug : it is a pregenerated list"
  << std::endl;

  return EXIT_SUCCESS;
}

