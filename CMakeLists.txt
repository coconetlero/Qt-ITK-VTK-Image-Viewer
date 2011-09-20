PROJECT(ImageViewer)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(COMMAND CMAKE_POLICY)
	   CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

FIND_PACKAGE(ITK)
IF(ITK_FOUND)
	INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
	MESSAGE(FATAL_ERROR "Cannot build InsightApplications without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

FIND_PACKAGE (VTK)
IF (VTK_FOUND)
   INCLUDE(${USE_VTK_FILE})
ENDIF(VTK_FOUND)


# Find QT 
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE( ${QT_USE_FILE} )

# support for out-of-source build
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR} #this is where ui_ImageViewerUI.h is generated
  ${CMAKE_CURRENT_SOURCE_DIR}
)
 
 
 
# Set your files and resources here
SET(ImageViewerSrcs imageviewer.cpp main.cpp)
SET(ImageViewerUI )
SET(ImageViewerHeaders imageviewer.h)
 
QT4_WRAP_UI(UISrcs ${ImageViewerUI})
QT4_WRAP_CPP(MOCSrcs ${ImageViewerHeaders} )
 
SOURCE_GROUP("Resources" FILES
  ${ImageViewerUI}
)
 
SOURCE_GROUP("Generated" FILES
  ${UISrcs}
  ${MOCSrcs}
)
 
ADD_EXECUTABLE(ImageViewer ${ImageViewerSrcs} ${UISrcs} ${MOCSrcs})
TARGET_LINK_LIBRARIES(ImageViewer QVTK ${VTK_LIBRARIES} ${ITK_LIBRARIES})

