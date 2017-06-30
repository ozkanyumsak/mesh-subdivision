#pragma once

#include "AlgoRunner.h"

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>

int main(int, char** argv)
{
	HWND window = SoWin::init(argv[0]);
	SoWinExaminerViewer* viewer = new SoWinExaminerViewer(window);
	viewer->setBackgroundColor(SbColor(0.2f, 0.2f, 0.2f));

	viewer->setDrawStyle(SoWinViewer::DrawType::INTERACTIVE,
		SoWinViewer::DrawStyle::VIEW_WIREFRAME_OVERLAY);
	
	SoSeparator* root = new SoSeparator();
	root->ref();

	root->addChild((new AlgoRunner())->run());

	viewer->setSceneGraph(root);
	viewer->show();

	SoWin::show(window);
	SoWin::mainLoop();

	delete viewer;
	root->unref();

	return 0;
}