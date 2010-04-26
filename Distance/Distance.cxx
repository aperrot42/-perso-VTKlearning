#include <vtkMath.h>
#include <vtk
int main(int arc, char argv[])
{
  // Create 2 pts
  double p0[3] = {0.0, 0.0, 0.0};
  double p1[3] = {1.0, 1.0, 1.0};

  // compute squared distance
  double dist = vtkMath::Distance2BetweenPoints(p0,p1);

  // console output

  std::cout<< "the distance between P0 : " << p0[0] << p0[1] << p0[2]
  << " and P1 : " << p1[0] << p1[1] << p1[2]
  << " is " << dist << std::endl;


  return EXIT_SUCCESS;
}

