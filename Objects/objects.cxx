#include <vtkSmartPointer.h>
// object definition
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>

#include <vtkLine.h>

#include <vtkXMLPolyDataWriter.h>

typedef float point3D[3]; // is it float or doule format for visu ?


// create a line and store it in a polydata
vtkSmartPointer<vtkPolyData> CreateLine(point3D p0,point3D p1);

// create a circle and store it into a polydata
vtkSmartPointer<vtkPolyData> CreateLine(point3D p0,point3D p1);



int main(int argc, char *argv[])
{
// we create 2 points
point3D p0 = {0., 0., 0.};
point3D p1 = {1., 1., 1.};



vtkSmartPointer<vtkPolyData> PolyLine= CreateLine(p0, p1);


//write the file containing geometrical informations
vtkSmartPointer<vtkXMLPolyDataWriter> writer =
                vtkSmartPointer<vtkXMLPolyDataWriter>::New();
writer->SetInput(PolyLine);
writer->SetFileName("Linesp.vtp");
writer->Write();


return EXIT_SUCCESS;

}





vtkSmartPointer<vtkPolyData> CreateLine(point3D p0, point3D p1)
{

// Create a pointlist object
vtkSmartPointer<vtkPoints> pointList = vtkSmartPointer<vtkPoints>::New();

// add a points to the list
pointList->InsertNextPoint(p0);
pointList->InsertNextPoint(p1);





// store the line linking the points in the poly data
 vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
   // Set id (A,B) A : id of the point in the line [0-1],
   // B id of the point in the list [0-end_of_list]
  line->GetPointIds()->SetId(0,0); // first point of line<=>first point of list
  line->GetPointIds()->SetId(1,1);

// create an ensemble of cells with the lines
vtkSmartPointer<vtkCellArray> Cells = vtkSmartPointer<vtkCellArray>::New();
Cells->InsertNextCell(line);

// we store the objects (cells in form of cell arrays) in poly
vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
// store the points of the lines in the poly data
polyData->SetPoints(pointList); // do we really have to ? YES...
// store the lines (in form of "cells") in the poly data
polyData->SetLines(Cells);

return polyData;
}
