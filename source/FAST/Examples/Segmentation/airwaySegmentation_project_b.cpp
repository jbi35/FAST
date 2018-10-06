/**
 * Examples/Segmentation/airwaySegmentation.cpp
 *
 * If you edit this example, please also update the wiki and source code file in the repository.
 */
#include "FAST/Algorithms/AirwaySegmentation/AirwaySegmentation.hpp"
#include "FAST/Importers/ImageFileImporter.hpp"
#include "FAST/Algorithms/SurfaceExtraction/SurfaceExtraction.hpp"
#include "FAST/Algorithms/CenterlineExtraction/CenterlineExtraction.hpp"
#include "FAST/Visualization/TriangleRenderer/TriangleRenderer.hpp"
#include "FAST/Visualization/LineRenderer/LineRenderer.hpp"
#include "FAST/Visualization/SimpleWindow.hpp"
#include "FAST/Exporters/VTKMeshFileExporter.hpp"
#include "FAST/Exporters/MetaImageExporter.hpp"
#include <iostream>
using namespace fast;

int main(int argc, char* argv[]) {

	// check if we have the correct command line arguments
	std::cout << "First argument "<< argv[1] << std::endl;
	//std::cout << "Second argument "<< argv[2] << std::endl;
	std::cout << "Third argument "<< argv[5] << std::endl;

	//std::cout << "Forth argument "<< argv[6] << std::endl;
	//exit(0);

	// Import CT data
	ImageFileImporter::pointer importer = ImageFileImporter::New();
	importer->setFilename(argv[1]);
	//importer->setFilename(Config::getTestDataPath() + "CT/CT-Thorax_p.mhd");

	// Do airway segmenetation
	AirwaySegmentation::pointer segmentation = AirwaySegmentation::New();
	// define seed point
	Vector3i my_seed(atof(argv[2]), atof(argv[3]), atof(argv[4]));
	//Vector3i my_seed(174, 152, 258);


	segmentation->setSeedPoint(my_seed);
	segmentation->setInputConnection(importer->getOutputPort());

	// Extract centerline from segmentation
	CenterlineExtraction::pointer centerline = CenterlineExtraction::New();
	centerline->setInputConnection(segmentation->getOutputPort());

	// Extract surface from segmentation
	SurfaceExtraction::pointer extraction = SurfaceExtraction::New();
	extraction->setInputConnection(segmentation->getOutputPort());

	VTKMeshFileExporter::pointer exporter = VTKMeshFileExporter::New();
	exporter->setInputConnection(centerline->getOutputPort());
	exporter->setFilename(argv[5]);
	//exporter->update(0);



	MetaImageExporter::pointer exporter2 = MetaImageExporter::New();
	//exporter2->setFilename(argv[6]);
	exporter2->setFilename(argv[6]);
	exporter2->setInputConnection(segmentation->getOutputPort());
	exporter2->update(0);
	exporter->update(0);
	//exit(0);

	// Set up renderers and window
	//TriangleRenderer::pointer renderer = TriangleRenderer::New();
	//renderer->addInputConnection(extraction->getOutputPort());

	//LineRenderer::pointer lineRenderer = LineRenderer::New();
	//lineRenderer->addInputConnection(centerline->getOutputPort());
	//lineRenderer->setDefaultDrawOnTop(true);
	//lineRenderer->setDefaultColor(Color::Blue());

	//SimpleWindow::pointer window = SimpleWindow::New();
	//window->addRenderer(renderer);
	//window->addRenderer(lineRenderer);

	//

//#ifdef FAST_CONTINUOUS_INTEGRATION
	// This will automatically close the window after 5 seconds, used for CI testing
  //  window->setTimeout(5*1000);
//#endif
	//window->start();
}
