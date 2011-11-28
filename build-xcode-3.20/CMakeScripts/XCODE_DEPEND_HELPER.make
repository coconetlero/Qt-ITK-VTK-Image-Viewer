# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# For each target create a dummy rule so the target does not have to exist


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.ImageViewer.Debug:
/Users/zian/Documents/Proyectos/Qt-ITK-VTK-Image-Viewer/build-xcode-3.20/Debug/ImageViewer:
	/bin/rm -f /Users/zian/Documents/Proyectos/Qt-ITK-VTK-Image-Viewer/build-xcode-3.20/Debug/ImageViewer


PostBuild.ImageViewer.Release:
/Users/zian/Documents/Proyectos/Qt-ITK-VTK-Image-Viewer/build-xcode-3.20/Release/ImageViewer:
	/bin/rm -f /Users/zian/Documents/Proyectos/Qt-ITK-VTK-Image-Viewer/build-xcode-3.20/Release/ImageViewer


PostBuild.ImageViewer.MinSizeRel:
/Users/zian/Documents/Proyectos/Qt-ITK-VTK-Image-Viewer/build-xcode-3.20/MinSizeRel/ImageViewer:
	/bin/rm -f /Users/zian/Documents/Proyectos/Qt-ITK-VTK-Image-Viewer/build-xcode-3.20/MinSizeRel/ImageViewer


PostBuild.ImageViewer.RelWithDebInfo:
/Users/zian/Documents/Proyectos/Qt-ITK-VTK-Image-Viewer/build-xcode-3.20/RelWithDebInfo/ImageViewer:
	/bin/rm -f /Users/zian/Documents/Proyectos/Qt-ITK-VTK-Image-Viewer/build-xcode-3.20/RelWithDebInfo/ImageViewer


