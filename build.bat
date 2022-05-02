@echo off

pushd build

set GLMInclude="..\vendor\glm"

set IncludeDirectories=-I%GLMInclude%
set LibDirectories=

set CompilerFlags= -DDEBUG -nologo -W4 -WX -Od -FS %IncludeDirectories% -Zi -EHsc -MD /D "_WINDOWS"
set LinkerFlags=-nologo -DEBUG %LibDirectories%

REM GLM is C++, need to be C++ in order to run the tests
REM cl /Tc ..\run_tests.c %CompilerFlags% /link %LinkerFlags% -SUBSYSTEM:CONSOLE shell32.lib
cl ..\run_tests.cpp %CompilerFlags% /link %LinkerFlags% -SUBSYSTEM:CONSOLE

popd
