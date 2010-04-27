#include <vtkSmartPointer.h>
// object definition
#include <vtkPoints.h>
#include <vtkCellArray.h> // why ?
#include <vtkUnstructuredGrid.h> // say what ????
#include <vtkPyramid.h>
// object representation
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
// Rendering
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
// points ensemble
vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
float p0[3] = {1., 0., 0.}; // we create a 4 points based pyramid
float p1[3] = {-1., 0., 0.};
float p2[3] = {0., 1., 0.};
float p3[3] = {0., -1., 0.};
float p4[3] = {0., 0., 1.};

points->InsertNextPoint(p0); // store the points in a points ensemble (points)
points->InsertNextPoint(p1);
points->InsertNextPoint(p2);
points->InsertNextPoint(p3);
points->InsertNextPoint(p4);

vtkSmartPointer<vtkPyramid> Pyramid = vtkSmartPointer<vtkPyramid>::New();

Pyramid->GetPointIds()->SetId(0, 0);
Pyramid->GetPointIds()->SetId(1, 1);
Pyramid->GetPointIds()->SetId(2, 2);
Pyramid->GetPointIds()->SetId(3, 3);
