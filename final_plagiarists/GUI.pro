HEADERS     = GUI.h 
SOURCES	   = GUI.cpp main.cpp
FORMS       = GUI.ui

# install
target.path = GUI
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro
sources.path = .
INSTALLS += target sources
